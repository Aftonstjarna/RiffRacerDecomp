#include "impl.hpp"
extern "C" riff::Record52* original_record52_default_initialize(riff::Record52*)
    __attribute__((thiscall));
extern "C" void test_write(const char*, unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
struct Guarded {
    unsigned char before[16];
    riff::Record52 record;
    unsigned char after[16];
};
static const uint32_t expected[13] = {
    0xbf800000u,0,0,0,0,0,0,0xffffffffu,0,
    0x3f800000u,0x3f800000u,0x3f800000u,0x3f800000u
};
static int run(unsigned seed) {
    Guarded a, b;
    unsigned char* ap = reinterpret_cast<unsigned char*>(&a);
    unsigned char* bp = reinterpret_cast<unsigned char*>(&b);
    for (unsigned i=0; i<sizeof(a); ++i) {
        unsigned char v = static_cast<unsigned char>(seed == 0 ? 0 :
            seed == 1 ? 255 : (i*73 + seed*31));
        ap[i]=v; bp[i]=v;
    }
    if (a.record.initialize() != &a.record) return 1;
    if (original_record52_default_initialize(&b.record) != &b.record) return 2;
    for (unsigned i=0; i<sizeof(a); ++i) {
        if (ap[i] != bp[i]) return 3;
        if (i<16 || i>=68) {
            unsigned char v = static_cast<unsigned char>(seed == 0 ? 0 :
                seed == 1 ? 255 : (i*73 + seed*31));
            if (ap[i] != v) return 4;
        }
    }
    const unsigned char* ep = reinterpret_cast<const unsigned char*>(expected);
    for (unsigned i=0; i<52; ++i) if (ap[16+i] != ep[i]) return 5;
    // Repeat initialization verifies independence of preexisting defaults.
    if (a.record.initialize() != &a.record ||
        original_record52_default_initialize(&b.record) != &b.record) return 6;
    for (unsigned i=0; i<sizeof(a); ++i) if (ap[i] != bp[i]) return 7;
    return 0;
}
extern "C" int test_main() {
    const unsigned saved = test_get_mxcsr();
    for (unsigned mode=0; mode<4; ++mode) {
        const unsigned control = (saved & ~0x6000u) | (mode<<13);
        test_set_mxcsr(control);
        for (unsigned seed=0; seed<258; ++seed) {
            int error=run(seed);
            if (error) { test_set_mxcsr(saved); return error; }
            if (test_get_mxcsr()!=control) { test_set_mxcsr(saved); return 8; }
        }
    }
    test_set_mxcsr(saved);
    test_write("record52 oracle comparison passed\n",34);
    return 0;
}
