#include "impl.hpp"
extern "C" Matrix64* __attribute__((thiscall)) original_matrix64_copy(Matrix64*, const void*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);

// Freestanding backing also lets all offsets be unaligned, including both
// directions of overlap. Entire arenas are compared, not only destinations.
static uint8_t actual[256], oracle[256], expected[256];
static int run(unsigned dst, unsigned src, unsigned seed) {
    for (unsigned i = 0; i < 256; ++i) {
        uint8_t v = static_cast<uint8_t>((i * 73u + seed * 29u) ^ (i >> 1) ^ seed);
        actual[i] = oracle[i] = expected[i] = v;
    }
    for (unsigned b = 0; b < 64; b += 16) {
        uint8_t temp[16];
        for (unsigned i = 0; i < 16; ++i) temp[i] = expected[src+b+i];
        for (unsigned i = 0; i < 16; ++i) expected[dst+b+i] = temp[i];
    }
    unsigned csr = test_get_mxcsr();
    Matrix64* o = original_matrix64_copy(reinterpret_cast<Matrix64*>(oracle+dst), oracle+src);
    if (o != reinterpret_cast<Matrix64*>(oracle+dst) || test_get_mxcsr() != csr) return 1;
    Matrix64* a = reinterpret_cast<Matrix64*>(actual+dst)->copy_from(actual+src);
    if (a != reinterpret_cast<Matrix64*>(actual+dst) || test_get_mxcsr() != csr) return 2;
    for (unsigned i = 0; i < 256; ++i)
        if (actual[i] != oracle[i] || actual[i] != expected[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    unsigned saved = test_get_mxcsr();
    // Masked exceptions, sticky flags, rounding modes, FTZ/DAZ: copying must
    // preserve all bits and treat every input byte as opaque, including NaNs.
    const unsigned modes[] = {0x1f80u, 0x1fbfu, 0x3f80u, 0x5f80u, 0x7f80u, 0x9fc0u};
    for (unsigned m = 0; m < sizeof(modes)/sizeof(modes[0]); ++m) {
        test_set_mxcsr(modes[m]);
        for (unsigned src = 32; src < 48; ++src)
            for (unsigned dst = 0; dst <= 176; ++dst) {
                int result = run(dst, src, m * 17 + src);
                if (result) { test_set_mxcsr(saved); return result; }
            }
    }
    test_set_mxcsr(saved);
    test_write("matrix64-copy passed\n", 21);
    return 0;
}
