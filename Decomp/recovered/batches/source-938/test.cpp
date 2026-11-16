#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_audio_backend_reset(AudioBackendState*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
static uint32_t fsStorage[8];
struct Guarded { uint32_t front[4]; AudioBackendState object; uint32_t back[4]; };
static Guarded a,b,before;
static uint32_t seed=0x173aac29u;
static uint8_t randomByte() { seed^=seed<<13; seed^=seed>>17; seed^=seed<<5; return static_cast<uint8_t>(seed); }
static bool changed(unsigned offset) {
    return (offset>=0x6d3c && offset<0x6d44) ||
           (offset>=0x6d50 && offset<0x6d54) ||
           (offset>=0x6d7c && offset<0x6d94);
}
static int check() {
    a.object.reset();
    original_audio_backend_reset(&b.object);
    if(test_get_fs_head()!=fsStorage[0]) return 1;
    const uint8_t* x=reinterpret_cast<const uint8_t*>(&a);
    const uint8_t* y=reinterpret_cast<const uint8_t*>(&b);
    const uint8_t* z=reinterpret_cast<const uint8_t*>(&before);
    for(unsigned i=0;i<sizeof(a);++i) {
        if(x[i]!=y[i]) return 2;
        if((i<16 || i>=16+sizeof(AudioBackendState) || !changed(i-16)) && x[i]!=z[i]) return 3;
    }
    if(a.object.backendTableAddress!=0xbaf470u || a.object.state6d40!=-1 ||
       a.object.state6d50 || a.object.state6d7c || a.object.state6d80 ||
       a.object.state6d84 || a.object.state6d88 || a.object.state6d8c || a.object.state6d90) return 4;
    return 0;
}
extern "C" int test_main() {
    fsStorage[0]=0xffffffffu;
    if(test_install_fs(fsStorage)!=0) return 5;
    for(unsigned pattern=0;pattern<260;++pattern) {
        uint8_t* x=reinterpret_cast<uint8_t*>(&a);
        uint8_t* y=reinterpret_cast<uint8_t*>(&b);
        uint8_t* z=reinterpret_cast<uint8_t*>(&before);
        for(unsigned i=0;i<sizeof(a);++i) {
            uint8_t value=pattern<256 ? static_cast<uint8_t>(pattern) :
                pattern==256 ? static_cast<uint8_t>(i) : pattern==257 ? static_cast<uint8_t>(~i) : randomByte();
            x[i]=y[i]=z[i]=value;
        }
        int result=check(); if(result) return result;
        // Reset again without reinitialization to verify idempotence.
        result=check(); if(result) return result;
    }
    test_write("audio-backend-reset: passed\n",28);
    return 0;
}
