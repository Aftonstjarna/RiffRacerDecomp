#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_wide_set_length(WideString*, uint32_t);
struct Fixture {
    uint32_t before[4];
    WideString value;
    uint32_t after[4];
    uint16_t backing[64];
    uint32_t end[4];
};
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) b[i] = static_cast<unsigned char>((i*37u+seed)%255u+1u);
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for (unsigned i=0; i<n; ++i) if(x[i]!=y[i]) return false;
    return true;
}
static void init(Fixture& f, uint32_t cap, uint32_t old, unsigned seed) {
    fill(&f,sizeof f,seed);
    if(cap>=8) f.value.storage.heap=f.backing+4;
    f.value.length=old;
    f.value.capacity=cap;
}
// Independently check all bytes, including pointer/unused union bytes, guards,
// old terminator and unused backing. Normalize only the fixture-local pointer.
static bool run(uint32_t cap, uint32_t old, uint32_t n, unsigned seed) {
    Fixture actual, oracle, expected;
    init(actual,cap,old,seed); init(oracle,cap,old,seed); init(expected,cap,old,seed);
    expected.value.length=n;
    if(cap>=8) expected.backing[4+n]=0;
    else expected.value.storage.inline_units[n]=0;
    original_wide_set_length(&oracle.value,n);
    actual.value.set_length(n);
    if(cap>=8) {
        if(actual.value.storage.heap!=actual.backing+4 ||
           oracle.value.storage.heap!=oracle.backing+4) return false;
        actual.value.storage.heap=expected.value.storage.heap;
        oracle.value.storage.heap=expected.value.storage.heap;
    }
    return equal(&actual,&oracle,sizeof actual) && equal(&actual,&expected,sizeof actual);
}
extern "C" int test_main() {
    const uint32_t caps[]={0,1,6,7,8,9,31,0x7fffffffu,0x80000000u,0xffffffffu};
    const uint32_t old_lengths[]={0,1,7,31,0x80000000u,0xffffffffu};
    for(unsigned c=0;c<sizeof(caps)/sizeof(caps[0]);++c)
        for(unsigned o=0;o<sizeof(old_lengths)/sizeof(old_lengths[0]);++o)
            for(unsigned n=0;n<(caps[c]<8 ? 8u:56u);++n)
                for(unsigned seed=0;seed<3;++seed)
                    if(!run(caps[c],old_lengths[o],n,seed*83)) return 1;
    return 0;
}
