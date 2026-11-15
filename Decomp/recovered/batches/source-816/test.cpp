#include "impl.hpp"
using namespace riff;
// regparm(3) with a dummy EAX argument expresses ECX=state, EDX=table,
// caller-popped key. GCC fastcall is correct for the two-register lookup.
extern "C" Value* __attribute__((regparm(3))) original_script_table_ensure_value_slot(unsigned,Table*,State*,const Value*);
extern "C" Value* __attribute__((fastcall)) original_script_table_get_value(Table*,const Value*);
extern "C" Value* __attribute__((regparm(3))) original_script_table_new_key(unsigned,Table*,State*,const Value*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*,unsigned);
static unsigned bad;
static Value* get(Table* t,const Value* k){return original_script_table_get_value(t,k);}
static Value* insert(State* s,Table* t,const Value* k){return original_script_table_new_key(0,t,s,k);}
static void unexpectedError(State*,const char*){bad=1;}
static const Services vm={get,insert,unexpectedError};
static bool equal(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
static void fill(void* p,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)p)[i]=uint8_t(37+i*19);}
struct Fixture {
 uint32_t left; Table table; uint32_t right; Value key; Value array[5];
 Node nodes[8]; uint32_t state[24]; uint32_t global[24];
 uint8_t objects[2][16]; uint32_t end;
};
static Fixture f,saved,after;
static State* state(){return reinterpret_cast<State*>(f.state);}
static unsigned bucket(uint32_t p){return p%7;}
static void setup(unsigned flags,unsigned white){
 fill(&f,sizeof f);f.table.array=f.array;f.table.arraySize=5;
 f.table.nodes=f.nodes;f.table.lastFree=f.nodes+8;f.table.hashLog2=3;
 f.table.header[5]=uint8_t(0xa0|flags);f.table.header[6]=0xed;
 f.state[4]=uint32_t(uintptr_t(f.global));f.objects[0][5]=uint8_t(white);
 f.objects[1][5]=0;f.key.payload.bits=uint32_t(uintptr_t(f.objects[0]));f.key.tag=5;
 for(unsigned i=0;i<8;++i){f.nodes[i].value.tag=0;f.nodes[i].key.tag=0;f.nodes[i].next=0;}
}
static int differential(unsigned kind,unsigned tag,unsigned flags,unsigned white,unsigned mode){
 setup(flags,white);f.key.tag=tag;
 unsigned b=bucket(f.key.payload.bits), selected=b;
 if(kind==0){f.key.tag=3;f.key.payload.number=float(tag%5+1);f.array[tag%5].tag=tag;}
 if(kind==1){f.nodes[b].key=f.key;f.nodes[b].value.tag=0;}
 if(kind==3){f.nodes[b].key=f.key;f.nodes[b].key.tag=tag==5?6:5;f.nodes[b].value.tag=3;selected=7;}
 if(kind==4){
  unsigned other=bucket(uint32_t(uintptr_t(f.objects[1])));
  if(other==b)return 1;
  f.nodes[b].key.payload.bits=uint32_t(uintptr_t(f.objects[1]));f.nodes[b].key.tag=5;f.nodes[b].value.tag=3;
  f.nodes[other].key=f.nodes[b].key;f.nodes[other].value.tag=3;f.nodes[other].next=f.nodes+b;
 }
 if(kind==5){f.key.tag=4; // Existing string lookup uses stored hash at object +8.
  uint32_t* object=reinterpret_cast<uint32_t*>(f.objects[0]);object[2]=3;b=3;
  f.nodes[b].key=f.key;f.nodes[b].value.tag=tag;
 }
 saved=f;test_set_mxcsr(mode);bad=0;
 Value* a=original_script_table_ensure_value_slot(0,&f.table,state(),&f.key);
 unsigned mx=test_get_mxcsr();after=f;
 f=saved;test_set_mxcsr(mode);
 Value* c=state()->ensureValueSlot(&f.table,&f.key,vm);
 if(bad||a!=c||mx!=test_get_mxcsr()||!equal(&f,&after,sizeof f))return 2;
 if(f.table.header[6]!=0||f.left!=saved.left||f.right!=saved.right||f.end!=saved.end||!equal(&f.key,&saved.key,8)||!equal(f.objects,saved.objects,sizeof f.objects))return 3;
 if(kind==0||kind==1||kind==5){saved.table.header[6]=0;if(!equal(&f,&saved,sizeof f))return 4;}
 else {
  Node* n=f.nodes+selected;
  if(c!=&n->value||!equal(&n->key,&f.key,8)||n->value.tag!=0)return 5;
  bool barrier=(flags&4)&&(white&3);
  if(f.table.header[5]!=(barrier?uint8_t(saved.table.header[5]&~4):saved.table.header[5]))return 6;
  if(f.global[10]!=(barrier?uint32_t(uintptr_t(&f.table)):saved.global[10]))return 7;
  if(f.table.gcLink!=(barrier?saved.global[10]:saved.table.gcLink))return 8;
  if(!equal(f.state,saved.state,sizeof f.state)||!equal(f.array,saved.array,sizeof f.array))return 9;
 }
 return 0;
}
static unsigned gets,news,errors,expectedError;
static Value result;static Value* lookupResult;
static Value* fakeGet(Table* t,const Value* k){++gets;if(t!=&f.table||k!=&f.key)bad=1;t->header[6]=0x9a;return lookupResult;}
static Value* fakeNew(State* s,Table* t,const Value* k){++news;if(s!=state()||t!=&f.table||k!=&f.key||t->header[6]!=0)bad=1;return &result;}
static bool textEqual(const char* a,const char* b){while(*a&&*a==*b){++a;++b;}return *a==*b;}
static void fakeError(State* s,const char* text){++errors;if(s!=state()||f.table.header[6]!=0||!textEqual(text,expectedError==1?"table index is nil":"table index is NaN"))bad=1;}
extern "C" int test_main(){
 unsigned old=test_get_mxcsr();
 for(unsigned m=0;m<4;++m)for(unsigned tag=0;tag<9;++tag){
  int r=differential(0,tag,4,1,0x1f80|(m<<13));if(r)return 10+r;
  r=differential(5,tag,4,1,0x1f80|(m<<13));if(r)return 20+r;
 }
 for(unsigned m=0;m<4;++m)for(unsigned tag=5;tag<=8;++tag)for(unsigned flags=0;flags<=4;flags+=4)for(unsigned white=0;white<4;++white)for(unsigned kind=1;kind<=4;++kind){
  int r=differential(kind,tag,flags,white,0x1f80|(m<<13));if(r)return 30+r;
 }
 const uint32_t bits[]={0,0x80000000,0x3f800000,0xbf800000,1,0x7f800000,0xff800000,0x7fc00001,0xffc12345,0x7f800001};
 const Services fake={fakeGet,fakeNew,fakeError};
 for(unsigned tag=0;tag<9;++tag)for(unsigned i=0;i<sizeof(bits)/sizeof(bits[0]);++i)for(unsigned outcome=0;outcome<3;++outcome){
  setup(4,1);f.key.tag=tag;f.key.payload.bits=bits[i];saved=f;
  gets=news=errors=bad=0;lookupResult=outcome==0?nilSentinel():outcome==1?&result:0;
  expectedError=tag==0?1:tag==3&&(bits[i]&0x7fffffff)>0x7f800000?2:0;
  test_set_mxcsr(0x1f80);Value* p=state()->ensureValueSlot(&f.table,&f.key,fake);
  if(bad||gets!=1||news!=(outcome==0?1u:0u)||errors!=(outcome==0&&expectedError?1u:0u)||p!=(outcome==0?&result:lookupResult))return 50;
  saved.table.header[6]=0;if(!equal(&f,&saved,sizeof f))return 51;
 }
 test_set_mxcsr(old);
 const char msg[]="584 original comparisons and 270 dependency-boundary cases passed\n";
 test_write(msg,sizeof(msg)-1);return 0;
}
extern "C" void* memcpy(void* d,const void* s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void* d,int c,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=uint8_t(c);return d;}
