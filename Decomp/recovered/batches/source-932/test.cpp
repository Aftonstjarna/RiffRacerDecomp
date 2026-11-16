#include "impl.hpp"
using namespace riff;
extern "C" uint32_t __attribute__((fastcall)) original_script_call_result_finish(ScriptState*, ScriptValue*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0; i<n; ++i) a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d, int v, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    for (unsigned i=0; i<n; ++i) a[i]=static_cast<unsigned char>(v);
    return d;
}
static unsigned unexpected_hooks;
namespace riff {
// Link-only test dependency. Hook bit 1 is always clear in oracle comparisons;
// this callback is not evidence for original return-hook behavior.
ScriptValue* RIFF_FASTCALL script_return_hook(ScriptState*, ScriptValue* p) {
    ++unexpected_hooks;
    return p;
}
}
struct Fixture {
    ScriptState state;
    ScriptCallInfo frames[3];
    ScriptValue slots[64];
    uint32_t guard[8];
};
static Fixture live;
static unsigned char initial[sizeof(Fixture)], oracle[sizeof(Fixture)];
static uint32_t fs_storage[16];
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int run(uint32_t count, unsigned available, unsigned source,
               unsigned destination, unsigned beyond, unsigned flags) {
    // Pattern every byte, including unknown state fields and frame/stack guards.
    unsigned char* bytes=reinterpret_cast<unsigned char*>(&live);
    for(unsigned i=0;i<sizeof(live);++i) bytes[i]=static_cast<unsigned char>(i*37u+91u);
    for(unsigned i=0;i<64;++i) {
        live.slots[i].payload=0xa0000000u+i*0x10203u;
        live.slots[i].tag=0x70000000u+i;
    }
    live.frames[0].base=&live.slots[3];
    live.frames[0].saved_pc=0x1234abcd;
    live.frames[1].function=&live.slots[destination];
    live.frames[1].requested_results=count;
    live.state.call_info=&live.frames[1];
    live.state.base=&live.slots[37];
    live.state.top=&live.slots[source+available-beyond];
    live.state.hook_mask=static_cast<uint8_t>(flags);
    memcpy(initial,&live,sizeof(live));
    uint32_t result=original_script_call_result_finish(&live.state,&live.slots[source]);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    memcpy(oracle,&live,sizeof(live));
    if(result!=count+1u || live.state.call_info!=&live.frames[0] ||
       live.state.base!=&live.slots[3] || live.state.saved_pc!=0x1234abcd) return 2;
    unsigned copies=available;
    if(beyond) copies=0;
    if((count&0x80000000u)==0 && copies>count) copies=count;
    unsigned produced=(count&0x80000000u) ? copies : count;
    if(live.state.top!=&live.slots[destination+produced]) return 3;
    // Nil padding must keep the payload at its previous value. These checks
    // use separate source/destination ranges; overlap is checked by full diff.
    if(destination+produced<=source && produced>copies) {
        for(unsigned i=copies;i<produced;++i) {
            if(live.slots[destination+i].tag!=0 ||
               live.slots[destination+i].payload!=0xa0000000u+(destination+i)*0x10203u) return 4;
        }
    }
    memcpy(&live,initial,sizeof(live));
    uint32_t recovered=live.state.finish_results(&live.slots[source]);
    if(recovered!=result || !equal(&live,oracle,sizeof(live))) return 5;
    if(unexpected_hooks) return 6;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0xdeadbeefu;
    if(test_install_fs(fs_storage)!=0) return 10;
    // Disjoint ranges, exact alias, both overlap directions, adjacent ranges.
    const unsigned destinations[]={0,12,19,20,21,24,32};
    const unsigned masks[]={0,1,4,0xfd};
    for(unsigned m=0;m<4;++m)
      for(unsigned d=0;d<7;++d)
        for(unsigned available=0;available<=12;++available)
          for(unsigned count=0;count<=12;++count) {
            int e=run(count,available,20,destinations[d],0,masks[m]);
            if(e) return 20+e;
          }
    const uint32_t negative[]={0xffffffffu,0xfffffffeu,0xfffffff0u};
    for(unsigned d=0;d<7;++d)
      for(unsigned n=0;n<3;++n)
        for(unsigned available=0;available<=12;++available) {
            int e=run(negative[n],available,20,destinations[d],0,0);
            if(e) return 30+e;
        }
    // first_result strictly past top: comparison is unsigned, no source read.
    for(unsigned count=0;count<=12;++count) {
        int e=run(count,0,20,0,1,0);
        if(e) return 40+e;
    }
    if(run(0x80000000u,0,20,0,0,0)) return 50;
    static const char message[]="script-call-result-finish: 5019 comparisons passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
