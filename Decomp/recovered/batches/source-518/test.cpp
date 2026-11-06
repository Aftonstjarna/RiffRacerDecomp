#include "impl.hpp"
// regparm(3) places these three words in EAX, EDX, ECX respectively;
// the uint64_t result is EDX:EAX. This is NOT a thiscall member routine.
extern "C" uint64_t original_unsigned64_logical_shift_right(
    uint32_t low, uint32_t high, uint32_t count) __attribute__((regparm(3)));
extern "C" unsigned test_get_mxcsr();

static int check(uint64_t value, uint32_t register_count)
{
    volatile uint32_t guards[4] = {0x01234567u, 0x89abcdefu, 0xdeadbeefu, 0xfedcba98u};
    const unsigned mxcsr = test_get_mxcsr();
    const uint64_t actual = original_unsigned64_logical_shift_right(
        static_cast<uint32_t>(value), static_cast<uint32_t>(value >> 32), register_count);
    if (test_get_mxcsr() != mxcsr) return 1;
    if (guards[0] != 0x01234567u || guards[1] != 0x89abcdefu ||
        guards[2] != 0xdeadbeefu || guards[3] != 0xfedcba98u) return 2;
    const uint8_t count = static_cast<uint8_t>(register_count);
    const uint64_t recovered = riff::unsigned64_logical_shift_right(value, count);
    if (actual != recovered) return 3;
    // Independently compute the mathematical result using repeated one-bit shifts.
    uint64_t expected = value;
    for (unsigned i = 0; i < count; ++i) expected >>= 1;
    if (actual != expected) return 4;
    return 0;
}

extern "C" int test_main()
{
    const uint64_t patterns[] = {
        0, 1, UINT64_C(0xffffffffffffffff), UINT64_C(0x8000000000000000),
        UINT64_C(0x0000000080000000), UINT64_C(0xffffffff00000000),
        UINT64_C(0x00000000ffffffff), UINT64_C(0x0123456789abcdef),
        UINT64_C(0xaaaaaaaa55555555), UINT64_C(0x55555555aaaaaaaa)
    };
    for (unsigned c = 0; c < 256; ++c) {
        for (unsigned p = 0; p < sizeof(patterns)/sizeof(patterns[0]); ++p) {
            int error = check(patterns[p], c);
            if (error) return error;
            error = check(patterns[p], 0xa5b6c700u | c);
            if (error) return error;
        }
        for (unsigned bit = 0; bit < 64; ++bit) {
            const int error = check(UINT64_C(1) << bit, c);
            if (error) return error;
        }
    }
    uint64_t state = UINT64_C(0x3141592653589793);
    for (unsigned i = 0; i < 4096; ++i) {
        state ^= state << 13;
        state ^= state >> 7;
        state ^= state << 17;
        const int error = check(state, i);
        if (error) return error;
    }
    return 0;
}
