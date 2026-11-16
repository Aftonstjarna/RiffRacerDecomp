#include "impl.hpp"
extern "C" int __attribute__((fastcall)) original_audio_frame_headers_compatible(uint32_t, uint32_t);
namespace {
unsigned calls;
int check(uint32_t a, uint32_t b, int expected = -1)
{
    // Volatile sentinels verify caller-owned input storage stays untouched.
    volatile uint32_t storage[4] = {0x13579bdfu, a, b, 0x2468ace0u};
    int actual = riff::audio_frame_headers_compatible(storage[1], storage[2]);
    int original = original_audio_frame_headers_compatible(storage[1], storage[2]);
    ++calls;
    return actual == original && (actual == 0 || actual == 1) &&
        (expected < 0 || actual == expected) &&
        storage[0] == 0x13579bdfu && storage[1] == a &&
        storage[2] == b && storage[3] == 0x2468ace0u;
}
uint32_t random_word(uint32_t& state)
{
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}
}
extern "C" int test_main()
{
    if (!check(0, 0, 1) || !check(0xffffffffu, 0xffffffffu, 1) ||
        !check(0, 0xffffffffu, 0) || !check(0xfffb9000u, 0xfffba200u, 1)) return 1;
    // Every individual differing bit, both directions, on two backgrounds.
    for (unsigned bit = 0; bit < 32; ++bit) {
        uint32_t delta = uint32_t(1) << bit;
        if (!check(0, delta) || !check(delta, 0) ||
            !check(~uint32_t(0), ~delta) || !check(~delta, ~uint32_t(0))) return 2;
    }
    // Exhaust all 13 ignored bits and all 16 pairs of channel modes.
    // The equality mask is held constant, then each compared bit is broken.
    for (uint32_t packed = 0; packed < 8192; ++packed) {
        uint32_t differences = 0;
        unsigned source_bit = 0;
        for (unsigned bit = 0; bit < 32; ++bit) {
            uint32_t mask = uint32_t(1) << bit;
            if ((mask & (0xfffe0c00u | 0xc0u)) == 0) {
                if (packed & (uint32_t(1) << source_bit)) differences |= mask;
                ++source_bit;
            }
        }
        for (unsigned a = 0; a < 4; ++a)
            for (unsigned b = 0; b < 4; ++b)
                if (!check(0xfffa0800u | (a << 6),
                           (0xfffa0800u ^ differences) | (b << 6),
                           (a == 3) == (b == 3))) return 3;
    }
    for (unsigned bit = 0; bit < 32; ++bit)
        if ((uint32_t(1) << bit) & 0xfffe0c00u)
            for (unsigned a = 0; a < 4; ++a)
                for (unsigned b = 0; b < 4; ++b)
                    if (!check(0xfffa0800u | (a << 6),
                        (0xfffa0800u ^ (uint32_t(1) << bit)) | (b << 6), 0)) return 4;
    uint32_t state = 0x927f460u;
    for (unsigned i = 0; i < 100000; ++i) {
        uint32_t a = random_word(state), b = random_word(state);
        if (!check(a, b) || !check(a, (a & 0xfffe0c00u) | (b & ~0xfffe0c00u))) return 5;
    }
    return calls > 300000 ? 0 : 6;
}
