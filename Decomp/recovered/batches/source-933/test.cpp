#include "impl.hpp"
extern "C" uint32_t __attribute__((cdecl)) original_audio_memory_seek_callback(AudioMemoryState*, int32_t, int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct GuardedState { uint32_t before; AudioMemoryState state; uint32_t after[4]; };
static void fill(GuardedState& s, uint32_t length, uint32_t position) {
    s.before = 0x12345678u;
    for (unsigned i=0;i<sizeof(s.state.opaque);++i) s.state.opaque[i]=static_cast<uint8_t>(i*37+11);
    s.state.length=length; s.state.position=position;
    for (unsigned i=0;i<4;++i) s.after[i]=0xdead0000u+i;
}
static bool equal(const GuardedState& a, const GuardedState& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(GuardedState& a, GuardedState& b, int32_t d, int32_t o) {
    GuardedState expected; fill(expected,a.state.length,a.state.position);
    uint32_t p=a.state.position;
    if(o==0) p=static_cast<uint32_t>(d);
    if(o==1) p+=static_cast<uint32_t>(d);
    if(o==2) p=a.state.length+static_cast<uint32_t>(d);
    expected.state.position=p;
    const uint32_t original=original_audio_memory_seek_callback(&a.state,d,o);
    if(test_get_fs_head()!=0x13579bdfu) return 1;
    const uint32_t recovered=audio_memory_seek_callback(&b.state,d,o);
    if(original!=p || recovered!=original || !equal(a,b) || !equal(a,expected)) return 2;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs_storage[8]={0x13579bdfu,0,0,0,0,0,0,0};
    if(test_install_fs(fs_storage)!=0) return 10;
    const uint32_t values[]={0,1,127,128,4096,0x7fffffffu,0x80000000u,0xffffffffu};
    const int32_t offsets[]={0,1,-1,127,-128,4097,2147483647,(-2147483647-1)};
    const int32_t origins[]={0,1,2,3,-1,2147483647,(-2147483647-1)};
    for(unsigned l=0;l<8;++l) for(unsigned p=0;p<8;++p)
    for(unsigned d=0;d<8;++d) for(unsigned o=0;o<7;++o) {
        GuardedState a,b; fill(a,values[l],values[p]); fill(b,values[l],values[p]);
        if(check(a,b,offsets[d],origins[o])) return 20;
    }
    GuardedState a,b; fill(a,128,0); fill(b,128,0);
    // End query, seek back from end, reset, underflow and unknown-origin query.
    const int32_t ds[]={0,-128,0,-1,1,0,2147483647,1};
    const int32_t os[]={2,2,0,1,1,-1,0,1};
    for(unsigned i=0;i<8;++i) if(check(a,b,ds[i],os[i])) return 30;
    return 0;
}
