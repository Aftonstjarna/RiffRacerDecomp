#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_audio_index_compact_even(AudioIndex*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(AudioIndex) == 24, "x86 object size");
static_assert(offsetof(AudioIndex, count) == 16, "count offset");
static_assert(offsetof(AudioIndex, growth) == 20, "growth offset");

static uint32_t mix(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352du; x ^= x >> 15;
    return x ^ 0xa5a55a5au;
}
static int run(uint32_t n, uint32_t stride, bool nullEmpty) {
    uint32_t a[262], b[262], before[262];
    for (uint32_t i = 0; i < 262; ++i)
        a[i] = b[i] = before[i] = mix(i + n * 313u + stride);
    AudioIndex x = {nullEmpty ? 0 : a + 2, stride, 0x89abcdefu,
                    0x13579bdfu, n, 0xfedcba98u};
    AudioIndex y = x; y.entries = nullEmpty ? 0 : b + 2;
    // Repetition checks that the tail retained by one call stays retained
    // on later compactions, including the eventual count==1 early return.
    for (unsigned pass = 0; pass < 12; ++pass) {
        const uint32_t oldCount = x.count, oldStride = x.stride;
        const uint32_t oldCovered = x.coveredUnits;
        for (unsigned i = 0; i < 262; ++i) before[i] = a[i];
        original_audio_index_compact_even(&x);
        y.compactEven();
        if (x.entries != (nullEmpty ? 0 : a + 2) ||
            y.entries != (nullEmpty ? 0 : b + 2) ||
            x.stride != y.stride || x.coveredUnits != y.coveredUnits ||
            x.capacity != y.capacity || x.count != y.count || x.growth != y.growth)
            return 1;
        const uint32_t expectedCount = oldCount < 2 ? oldCount : oldCount / 2;
        const uint32_t expectedStride = oldCount < 2 ? oldStride : oldStride * 2u;
        if (x.count != expectedCount || x.stride != expectedStride ||
            x.coveredUnits != (oldCount < 2 ? oldCovered : expectedCount * expectedStride) ||
            x.capacity != 0x13579bdfu || x.growth != 0xfedcba98u) return 2;
        for (uint32_t i = 0; i < 262; ++i) {
            const uint32_t expected = oldCount >= 2 && i >= 2 && i < expectedCount + 2
                ? before[2 + (i - 2) * 2] : before[i];
            if (a[i] != b[i] || a[i] != expected) return 3;
        }
    }
    return 0;
}
extern "C" int test_main() {
    const uint32_t strides[] = {0, 1, 2, 3, 0x7fffffffu, 0x80000000u, 0xffffffffu, 0x12345678u};
    for (unsigned s = 0; s < sizeof(strides)/sizeof(strides[0]); ++s)
        for (uint32_t n = 0; n <= 257; ++n) {
            int result = run(n, strides[s], false);
            if (result) return result;
        }
    if (run(0, 0xffffffffu, true) || run(1, 0x80000000u, true)) return 4;
    test_write("audio-index-compact-even: passed\n", 33);
    return 0;
}
