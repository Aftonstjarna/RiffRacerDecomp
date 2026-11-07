#include "impl.hpp"
extern "C" void __attribute__((cdecl)) original_byte_widen_terminated(
    uint16_t*, const unsigned char*, uint32_t);
extern "C" void test_write(const char*, unsigned);

static bool separate(unsigned length, uint32_t capacity, unsigned pattern)
{
    unsigned char source[600], before[600];
    uint16_t actual[304], oracle[304];
    for (unsigned i=0; i<600; ++i) {
        source[i] = i < length ? static_cast<unsigned char>(1+(i*73+pattern)%255) : 0;
        before[i] = source[i];
    }
    for (unsigned i=0; i<304; ++i) actual[i]=oracle[i]=0xa55a;
    recovered_byte_widen_terminated(actual+2, source, capacity);
    original_byte_widen_terminated(oracle+2, source, capacity);
    for (unsigned i=0; i<304; ++i) if (actual[i]!=oracle[i]) return false;
    for (unsigned i=0; i<600; ++i) if (source[i]!=before[i]) return false;
    unsigned copied = capacity/2 > 1 ? capacity/2-1 : 0;
    if (copied>length) copied=length;
    for (unsigned i=0; i<304; ++i) {
        uint16_t expected = 0xa55a;
        if (i>=2 && i<2+copied) expected=source[i-2];
        if (i==2+copied) expected=0;
        if (actual[i]!=expected) return false;
    }
    return true;
}

static bool overlap(unsigned source_offset, unsigned destination_offset, uint32_t capacity)
{
    uint16_t actual[64], oracle[64];
    unsigned char* a=reinterpret_cast<unsigned char*>(actual);
    unsigned char* o=reinterpret_cast<unsigned char*>(oracle);
    for (unsigned i=0; i<128; ++i) a[i]=o[i]=static_cast<unsigned char>(1+(i*11)%255);
    a[100]=o[100]=0;
    recovered_byte_widen_terminated(actual+destination_offset,a+source_offset,capacity);
    original_byte_widen_terminated(oracle+destination_offset,o+source_offset,capacity);
    for (unsigned i=0; i<128; ++i) if(a[i]!=o[i]) return false;
    return true;
}
extern "C" int test_main()
{
    const unsigned lengths[]={0,1,2,3,7,254,255,256,511};
    const uint32_t capacities[]={0,1,2,3,4,5,6,7,8,15,16,17,510,511,512,513};
    for (unsigned l=0;l<sizeof(lengths)/sizeof(lengths[0]);++l)
        for (unsigned c=0;c<sizeof(capacities)/sizeof(capacities[0]);++c)
            for (unsigned p=0;p<4;++p)
                if (!separate(lengths[l],capacities[c],p*64)) return 1;
    // Huge unsigned sizes are safe here because the source ends immediately.
    if (!separate(0,0xffffffffu,0) || !separate(1,0x80000000u,0)) return 2;
    for (unsigned s=0;s<12;++s)
        for (unsigned d=0;d<6;++d)
            for (unsigned c=0;c<34;++c)
                if (!overlap(s,d,c)) return 3;
    test_write("byte-widen-terminated: passed\n",30);
    return 0;
}
