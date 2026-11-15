#include "impl.hpp"
// Original uses ECX and EDX, not stack-based thiscall arguments.
extern "C" bool __attribute__((fastcall)) original_object_flags_channel_enabled(const ObjectFlags*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static ObjectFlags object;
static uint8_t saved[sizeof(ObjectFlags)];
static int check(uint32_t channel) {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&object);
    for (unsigned i=0;i<sizeof(object);++i) saved[i]=bytes[i];
    bool expected = (object.flags & 7u) == 7u &&
        (object.channel_mask & (uint32_t(1) << (channel & 31u))) != 0;
    bool actual = original_object_flags_channel_enabled(&object, channel);
    if (actual != expected) return 1;
    for (unsigned i=0;i<sizeof(object);++i) if (bytes[i]!=saved[i]) return 2;
    if (object.channel_enabled(channel) != actual) return 3;
    for (unsigned i=0;i<sizeof(object);++i) if (bytes[i]!=saved[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&object);
    for (unsigned i=0;i<sizeof(object);++i) bytes[i]=uint8_t(i*73u+19u);
    const uint32_t channels[] = {0,1,7,15,30,31,32,33,63,64,255,256,257,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
    for (unsigned f=0;f<256;++f) {
        object.flags=uint8_t(f);
        for (unsigned m=0;m<36;++m) {
            object.channel_mask = m<32 ? uint32_t(1)<<m :
                m==32 ? 0u : m==33 ? 0xffffffffu : m==34 ? 0xaaaaaaaau : 0x55555555u;
            for (unsigned c=0;c<32;++c) {
                int r=check(c); if (r) return r;
            }
            for (unsigned c=0;c<sizeof(channels)/sizeof(channels[0]);++c) {
                int r=check(channels[c]); if (r) return r;
            }
        }
    }
    test_write("object flags tests passed\n",25);
    return 0;
}
