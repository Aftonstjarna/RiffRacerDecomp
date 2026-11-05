#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_record24_growth_capacity(const Record24Storage*, uint32_t);
extern "C" void test_write(const char*, unsigned);
struct Guarded { uint32_t before; Record24Storage value; uint32_t after; };
static int check(uint32_t begin, uint32_t distance, uint32_t required, uint32_t middle) {
    Guarded a = {0x12345678u, {begin, middle, begin + distance}, 0x87654321u};
    Guarded b = a;
    const uint32_t expected = original_record24_growth_capacity(&a.value, required);
    const uint32_t actual = b.value.growth_capacity(required);
    if (expected != actual) return 1;
    if (a.before != 0x12345678u || b.before != a.before ||
        a.after != 0x87654321u || b.after != a.after) return 2;
    if (a.value.begin != begin || a.value.end != middle ||
        a.value.allocation_end != begin + distance ||
        b.value.begin != a.value.begin || b.value.end != middle ||
        b.value.allocation_end != a.value.allocation_end) return 3;
    return 0;
}
extern "C" int test_main() {
    const uint32_t distances[] = {0,1,23,24,25,47,48,72,96,
        0x7fffffffu,0x80000000u,0x80000001u,0xffffffe7u,0xffffffe8u,0xffffffffu};
    const uint32_t requests[] = {0,1,2,3,4,10,0x0aaaaaa9u,0x0aaaaaaau,
        0x0aaaaaabu,0x7fffffffu,0x80000000u,0xffffffffu};
    const uint32_t starts[] = {0,0x1000u,0x80000000u,0xfffffff0u};
    for (unsigned s=0;s<4;++s)
        for (unsigned d=0;d<sizeof(distances)/sizeof(distances[0]);++d)
            for (unsigned r=0;r<sizeof(requests)/sizeof(requests[0]);++r)
                if (check(starts[s],distances[d],requests[r],0xdeadbeefu)) return 10;
    // Branch threshold: c+floor(c/2) <= max. Neighboring capacities and
    // unaligned distances check truncation, both growth paths and odd rounding.
    const uint32_t threshold = 0x0aaaaaaau / 3u * 2u;
    for (uint32_t c=threshold-4;c<=threshold+4;++c)
        for (uint32_t extra=0;extra<24;++extra)
            for (unsigned r=0;r<sizeof(requests)/sizeof(requests[0]);++r)
                if (check(0x70000000u,c*24u+extra,requests[r],0)) return 11;
    uint32_t state=0xc001d00du;
    for (unsigned i=0;i<20000;++i) {
        state=state*1664525u+1013904223u; uint32_t begin=state;
        state=state*1664525u+1013904223u; uint32_t distance=state;
        state=state*1664525u+1013904223u;
        if (check(begin,distance,state,state^0xabcdef01u)) return 12;
    }
    // Independent landmarks supplement differential comparison.
    Record24Storage v={0,0,72};
    if (v.growth_capacity(0)!=4 || v.growth_capacity(7)!=7) return 13;
    v.allocation_end=(threshold+2)*24u;
    if (v.growth_capacity(0)!=0) return 14;
    test_write("record24 growth: all checks passed\n",35);
    return 0;
}
