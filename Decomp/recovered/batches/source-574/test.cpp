#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall))
original_u32_vector_growth_capacity(const U32Vector*, uint32_t);
extern "C" void test_write(const char*, unsigned);
struct Guarded { uint32_t before; U32Vector v; uint32_t after; };
static bool check(uint32_t base, uint32_t distance, uint32_t end, uint32_t request) {
    Guarded a = {0x12345678u, {base, end, base + distance}, 0xfedcba98u};
    Guarded b = a;
    uint32_t actual = a.v.growth_capacity(request);
    uint32_t expected = original_u32_vector_growth_capacity(&b.v, request);
    if (actual != expected) return false;
    const uint32_t* ap = reinterpret_cast<const uint32_t*>(&a);
    const uint32_t* bp = reinterpret_cast<const uint32_t*>(&b);
    const uint32_t words[] = {0x12345678u,base,end,base+distance,0xfedcba98u};
    for (unsigned i=0;i<5;++i)
        if(ap[i]!=words[i] || bp[i]!=words[i]) return false;
    return true;
}
extern "C" int test_main() {
    const uint32_t distances[] = {0,1,2,3,4,8,12,16,28,0x1000,
        0x7ffffffc,0x7ffffffd,0x7fffffff,0x80000000,0x80000004,
        0xaaaaaaaa,0xfffffffc,0xfffffffd,0xffffffff};
    const uint32_t requests[] = {0,1,2,3,4,5,6,7,10,0x2aaaaaaa,
        0x3ffffffe,0x3fffffff,0x40000000,0x7fffffff,0x80000000,0xffffffff};
    const uint32_t bases[] = {0,0x10000,0x80000000,0xfffffff0};
    for(unsigned i=0;i<sizeof(distances)/sizeof(distances[0]);++i)
        for(unsigned j=0;j<sizeof(requests)/sizeof(requests[0]);++j)
            for(unsigned k=0;k<4;++k)
                if(!check(bases[k],distances[i],requests[j]^0xdeadbeefu,requests[j])) return 1;
    // Valid small vectors: exercise even/odd capacities and both max branches.
    for(uint32_t cap=0;cap<1024;++cap)
        for(uint32_t request=0;request<1600;request+=17)
            if(!check(0x100000,cap*4,0x100000+cap*2,request)) return 2;
    uint32_t rng=0x76543210u;
    for(unsigned i=0;i<100000;++i) {
        rng=rng*1664525u+1013904223u; uint32_t base=rng;
        rng=rng*1664525u+1013904223u; uint32_t distance=rng;
        rng=rng*1664525u+1013904223u; uint32_t end=rng;
        rng=rng*1664525u+1013904223u;
        if(!check(base,distance,end,rng)) return 3;
    }
    test_write("growth capacity comparisons passed\n",35);
    return 0;
}
