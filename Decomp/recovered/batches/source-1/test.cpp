#include "impl.hpp"
extern "C" void __attribute__((cdecl)) original_narrow_inline_swap(void*, void*);
extern "C" void test_write(const char*, unsigned);

static unsigned char recovered[128], reference[128], before[128];
static void initialize(unsigned seed) {
    for (unsigned i=0; i<128; ++i) {
        unsigned char v = static_cast<unsigned char>((i*73u + seed*29u) ^ (i>>1));
        recovered[i]=reference[i]=before[i]=v;
    }
}
static bool compare(unsigned a, unsigned b) {
    narrow_inline_swap(recovered+a,recovered+b);
    original_narrow_inline_swap(reference+a,reference+b);
    for(unsigned i=0;i<128;++i) {
        if(recovered[i]!=reference[i]) return false;
        if (!(i>=a && i<a+16) && !(i>=b && i<b+16)
            && recovered[i]!=before[i]) return false;
    }
    // Disjoint operands must exchange every byte; guards include the size
    // and capacity fields following each 16-byte inline storage region.
    if(a+16<=b || b+16<=a)
        for(unsigned i=0;i<16;++i)
            if(recovered[a+i]!=before[b+i] || recovered[b+i]!=before[a+i]) return false;
    return true;
}
extern "C" int test_main() {
    // Every overlap displacement in both directions, unaligned operands,
    // identical pointers, adjacent and disjoint regions, diverse byte values.
    for(unsigned seed=0;seed<8;++seed)
        for(unsigned a=16;a<=48;++a)
            for(unsigned b=16;b<=48;++b) {
                initialize(seed);
                if(!compare(a,b)) return 1;
            }
    initialize(13);
    if(!compare(8,80)) return 2;
    // No-access paths: invalid pointers are intentional and never dereferenced.
    using Address = __UINTPTR_TYPE__;
    const Address maximum = ~Address(0);
    void* equal_values[] = {nullptr, reinterpret_cast<void*>(Address(1)),
                           reinterpret_cast<void*>(maximum)};
    for(void* p: equal_values) {
        narrow_inline_swap(p,p);
        original_narrow_inline_swap(p,p);
    }
    for(unsigned i=0;i<128;++i) before[i]=recovered[i];
    for(unsigned distance=0;distance<16;++distance) {
        void* p=reinterpret_cast<void*>(maximum-distance);
        narrow_inline_swap(p,recovered+32);
        original_narrow_inline_swap(p,reference+32);
    }
    for(unsigned i=0;i<128;++i)
        if(recovered[i]!=reference[i] || recovered[i]!=before[i]) return 3;
    const char message[]="narrow-inline-swap: all comparisons passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
