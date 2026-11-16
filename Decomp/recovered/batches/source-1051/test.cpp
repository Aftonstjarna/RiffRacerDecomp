#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_record12_capacity_growth(const Record12Vector*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
static int check(uint32_t begin, uint32_t end, uint32_t cap, uint32_t minimum) {
    struct Guarded { uint32_t before; Record12Vector v; uint32_t after; };
    Guarded a = {0x12345678u, {begin,end,cap}, 0x87654321u};
    Guarded b = a;
    const uint32_t result = original_record12_capacity_growth(&a.v, minimum);
    if (test_get_fs_head() != fs_storage[0]) return 1;
    const uint32_t recovered = b.v.capacity_growth(minimum);
    if (result != recovered) return 2;
    if (a.before != 0x12345678u || a.after != 0x87654321u ||
        b.before != a.before || b.after != a.after) return 3;
    if (a.v.begin != begin || a.v.end != end || a.v.capacity_end != cap ||
        b.v.begin != begin || b.v.end != end || b.v.capacity_end != cap) return 4;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 10;
    const uint32_t minima[] = {0,1,2,3,7,12,100,0x15555554u,0x15555555u,0x15555556u,0x7fffffffu,0x80000000u,0xffffffffu};
    const uint32_t deltas[] = {0,1,11,12,13,23,24,36,48,120,12000,0x7fffffffu,0x80000000u,0x80000001u,0xfffffff3u,0xfffffff4u,0xfffffff5u,0xffffffffu};
    const uint32_t bases[] = {0,0x1000u,0x7fffffffu,0xfffffff0u};
    for (unsigned b=0;b<4;++b) for (unsigned d=0;d<sizeof(deltas)/sizeof(deltas[0]);++d)
        for (unsigned m=0;m<sizeof(minima)/sizeof(minima[0]);++m) {
            int r=check(bases[b],0xdeadbeefu,bases[b]+deltas[d],minima[m]);
            if(r) return 20+r;
        }
    // Valid 12-byte records: odd/even rounding and minimum selection.
    for (uint32_t n=0;n<2048;++n) {
        uint32_t expected=n+n/2;
        Record12Vector v={0x1000u,0x1000u+n*12,0x1000u+n*12};
        if(v.capacity_growth(0)!=expected) return 30;
        for(uint32_t m=0;m<3;++m) {
            int r=check(v.begin,v.end,v.capacity_end,expected+m);
            if(r) return 40+r;
        }
    }
    uint32_t random=0x92e13807u;
    for(unsigned i=0;i<20000;++i) {
        random=random*1664525u+1013904223u; uint32_t begin=random;
        random=random*1664525u+1013904223u; uint32_t cap=random;
        random=random*1664525u+1013904223u; uint32_t minimum=random;
        int r=check(begin,~random,cap,minimum); if(r) return 50+r;
    }
    return 0;
}
