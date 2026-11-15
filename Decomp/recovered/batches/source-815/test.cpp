#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((regparm(3))) original_script_table_resize(unsigned,Table*,State*,int32_t,int32_t);
extern "C" void __attribute__((regparm(3))) original_script_table_resize_array(unsigned,Table*,State*,int32_t);
extern "C" void __attribute__((regparm(3))) original_script_table_initialize_hash_storage(unsigned,Table*,State*,int32_t);
extern "C" Value* __attribute__((regparm(3))) original_script_table_ensure_integer_slot(unsigned,Table*,State*,int32_t);
extern "C" Value* __attribute__((fastcall)) original_script_table_get_value(Table*,const Value*);
extern "C" Value* __attribute__((regparm(3))) original_script_table_new_key(unsigned,Table*,State*,const Value*);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(unsigned,void*,State*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
// Data only: original nil value, dummy node and ceil-log table at 0x99a41c.
// Full local linker maps these; unrecognized trusted sections are detected.
struct Constants { Value nil; Node dummy; uint8_t log[256]; };
Constants constants __attribute__((section(".resize_constants"),used,aligned(4)));
uint32_t dispatch[4] __attribute__((section(".oracle_dispatch"),used,aligned(4)))={0x4f0150,0x4f016a,0x4f0127,0x4f0133};
uint32_t zero __attribute__((section(".oracle_zero"),used,aligned(4)))=0;
static void fill(void* p,unsigned n,uint8_t b){for(unsigned i=0;i<n;++i)((uint8_t*)p)[i]=b;}
static bool equal(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
extern "C" void* memcpy(void* d,const void* s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void* d,int c,size_t n){fill(d,n,uint8_t(c));return d;}
struct Event { void* ptr; uint32_t oldN,newN; };
struct Fixture {
 uint32_t guard1; Table t; uint32_t guard2;
 Value array[16]; Node oldNodes[16];
 uint32_t state[32],global[32];
 uint32_t arena[4096]; Event events[64];
 unsigned used,calls,bad;
};
static Fixture f,saved,after;
static void* allocation(void* user,void* memory,uint32_t oldN,uint32_t newN){
 if(user!=&f || f.calls>=64){f.bad=1;return 0;}
 Event& e=f.events[f.calls++];e.ptr=memory;e.oldN=oldN;e.newN=newN;
 if(!newN)return 0;
 unsigned words=(newN+3)/4;
 if(f.used+words>4096){f.bad=1;return 0;}
 void* result=f.arena+f.used;f.used+=words;
 if(memory)memcpy(result,memory,oldN<newN?oldN:newN);
 return result;
}
static void grow(State* s,Table* t,int32_t n){original_script_table_resize_array(0,t,s,n);}
static void init(State* s,Table* t,int32_t n){original_script_table_initialize_hash_storage(0,t,s,n);}
static Value* integer(State* s,Table* t,int32_t n){return original_script_table_ensure_integer_slot(0,t,s,n);}
static Value* lookup(Table* t,const Value* k){return original_script_table_get_value(t,k);}
static Value* insert(State* s,Table* t,const Value* k){return original_script_table_new_key(0,t,s,k);}
static void* reallocVM(State* s,void* p,uint32_t oldN,uint32_t newN){return original_script_reallocate(0,p,s,oldN,newN);}
static void error(State*,Error){f.bad=1;}
static const Services services={grow,init,integer,lookup,insert,reallocVM,error};
static State* state(){return reinterpret_cast<State*>(f.state);}
static void setup(unsigned oldSize,unsigned exponent,bool sentinel){
 fill(&f,sizeof f,0xa5);f.used=f.calls=f.bad=0;
 f.t.array=f.array;f.t.arraySize=int32_t(oldSize);f.t.hashLog2=uint8_t(exponent);
 f.t.nodes=sentinel?emptyHash():f.oldNodes;f.t.lastFree=f.oldNodes+(1u<<exponent);
 for(unsigned i=0;i<16;++i){f.array[i].tag=0;f.array[i].payload.bits=0x87650000u+i;
 f.oldNodes[i].value.tag=0;f.oldNodes[i].key.tag=0;f.oldNodes[i].next=0;}
 f.state[4]=uint32_t(uintptr_t(f.global));
 f.global[3]=uint32_t(uintptr_t(&allocation));f.global[4]=uint32_t(uintptr_t(&f));
 f.global[17]=0xfffffff0u;
}
static int compare(int32_t requested,int32_t hashRequest){
 saved=f;test_set_mxcsr(0x1f80);
 original_script_table_resize(0,&f.t,state(),requested,hashRequest);
 unsigned mx=test_get_mxcsr();after=f;
 if(f.bad)return 1;
 f=saved;test_set_mxcsr(0x1f80);state()->resize(&f.t,requested,hashRequest,services);
 if(f.bad||test_get_mxcsr()!=mx||!equal(&f,&after,sizeof f))return 2;
 if(f.guard1!=saved.guard1||f.guard2!=saved.guard2||!equal(f.state,saved.state,sizeof f.state))return 3;
 if(!equal(f.oldNodes,saved.oldNodes,sizeof f.oldNodes))return 4;
 for(unsigned i=0;i<16;++i){
  Value expected=saved.array[i];
  if(requested==saved.t.arraySize && i<unsigned(requested) && saved.t.nodes!=emptyHash())
   for(unsigned j=0;j<(1u<<(saved.t.hashLog2&31));++j)
    if(saved.oldNodes[j].value.tag && saved.oldNodes[j].key.tag==3 && saved.oldNodes[j].key.payload.number==float(i+1))expected=saved.oldNodes[j].value;
  if(!equal(f.array+i,&expected,8))return 4;
 }
 if(f.t.arraySize!=requested||f.t.metatable!=saved.t.metatable||f.t.gcLink!=saved.t.gcLink||!equal(f.t.header,saved.t.header,6))return 5;
 // Independent allocation accounting and untouched global fields.
 uint32_t bytes=saved.global[17];
 for(unsigned i=0;i<f.calls;++i)bytes+=f.events[i].newN-f.events[i].oldN;
 if(f.global[17]!=bytes)return 6;
 for(unsigned i=0;i<32;++i)if(i!=17&&f.global[i]!=saved.global[i])return 7;
 return 0;
}
extern "C" int test_main(){
 unsigned oldMx=test_get_mxcsr();
 fill(&constants,sizeof constants,0);
 for(unsigned i=1;i<256;++i){unsigned x=i;while(x){++constants.log[i];x>>=1;}}
 bool mapped=uintptr_t(&constants)==0x99a41c && uintptr_t(dispatch)==0x4f018c && uintptr_t(&zero)==0xa063ec;
 // Always-executable direct oracle paths: empty hash, resize both directions,
 // retained nil slots, old hash values moving to existing or newly grown array.
 for(unsigned old=0;old<=12;++old)for(unsigned n=0;n<=12;++n)for(unsigned e=0;e<=3;++e){
  setup(old,e,false);
  if(n>0){f.oldNodes[0].key.tag=3;f.oldNodes[0].key.payload.number=1.0f;f.oldNodes[0].value.tag=7;f.oldNodes[0].value.payload.bits=0xdeadbeef;}
  int r=compare(int32_t(n),0);if(r)return 10+r;
  if(n>0&&(f.t.array[0].tag!=7||f.t.array[0].payload.bits!=0xdeadbeef||f.t.header[6]!=0))return 19;
 }
 for(unsigned e=0;e<4;++e){setup(4,e,false);f.t.hashLog2=uint8_t(32+e);int r=compare(4,0);if(r)return 20+r;}
 if(mapped){
  // New storage requests round to powers of two. Mix nil/non-nil truncated
  // array slots and numeric hash keys; ample hash space prevents nested rehash.
  const int requests[]={16,17,31,32,33};
  for(unsigned old=0;old<=12;++old)for(unsigned n=0;n<=12;++n)for(unsigned pattern=0;pattern<4;++pattern)for(unsigned h=0;h<5;++h){
   setup(old,3,false);
   for(unsigned i=0;i<old;++i)f.array[i].tag=(i+pattern)%3?((i&1)?0xffffffffu:3u):0u;
   for(unsigned i=0;i<8;++i)if((i+pattern)%3){
    f.oldNodes[i].key.tag=3;f.oldNodes[i].key.payload.number=float(i+17);
    f.oldNodes[i].value.tag=uint32_t(i+1);f.oldNodes[i].value.payload.bits=0xcafe0000u+i;
   }
   int r=compare(int32_t(n),requests[h]);if(r)return 30+r;
   for(unsigned i=0;i<old;++i){
    Value* v= i<unsigned(n)?f.t.array+i:0;
    if(!v && saved.array[i].tag)v=integer(state(),&f.t,int32_t(i+1));
    if(v&& !equal(v,saved.array+i,8))return 39;
   }
   for(unsigned i=0;i<8;++i)if(saved.oldNodes[i].value.tag){
    Value* v=integer(state(),&f.t,int32_t(i+17));
    if(v==nilValue()||!equal(v,&saved.oldNodes[i].value,8))return 38;
   }
  }
  for(unsigned n=0;n<5;++n){setup(0,0,true);int r=compare(n,16);if(r)return 40+r;}
 }
 test_set_mxcsr(oldMx);
 const char full[]="resize: full mapped differential cases passed\n";
 const char partial[]="resize: core differential cases passed; full hash tests require fixed data mappings\n";
 if(mapped)test_write(full,sizeof full-1);else test_write(partial,sizeof partial-1);
 return 0;
}
