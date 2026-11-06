#include "impl.hpp"
extern "C" uint64_t __attribute__((stdcall)) original_unsigned64_remainder(uint64_t, uint64_t);
extern "C" void test_write(const char*, unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsStorage[4] = {0xffffffffu, 0, 0, 0};

// Independent bit-at-a-time mathematical remainder, with overflow handled
// explicitly. No compiler 64-bit division runtime or dependency on recovery.
static uint64_t mathematical_remainder(uint64_t n, uint64_t d) {
    uint64_t r = 0;
    for (unsigned i = 64; i; --i) {
        const bool overflow = (r >> 63) != 0;
        r = (r << 1) | ((n >> (i - 1)) & 1u);
        if (overflow || r >= d) r -= d;
    }
    return r;
}
static bool check(uint64_t n, uint64_t d) {
    struct Guarded { uint32_t before; uint64_t n, d; uint32_t after; };
    volatile Guarded inputs = {0x13579bdfu, n, d, 0x2468ace0u};
    const unsigned mxcsr = test_get_mxcsr();
    const uint64_t original = original_unsigned64_remainder(inputs.n, inputs.d);
    if (test_get_mxcsr() != mxcsr || test_get_fs_head() != fsStorage[0]) return false;
    const uint64_t recovered = recovered_unsigned64_remainder(inputs.n, inputs.d);
    return original == recovered && recovered == mathematical_remainder(n, d)
        && recovered < d && inputs.n == n && inputs.d == d
        && inputs.before == 0x13579bdfu && inputs.after == 0x2468ace0u
        && test_get_mxcsr() == mxcsr && test_get_fs_head() == fsStorage[0];
}
static uint32_t random_word(uint32_t& state) {
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}
extern "C" int test_main() {
    if (test_install_fs(fsStorage) != 0) return 7;
    if (test_get_fs_head() != fsStorage[0]) return 8;
    const uint64_t values[] = {0, 1, 2, 3, 7, 0x7fffffffULL,
        0x80000000ULL, 0xfffffffeULL, 0xffffffffULL, 0x100000000ULL,
        0x100000001ULL, 0x100000003ULL, 0x1ffffffffULL,
        0x7fffffffffffffffULL, 0x8000000000000000ULL,
        0x8000000000000001ULL, 0xfffffffffffffffeULL, 0xffffffffffffffffULL};
    const unsigned count = sizeof(values) / sizeof(values[0]);
    for (unsigned i = 0; i < count; ++i)
        for (unsigned j = 1; j < count; ++j)
            if (!check(values[i], values[j])) return 1;
    // Every normalization length, including quotient correction and product
    // overflow cases such as (2^64-1) % (2^32+3).
    for (unsigned bit = 0; bit < 64; ++bit) {
        const uint64_t d = uint64_t(1) << bit;
        if (!check(~uint64_t(0), d) || !check(d - 1, d)
            || !check(d, d) || !check(d + 1, d)) return 2;
        if (d > 1 && !check(~uint64_t(0), d - 1)) return 3;
        if (!check(~uint64_t(0), d + 1)) return 4;
    }
    uint32_t state = 0x72696666u;
    for (unsigned i = 0; i < 50000; ++i) {
        uint64_t n = uint64_t(random_word(state)) << 32;
        n |= random_word(state);
        uint64_t d = uint64_t(random_word(state)) << 32;
        d |= random_word(state);
        if (!check(n, d ? d : 1)) return 5;
        const uint32_t narrow = random_word(state) | 1u;
        if (!check(n, narrow)) return 6;
    }
    test_write("unsigned64-remainder: PASS\n", 27);
    return 0;
}
