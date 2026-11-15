#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_script_throw_status(riff::ScriptState*, int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
namespace {
struct StateBox { uint32_t before[4]; riff::ScriptState state; uint32_t after[4]; };
struct GlobalBox { uint32_t before[4]; riff::ScriptGlobal global; uint32_t after[4]; };
void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) b[i] = static_cast<unsigned char>(seed + i*37);
}
void copy(void* dst, const void* src, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (unsigned i=0; i<n; ++i) d[i]=s[i];
}
bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
int run(int32_t code, unsigned seed) {
    GlobalBox global, savedGlobal;
    StateBox actual, recovered, expected;
    fill(&global,sizeof(global),seed+13);
    global.global.panic=0;
    copy(&savedGlobal,&global,sizeof(global));
    fill(&actual,sizeof(actual),seed);
    actual.state.global=&global.global;
    actual.state.errorJump=0;
    copy(&recovered,&actual,sizeof(actual));
    copy(&expected,&actual,sizeof(actual));
    expected.state.status=static_cast<uint8_t>(code);
    const unsigned head=test_get_fs_head();
    original_script_throw_status(&actual.state,code);
    if(test_get_fs_head()!=head) return 1;
    riff::scriptThrowStatus(&recovered.state,code);
    if(!equal(&actual,&recovered,sizeof(actual))) return 2;
    // Independently require exactly one byte to change, including all padding,
    // pointer fields and surrounding canaries; global must remain untouched.
    if(!equal(&actual,&expected,sizeof(actual))) return 3;
    if(!equal(&global,&savedGlobal,sizeof(global))) return 4;
    return 0;
}
}
extern "C" int test_main() {
    uint32_t fsStorage[8];
    fill(fsStorage,sizeof(fsStorage),0);
    fsStorage[0]=0xffffffffu;
    if(test_install_fs(fsStorage)!=0) return 10;
    if(test_get_fs_head()!=0xffffffffu) return 11;
    // All low-byte outputs, with varied original contents and nonzero high bits.
    for(unsigned i=0;i<256;++i) {
        int r=run(static_cast<int32_t>(i),i); if(r) return 20+r;
        r=run(static_cast<int32_t>(0x12340000u+i),255-i); if(r) return 30+r;
        r=run(-1-static_cast<int32_t>(i),i*19); if(r) return 40+r;
    }
    const int32_t edges[]={-2147483647-1,2147483647,256,-256,65536,-65536};
    for(unsigned i=0;i<sizeof(edges)/sizeof(edges[0]);++i) {
        int r=run(edges[i],i*61); if(r) return 50+r;
    }
    test_write("script-throw-status: 774 differential cases passed\n",51);
    return 0;
}
