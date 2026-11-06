#include "impl.hpp"
extern "C" uint64_t __attribute__((stdcall)) original_unsigned64_divide(uint64_t, uint64_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_write(const char*, unsigned);

static uint32_t fsStorage[8];
static uint32_t state = 0x782fa149u;
static uint32_t random32() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}
static uint64_t random64() {
    const uint64_t high = random32();
    return (high << 32) | random32();
}
// Independent restoring division, including the overflow bit of the remainder.
static uint64_t expected(uint64_t n, uint64_t d) {
    uint64_t q = 0, r = 0;
    for (unsigned i = 64; i != 0; --i) {
        const bool carry = (r >> 63) != 0;
        r = (r << 1) | ((n >> (i - 1)) & 1u);
        if (carry || r >= d) {
            r -= d;
            q |= static_cast<uint64_t>(1) << (i - 1);
        }
    }
    return q;
}
static int check(uint64_t n, uint64_t d) {
    // There are no pointer arguments or object fields. Check caller-owned
    // input storage and nearby canaries, as well as TLS and floating state.
    volatile uint64_t words[4];
    words[0] = UINT64_C(0x123456789abcdef0);
    words[1] = n;
    words[2] = d;
    words[3] = UINT64_C(0xfedcba9876543210);
    const unsigned mxcsr = test_get_mxcsr();
    const uint64_t oracle = original_unsigned64_divide(words[1], words[2]);
    if (test_get_fs_head() != 0x13579bdfu) return 1;
    if (test_get_mxcsr() != mxcsr) return 2;
    const uint64_t actual = recovered_unsigned64_divide(words[1], words[2]);
    if (oracle != actual || actual != expected(n, d)) return 3;
    if (words[0] != UINT64_C(0x123456789abcdef0) || words[1] != n ||
        words[2] != d || words[3] != UINT64_C(0xfedcba9876543210)) return 4;
    for (unsigned i = 1; i != 8; ++i)
        if (fsStorage[i] != (0x11223300u + i)) return 5;
    return 0;
}
extern "C" int test_main() {
    fsStorage[0] = 0x13579bdfu;
    for (unsigned i = 1; i != 8; ++i) fsStorage[i] = 0x11223300u + i;
    if (test_install_fs(fsStorage) != 0) return 10;
    const uint64_t values[] = {
        0, 1, 2, 3, 7, 15, 16, 17, 0x7fffffffu, 0x80000000u,
        0xfffffffeu, 0xffffffffu, UINT64_C(0x100000000),
        UINT64_C(0x100000001), UINT64_C(0x1ffffffff),
        UINT64_C(0x7fffffffffffffff), UINT64_C(0x8000000000000000),
        UINT64_C(0xffffffff00000000), UINT64_C(0xfffffffffffffffe),
        UINT64_C(0xffffffffffffffff)
    };
    for (unsigned i = 0; i != sizeof(values)/sizeof(values[0]); ++i)
        for (unsigned j = 1; j != sizeof(values)/sizeof(values[0]); ++j) {
            const int error = check(values[i], values[j]);
            if (error) return 20 + error;
        }
    // Every normalization length, power boundaries, and one-off quotients.
    for (unsigned bit = 0; bit != 64; ++bit) {
        const uint64_t power = static_cast<uint64_t>(1) << bit;
        for (unsigned offset = 0; offset != 3; ++offset) {
            const uint64_t d = power + offset - 1;
            if (!d) continue;
            const uint64_t ns[] = { d - 1, d, d + 1, ~static_cast<uint64_t>(0) };
            for (unsigned k = 0; k != 4; ++k) {
                const int error = check(ns[k], d);
                if (error) return 30 + error;
            }
        }
    }
    // Explicit overestimated quotient with carry, and comparison corrections.
    if (check(UINT64_C(0xffffffffffffffff), UINT64_C(0x100000003))) return 40;
    if (check(UINT64_C(0x100000000), UINT64_C(0x100000001))) return 41;
    if (check(UINT64_C(0x200000000), UINT64_C(0x100000001))) return 42;
    for (unsigned i = 0; i != 30000; ++i) {
        const uint64_t n = random64();
        uint64_t d = random64();
        if ((i & 3u) == 0) d = random32();
        if (!d) d = 1;
        const int error = check(n, d);
        if (error) return 50 + error;
    }
    test_write("unsigned64-divide: passed\n", 26);
    return 0;
}
