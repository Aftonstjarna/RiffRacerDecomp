#include "impl.hpp"
using namespace riff;
// Dummy EAX + regparm(3) models EDX=table, ECX=state and caller-popped
// fourth argument. This is not the callee-pop GCC fastcall convention.
extern "C" Value* __attribute__((regparm(3))) original_script_table_ensure_string_slot(unsigned,Table*,State*,String*);
extern "C" Value* __attribute__((regparm(3))) original_script_table_new_key(unsigned,Table*,State*,const Value*);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsStorage[32];
static unsigned fsCorrupt;
// Original non-executable dispatch data at 0x4f018c: tags 1,2,3,4.
uint32_t dispatch[4] __attribute__((section(".oracle_dispatch"),used,aligned(4)))={0x4f0150,0x4f016a,0x4f0127,0x4f0133};
static Value* insert(State* s,Table* t,const Value* k){Value* p=original_script_table_new_key(0,t,s,k);if(test_get_fs_head()!=fsStorage[0])fsCorrupt=1;return p;}
static const Services vm={insert};
static bool equal(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
static void fill(void* p,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)p)[i]=uint8_t(37+i*19);}
struct Fixture {
 uint32_t left; Table table; uint32_t right;
 Node nodes[8]; String strings[3]; Value array[5];
 uint32_t state[24]; uint32_t global[24]; uint32_t end;
};
static Fixture f,saved,after;
static State* state(){return reinterpret_cast<State*>(f.state);}
static void setup(unsigned exponent,unsigned hash,unsigned flags,unsigned white){
 fill(&f,sizeof f);f.table.array=f.array;f.table.arraySize=5;
 f.table.nodes=f.nodes;f.table.lastFree=f.nodes+8;f.table.hashLog2=uint8_t(exponent);
 f.table.header[5]=uint8_t(0xa0|flags);f.table.header[6]=0xed;
 f.state[4]=uint32_t(uintptr_t(f.global));
 for(unsigned i=0;i<3;++i){f.strings[i].hash=hash;f.strings[i].header[5]=uint8_t(white);}
 for(unsigned i=0;i<8;++i){f.nodes[i].value.tag=0;f.nodes[i].key.tag=0;f.nodes[i].next=0;}
}
static unsigned comparisons;
static int compare(unsigned selected,bool unchanged){
 saved=f;
 Value* a=original_script_table_ensure_string_slot(0,&f.table,state(),f.strings);
 if(test_get_fs_head()!=fsStorage[0])return 5;
 after=f;f=saved;
 Value* b=state()->ensureStringSlot(&f.table,f.strings,vm);
 ++comparisons;
 if(fsCorrupt||a!=b||b!=&f.nodes[selected].value||!equal(&f,&after,sizeof f))return 1;
 if(unchanged&&!equal(&f,&saved,sizeof f))return 2;
 if(f.table.header[6]!=0xed||f.left!=saved.left||f.right!=saved.right||f.end!=saved.end)return 3;
 if(!equal(f.state,saved.state,sizeof f.state)||!equal(f.strings,saved.strings,sizeof f.strings)||!equal(f.array,saved.array,sizeof f.array))return 4;
 return 0;
}
static int existing(unsigned exponent,unsigned hash,unsigned kind,unsigned valueTag){
 setup(exponent,hash,4,1);
 unsigned b=hash & ((uint32_t(1)<<(exponent&31))-1);
 unsigned selected=b;
 if(kind){
  // Reject same pointer with non-string tag; then reject a different interned
  // string with identical hash before finding the actual key at chain tail.
  f.nodes[b].key.payload.string=f.strings;f.nodes[b].key.tag=kind==1?3:0xffffffff;
  unsigned middle=(b+1)%8;selected=(b+2)%8;
  f.nodes[b].next=f.nodes+middle;
  f.nodes[middle].key.payload.string=f.strings+1;f.nodes[middle].key.tag=4;
  f.nodes[middle].next=f.nodes+selected;
 }
 f.nodes[selected].key.payload.string=f.strings;f.nodes[selected].key.tag=4;
 f.nodes[selected].value.tag=valueTag;
 return compare(selected,true);
}
static int insertion(unsigned kind,unsigned flags,unsigned white){
 setup(3,2,flags,white);unsigned selected=2;
 if(kind==1){ // Occupant belongs in this bucket: append free node.
  f.nodes[2].key.payload.string=f.strings+1;f.nodes[2].key.tag=4;
  f.nodes[2].value.tag=3;selected=7;
 }
 if(kind==2){ // Displaced occupant: move it back into a free node.
  f.strings[1].hash=1;
  f.nodes[2].key.payload.string=f.strings+1;f.nodes[2].key.tag=4;f.nodes[2].value.tag=3;
  f.nodes[1].key=f.nodes[2].key;f.nodes[1].value.tag=3;f.nodes[1].next=f.nodes+2;
 }
 int r=compare(selected,false);if(r)return r;
 if(f.nodes[selected].key.tag!=4||f.nodes[selected].key.payload.string!=f.strings||f.nodes[selected].value.tag!=0)return 5;
 bool barrier=(flags&4)&&(white&3);
 if(f.table.header[5]!=(barrier?uint8_t(saved.table.header[5]&~4):saved.table.header[5]))return 6;
 if(f.table.gcLink!=(barrier?saved.global[10]:saved.table.gcLink))return 7;
 if(f.global[10]!=(barrier?uint32_t(uintptr_t(&f.table)):saved.global[10]))return 8;
 if(kind==0&&f.table.lastFree!=saved.table.lastFree)return 9;
 if(kind&&f.table.lastFree!=f.nodes+7)return 10;
 if(kind==1&&(f.nodes[2].next!=f.nodes+7||f.nodes[7].next!=0))return 11;
 if(kind==2&&(f.nodes[1].next!=f.nodes+7||!equal(&f.nodes[7],&saved.nodes[2],sizeof(Node))))return 12;
 return 0;
}
static unsigned calls,bad;
static Value result;static Value* returned;
static Value* checkNew(State* s,Table* t,const Value* k){
 ++calls;if(s!=state()||t!=&f.table||k->tag!=4||k->payload.string!=f.strings||!equal(&f,&saved,sizeof f))bad=1;
 return returned;
}
extern "C" int test_main(){
 fsStorage[0]=0xffffffffu;
 if(test_install_fs(fsStorage)!=0||test_get_fs_head()!=fsStorage[0])return 60;
 for(unsigned exponent=0;exponent<256;++exponent)for(unsigned hash=0;hash<8;++hash)for(unsigned kind=0;kind<3;++kind)for(unsigned tag=0;tag<9;++tag){
  int r=existing(exponent,hash,kind,tag);if(r)return 10+r;
 }
 if(uintptr_t(dispatch)==0x4f018c){
  for(unsigned kind=0;kind<3;++kind)for(unsigned flags=0;flags<=4;flags+=4)for(unsigned white=0;white<4;++white){
   int r=insertion(kind,flags,white);if(r)return 30+r;
  }
  const char msg[]="Full original lookup and insertion comparisons passed\n";test_write(msg,sizeof(msg)-1);
 }else{
  const char msg[]="Dispatch fixture unmapped: original insertion comparisons skipped; original lookup comparisons passed\n";test_write(msg,sizeof(msg)-1);
 }
 const Services checked={checkNew};
 for(unsigned outcome=0;outcome<3;++outcome){
  setup(3,2,4,1);saved=f;calls=bad=0;
  returned=outcome==0?&result:outcome==1?nilSentinel():0;
  Value* p=state()->ensureStringSlot(&f.table,f.strings,checked);
  if(p!=returned||calls!=1||bad||!equal(&f,&saved,sizeof f))return 50;
 }
 return comparisons?0:51;
}
extern "C" void* memcpy(void* d,const void* s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void* d,int c,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=uint8_t(c);return d;}
