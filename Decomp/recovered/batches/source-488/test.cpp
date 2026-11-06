#include "impl.hpp"
// Three 32-bit arguments occupy EAX, EDX, ECX; uint64_t returns in EDX:EAX.
// This is a compiler helper, neither thiscall nor stdcall.
extern "C" uint64_t original_signed64_arithmetic_shift_right(
    uint32_t low, uint32_t high, uint32_t count) __attribute__((regparm(3)));
extern "C" void test_write(const char*, unsigned);

static bool check(uint64_t bits, uint32_t count)
{
    const uint64_t actual = signed64_arithmetic_shift_right(bits, count);
    const uint64_t original = original_signed64_arithmetic_shift_right(
        uint32_t(bits), uint32_t(bits >> 32), count);
    return actual == original;
}

extern "C" int test_main()
{
    const uint64_t patterns[] = {
        0, 1, 2, 0x7fffffffffffffffULL, 0x8000000000000000ULL,
        0xffffffffffffffffULL, 0xffffffff00000000ULL, 0x00000000ffffffffULL,
        0x0123456789abcdefULL, 0xfedcba9876543210ULL,
        0xaaaaaaaaaaaaaaaaULL, 0x5555555555555555ULL
    };
    // Every CL value, including 0,31,32,63,64,255; repeat with upper ECX bits.
    for (unsigned i = 0; i < sizeof(patterns)/sizeof(patterns[0]); ++i)
        for (uint32_t c = 0; c < 1024; ++c)
            if (!check(patterns[i], c) || !check(patterns[i], c | 0xa53c0000u))
                return 1;
    // All one-bit and complemented one-bit inputs, at every low-byte count.
    for (unsigned bit = 0; bit < 64; ++bit)
        for (unsigned c = 0; c < 256; ++c)
            if (!check(uint64_t(1) << bit, c) ||
                !check(~(uint64_t(1) << bit), c))
                return 2;
    uint32_t state = 0x193ac57du;
    for (unsigned i = 0; i < 10000; ++i) {
        state = state * 1664525u + 1013904223u;
        uint64_t bits = uint64_t(state) << 32;
        state = state * 1664525u + 1013904223u;
        bits |= state;
        state = state * 1664525u + 1013904223u;
        if (!check(bits, state)) return 3;
    }
    // There are no fields, pointer arguments, globals, or memory writes in
    // the original; register/flags scratch effects are outside the C++ API.
    test_write("shift oracle comparisons passed\n", 32);
    return 0;
}
