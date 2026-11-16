#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_audio_bitstream_read16(recovered::AudioBitstream*);
extern "C" void test_write(const char*, unsigned);
static recovered::AudioBitstream actual, expected;
static uint8_t data[260], saved[260];
static uint32_t rng = 0x529b71u;
static uint32_t random_value() { rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng; }
static bool run(uint32_t offset, unsigned index, bool sequence) {
    uint8_t* a = reinterpret_cast<uint8_t*>(&actual);
    uint8_t* e = reinterpret_cast<uint8_t*>(&expected);
    for (unsigned i=0; i<sizeof(actual); ++i) a[i]=e[i]=uint8_t(i*37u+offset);
    actual.bit_offset=expected.bit_offset=offset;
    actual.cursor=expected.cursor=data+index;
    for(unsigned iteration=0; iteration<(sequence ? 32u : 1u); ++iteration) {
        uint32_t result=actual.read16();
        uint32_t oracle=original_audio_bitstream_read16(&expected);
        if(result!=oracle || result>65535u) return false;
        for(unsigned i=0; i<sizeof(actual); ++i) if(a[i]!=e[i]) return false;
        // Also independently require all opaque object bytes to stay untouched.
        for(unsigned i=0; i<0x4d4c; ++i) if(a[i]!=uint8_t(i*37u+offset)) return false;
        for(unsigned i=0; i<sizeof(data); ++i) if(data[i]!=saved[i]) return false;
    }
    return true;
}
extern "C" int test_main() {
    const uint32_t edges[]={0,1,7,8,15,16,23,24,31,32,33,255,
        0x7fffffefu,0x7ffffff0u,0x7fffffffu,0x80000000u,
        0xffffffe0u,0xfffffff0u,0xfffffff7u,0xfffffff8u,0xffffffffu};
    for(unsigned pattern=0; pattern<12; ++pattern) {
        for(unsigned i=0; i<sizeof(data); ++i) {
            data[i]=saved[i]= pattern==0 ? 0 : pattern==1 ? 255 :
                pattern==2 ? uint8_t(i) : pattern==3 ? uint8_t(1u<<(i&7)) : uint8_t(random_value());
        }
        for(unsigned bit=0; bit<8; ++bit) {
            if(!run(bit,pattern%4,true)) return 1;
            // Last accessible 3-byte window, including aligned reads.
            if(!run(bit,257,false)) return 2;
        }
        for(unsigned i=0;i<sizeof(edges)/sizeof(edges[0]);++i)
            if(!run(edges[i],1,false)) return 3;
        for(unsigned i=0;i<256;++i)
            if(!run(random_value(),i%4,false)) return 4;
    }
    test_write("read16 oracle checks passed\n",28);
    return 0;
}
