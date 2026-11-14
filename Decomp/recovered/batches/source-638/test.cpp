#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_random_range_inclusive(RiffRandom*, uint32_t, uint32_t);
struct Guarded { uint32_t before[2]; RiffRandom rng; uint32_t after[3]; };
static bool same(const Guarded& a, const Guarded& b) {
    return a.before[0]==b.before[0] && a.before[1]==b.before[1] &&
        a.rng.state==b.rng.state && a.after[0]==b.after[0] &&
        a.after[1]==b.after[1] && a.after[2]==b.after[2];
}
extern "C" int test_main() {
    const uint32_t seeds[] = {0,1,0xffffffffu,0x80000000u,0x7fffffffu,
        0x12345678u,0xdeadbeefu,0x55555555u,0xaaaaaaaau};
    const uint32_t ranges[][2] = {{0,0},{0,1},{0,9},{1,100},
        {0x80000000u,0x80000000u},{0xfffffffeu,0xffffffffu},
        {0x80000000u,0x7ffffffeu},{0,0x7fffffffu},
        {0,0xfffffffeu},{0xfffffff0u,15}, {100,5},
        {0x7fffffffu,0x80000000u}};
    for (unsigned s=0;s<sizeof(seeds)/sizeof(seeds[0]);++s) {
        for(unsigned r=0;r<sizeof(ranges)/sizeof(ranges[0]);++r) {
            Guarded a={{0x13579bdfu,0x2468ace0u},{seeds[s]},
                       {0x11223344u,0xaabbccddu,0x87654321u}};
            Guarded b=a;
            for(unsigned n=0;n<257;++n) {
                uint32_t x=a.rng.inclusive(ranges[r][0],ranges[r][1]);
                uint32_t y=original_random_range_inclusive(&b.rng,ranges[r][0],ranges[r][1]);
                if(x!=y || !same(a,b)) return 1;
                if(a.before[0]!=0x13579bdfu || a.before[1]!=0x2468ace0u ||
                   a.after[0]!=0x11223344u || a.after[1]!=0xaabbccddu ||
                   a.after[2]!=0x87654321u) return 2;
                if(ranges[r][0]<=ranges[r][1] &&
                   (x<ranges[r][0] || x>ranges[r][1])) return 3;
            }
        }
    }
    RiffRandom known={0};
    if(known.inclusive(0,0)!=0 || known.state!=0x73d1e4f4u) return 4;
    return 0;
}
