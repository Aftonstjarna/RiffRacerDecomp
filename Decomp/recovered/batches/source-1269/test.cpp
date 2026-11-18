#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_script_gc_finalize_one(State*);
extern "C" void __attribute__((regparm(3))) original_script_call_with_depth_guard(uint32_t, Value*, State*, int);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs[8];
namespace riff { void invoke_finalizer(State* s, Value* f, int n) { original_script_call_with_depth_guard(0,f,s,n); } }
static unsigned called, observed;
extern "C" int finalizer(State* s) {
 ++called;
 Global* g=s->global;
 if (!s->allow_hook && g->threshold==g->total*2 && s->top[ -1 ].tag==7) observed=1;
 return -1; // accepted pre-call returns directly, avoiding unrelated VM execution.
}
struct Fixture {
 State state; Global global; Object objects[3]; Object* roots; Table table; Node node; String name;
 Value stack[32]; uint8_t frames[48]; uint8_t closure[24];
};
static void fill(void* p, unsigned n, uint8_t v) { uint8_t* q=(uint8_t*)p; while(n--) *q++=v; }
static void put(void* p,unsigned off,uintptr_t v) { *(uint32_t*)((uint8_t*)p+off)=uint32_t(v); }
static bool equal(const void* a,const void* b,unsigned n) { const uint8_t* x=(const uint8_t*)a; const uint8_t* y=(const uint8_t*)b; while(n--) if(*x++!=*y++) return false; return true; }
static void setup(Fixture& f,unsigned c) {
 fill(&f,sizeof f,0x5a);
 f.state.global=&f.global; f.state.top=f.stack; f.state.allow_hook=0xa7;
 f.global.pending=&f.objects[0]; f.objects[0].next=(c&1)?&f.objects[1]:&f.objects[0]; f.objects[1].next=&f.objects[0];
 f.roots=&f.objects[2]; f.global.root_link=&f.roots; f.global.current_white=uint8_t(c>>1); f.global.threshold=0x87654321; f.global.total=0x1234;
 Object* o=f.objects[0].next; o->marked=uint8_t(0xff-(c&7)); o->metatable=(c%5==0)?0:&f.table;
 f.table.absent=(c%5==1)?0x84:0x80; f.table.exponent=0; f.table.nodes=&f.node; f.name.hash=0x12345678; f.global.finalizer_name=&f.name;
 f.node.key=&f.name; f.node.key_tag=4; f.node.next=0; f.node.value.tag=(c%5==2)?0:6; f.node.value.payload=uint32_t((uintptr_t)f.closure);
 // C closure and call frame for the accepted pre-call's direct native path.
 f.closure[6]=1; put(f.closure,0x10,(uintptr_t)&finalizer);
 put(&f.state,0x14,(uintptr_t)f.frames); put(&f.state,0x18,0x11223344); put(&f.state,0x1c,(uintptr_t)(f.stack+32)); put(&f.state,0x20,(uintptr_t)f.stack); put(&f.state,0x24,(uintptr_t)(f.frames+24));
 *(uint16_t*)((uint8_t*)&f.state+0x34)=0; *((uint8_t*)&f.state+0x38)=0;
}
extern "C" int test_main() {
 fs[0]=0x13579bdf; if(test_install_fs(fs)) return 1;
 for(unsigned c=0;c<40;c++) {
  Fixture f, initial, original; setup(f,c); initial=f; called=observed=0;
  original_script_gc_finalize_one(&f.state); if(test_get_fs_head()!=fs[0]) return 2;
  unsigned calls=called, obs=observed; original=f; f=initial; called=observed=0;
  f.state.finalize_one();
  if(!equal(&f,&original,sizeof f) || called!=calls || observed!=obs) return 3;
  bool active=c%5>=3;
  if(calls!=unsigned(active) || obs!=unsigned(active)) return 4;
  Object* o=(c&1)?&f.objects[1]:&f.objects[0];
  if(f.roots!=o || o->next!=&f.objects[2] || f.global.pending!=((c&1)?&f.objects[0]:0)) return 5;
  if(f.state.allow_hook!=0xa7 || f.global.threshold!=0x87654321) return 6;
 }
 return 0;
}
extern "C" void* memcpy(void* d,const void* s, size_t n) { uint8_t* a=(uint8_t*)d; const uint8_t* b=(const uint8_t*)s; for(size_t i=0;i<n;++i) a[i]=b[i]; return d; }
