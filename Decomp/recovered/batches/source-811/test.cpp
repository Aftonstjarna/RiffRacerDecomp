#include "impl.hpp"
using namespace riff;
extern "C" Value* __attribute__((regparm(3))) original_script_table_ensure_integer_slot(unsigned,Table*,State*,int32_t);
extern "C" Value* __attribute__((fastcall)) original_script_table_get_integer(Table*,int32_t);
extern "C" Value* __attribute__((regparm(3))) original_script_table_new_key(unsigned,Table*,State*,const Value*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*,unsigned);
// Data from Game.exe 0x4f018c and 0xa063ec, not executable bytes.
uint32_t oracle_dispatch[4] __attribute__((section(".oracle_dispatch"),used,aligned(4)))={0x4f0150,0x4f016a,0x4f0127,0x4f0133};
uint32_t oracle_zero __attribute__((section(".oracle_zero"),used,aligned(4)))=0;
static Value* lookup(Table* t,int32_t i){return original_script_table_get_integer(t,i);}
static Value* insert(State* s,Table* t,const Value* k){return original_script_table_new_key(0,t,s,k);}
static const Services vm={lookup,insert};
static bool equal(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
static void fill(void* a,unsigned n,unsigned seed){for(unsigned i=0;i<n;++i)((uint8_t*)a)[i]=uint8_t(seed+i*17);}
struct Fixture {uint32_t left;Table table;uint32_t right;Value array[5];Node nodes[8];uint32_t state[24];};
static Fixture f,saved,after;
static unsigned arrayTag;
static void setup(){
 fill(&f,sizeof f,21);f.table.array=f.array;f.table.arraySize=5;f.table.nodes=f.nodes;f.table.lastFree=f.nodes+8;f.table.hashLog2=3;
 for(unsigned i=0;i<8;++i){f.nodes[i].value.tag=0;f.nodes[i].key.tag=0;f.nodes[i].next=0;}
}
static State* state(){return reinterpret_cast<State*>(f.state);}
static unsigned indexFor(int32_t k){Value v;v.payload.number=float(k);return k==0?0:v.payload.bits%7;}
static int differential(int32_t k,unsigned kind,unsigned mode){
 setup();for(unsigned j=0;j<5;++j)f.array[j].tag=arrayTag;test_set_mxcsr(mode);
 unsigned bucket=0;
 if(kind){bucket=indexFor(k);if(kind==1){f.nodes[bucket].key.payload.number=float(k);f.nodes[bucket].key.tag=3;f.nodes[bucket].value.tag=0;}
 if(kind==3){ // Occupied main bucket with a same-bucket numeric collision.
   f.nodes[bucket].key.payload.number=0.0f;f.nodes[bucket].key.tag=3;f.nodes[bucket].value.tag=3;
   // Use exponent zero in this case: all numeric keys hash to bucket zero.
   f.table.hashLog2=0;bucket=0;
   for(unsigned i=0;i<8;++i){f.nodes[i].key.tag=0;f.nodes[i].value.tag=0;f.nodes[i].next=0;}
   f.nodes[0].key.payload.number=0;f.nodes[0].key.tag=3;f.nodes[0].value.tag=3;
 }}
 saved=f;test_set_mxcsr(mode);
 Value* a=original_script_table_ensure_integer_slot(0,&f.table,state(),k);
 unsigned mx=test_get_mxcsr();after=f;
 // No fixture address changes: pointer fields remain comparable after reset.
 f=saved;test_set_mxcsr(mode);
 Value* b=state()->ensureIntegerSlot(&f.table,k,vm);
 if(a!=b||test_get_mxcsr()!=mx||!equal(&f,&after,sizeof f))return 1;
 if(!equal(f.state,saved.state,sizeof f.state)||f.left!=saved.left||f.right!=saved.right||(!equal(&f.table,&saved.table,sizeof(Table)) && kind!=3))return 2;
 if(kind==0||kind==1){if(!equal(&f,&saved,sizeof f))return 3;}
 else {
   Value numeric;numeric.payload.number=float(k);numeric.tag=3;
   Node* selected=kind==3?f.nodes+7:f.nodes+bucket;
   if(b!=&selected->value||!equal(&selected->key,&numeric,8)||!equal(&selected->value,&saved.nodes[selected-f.nodes].value,8))return 4;
 }
 return 0;
}
// Source-only dependency-boundary assertions cover sentinel identity, null
// passthrough and exact signed input forwarding even without fixed data maps.
static Value result,captured;static unsigned gets,news,bad;static int32_t wanted;
static Value* returned;static State* expectedState;
static Value* fakeGet(Table* t,int32_t i){++gets;if(t!=&f.table||i!=wanted)bad=1;return returned;}
static Value* fakeNew(State* s,Table* t,const Value* k){++news;if(s!=expectedState||t!=&f.table)bad=1;captured=*k;return &result;}
extern "C" int test_main(){
 unsigned old=test_get_mxcsr();
 for(unsigned tag=0;tag<8;++tag){arrayTag=tag;for(int32_t k=1;k<=5;++k){int r=differential(k,0,0x1f80);if(r)return 10+r;}}
 bool mapped=reinterpret_cast<uintptr_t>(oracle_dispatch)==0x4f018c && reinterpret_cast<uintptr_t>(&oracle_zero)==0xa063ec;
 const int32_t keys[]={0,-1,6,17,-17,16777215,16777216,16777217,-16777217,2147483647,(-2147483647-1)};
 for(unsigned m=0;m<4;++m)for(unsigned i=0;i<sizeof(keys)/sizeof(keys[0]);++i){
  unsigned mode=0x1f80|(m<<13);
  if(mapped)for(unsigned kind=1;kind<=3;++kind){if(kind==3&&keys[i]==0)continue;int r=differential(keys[i],kind,mode);if(r)return 20+r;}
  setup();saved=f;wanted=keys[i];expectedState=state();
  const Services fake={fakeGet,fakeNew};
  for(unsigned miss=0;miss<3;++miss){
   gets=news=bad=0;returned=miss==0?&result:miss==1?nilSentinel():0;
   test_set_mxcsr(mode);Value* p=state()->ensureIntegerSlot(&f.table,wanted,fake);
   if(bad||gets!=1||news!=(miss==1?1u:0u)||p!=(miss==1?&result:returned)||!equal(&f,&saved,sizeof f))return 30;
   if(miss==1){Value expected;expected.payload.number=float(wanted);expected.tag=3;if(!equal(&captured,&expected,8))return 31;}
  }
 }
 test_set_mxcsr(old);
 const char full[]="full mapped original comparisons passed\n";
 const char partial[]="original array comparisons passed; hash/insertion comparisons require dispatch and zero mappings (locally tested)\n";
 if(mapped)test_write(full,sizeof(full)-1);else test_write(partial,sizeof(partial)-1);
 return 0;
}
extern "C" void* memcpy(void* d,const void* s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void* d,int c,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=uint8_t(c);return d;}
