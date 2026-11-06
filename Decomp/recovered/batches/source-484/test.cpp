#include "impl.hpp"

// GCC i386 regparm(3) puts these three WORD arguments in EAX, EDX, ECX.
// The uint64_t result is EDX:EAX. This is a register helper, not thiscall
// or stdcall; there are no stack parameters and RET has no pop immediate.
extern "C" uint64_t original_u64_shift_left(uint32_t low, uint32_t high,
                                           uint32_t count)
    __attribute__((regparm(3)));
extern "C" unsigned test_get_mxcsr();
extern "C" void test_write(const char*, unsigned);

static int check(uint64_t value, uint32_t count)
{
    const unsigned mxcsr = test_get_mxcsr();
    const uint64_t expected = original_u64_shift_left(
        static_cast<uint32_t>(value), static_cast<uint32_t>(value >> 32), count);
    if (test_get_mxcsr() != mxcsr)
        return 1;
    const uint64_t actual = u64_shift_left(value, count);
    if (test_get_mxcsr() != mxcsr || expected != actual)
        return 2;
    return 0;
}

extern "C" int test_main()
{
    const uint64_t values[] = {
        0, 1, 0xffffffffffffffffULL, 0x8000000000000000ULL,
        0x0000000080000000ULL, 0xffffffff00000000ULL,
        0x00000000ffffffffULL, 0x0123456789abcdefULL,
        0xfedcba9876543210ULL
    };
    const uint32_t upper_counts[] = {0, 0x100u, 0x12345600u, 0xffffff00u};
    for (unsigned i = 0; i < sizeof(values)/sizeof(values[0]); ++i)
        for (unsigned j = 0; j < sizeof(upper_counts)/sizeof(upper_counts[0]); ++j)
            for (uint32_t c = 0; c < 256; ++c)
                if (check(values[i], upper_counts[j] | c)) return 1;
    // Each input bit separately, including both halves and the sign bits.
    for (unsigned bit = 0; bit < 64; ++bit)
        for (uint32_t c = 0; c < 256; ++c)
            if (check(uint64_t(1) << bit, c)) return 2;
    // Deterministic mixed words exercise bit transfer across the 32-bit split.
    uint32_t state = 0xa5a55a5au;
    for (unsigned i = 0; i < 4096; ++i) {
        state = state * 1664525u + 1013904223u;
        const uint32_t low = state;
        state = state * 1664525u + 1013904223u;
        const uint64_t value = (uint64_t(state) << 32) | low;
        if (check(value, i)) return 3;
    }
    test_write("u64-shift-left: passed\n", 23);
    return 0;
}
