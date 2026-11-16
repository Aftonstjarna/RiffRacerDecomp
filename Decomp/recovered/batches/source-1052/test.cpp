#include "impl.hpp"
extern "C" int32_t __attribute__((fastcall)) original_audio_resample_output_count(
    const AudioResampleState*, int32_t);
extern "C" void test_write(const char*, unsigned);

static AudioResampleState state;
static unsigned char saved[sizeof(state)];
static uint32_t random_state = 0x9e3779b9u;
static uint32_t random_word() {
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;
    return random_state;
}
static int32_t signed_word(uint32_t v) {
    return v <= 0x7fffffffu ? static_cast<int32_t>(v) :
        -1 - static_cast<int32_t>(~v);
}
static bool unchanged() {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&state);
    for (unsigned i = 0; i < sizeof(state); ++i)
        if (bytes[i] != saved[i]) return false;
    return true;
}
static bool check(int32_t count, int32_t limit, int32_t step,
                  bool has_expected = false, int32_t expected = 0) {
    state.chunk_input_limit = limit;
    state.step_q15 = step;
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&state);
    for (unsigned i = 0; i < sizeof(state); ++i) saved[i] = bytes[i];
    const int32_t reference = original_audio_resample_output_count(&state, count);
    if (!unchanged()) return false;
    const int32_t recovered = state.output_count(count);
    if (!unchanged() || reference != recovered) return false;
    if (has_expected && recovered != expected) return false;
    // Repeating a query must not carry phase between calls.
    return state.output_count(count) == reference && unchanged();
}
extern "C" int test_main() {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&state);
    for (unsigned i = 0; i < sizeof(state); ++i) bytes[i] = (i * 37u + 19u) & 255u;
    const int32_t counts[] = {-2147483647-1, -1, 0, 1, 2, 3, 383, 384,
                              385, 1151, 1152, 1153, 4097};
    const int32_t limits[] = {1, 2, 3, 384, 1152, 65535, 2147483647};
    const int32_t steps[] = {0, 1, -1, 8192, 16383, 16384, 16385,
                            32767, 32768, 32769, 65536, -16384, -32768,
                            2147483647, -2147483647-1, -65537};
    for (unsigned a = 0; a < sizeof(counts)/sizeof(counts[0]); ++a)
        for (unsigned b = 0; b < sizeof(limits)/sizeof(limits[0]); ++b)
            for (unsigned c = 0; c < sizeof(steps)/sizeof(steps[0]); ++c)
                if (!check(counts[a], limits[b], steps[c])) return 1;
    if (!check(1, 384, 16384, true, 1) ||
        !check(1, 384, -16384, true, 0) ||
        !check(1, 384, -49152, true, -1) ||
        !check(1153, 1152, 32768, true, 1153) ||
        !check(65536, 65536, 32768, true, -65535)) return 2;
    // Large counts with bounded iteration counts, including wrapped products.
    if (!check(2147483647, 2147483647, 2147483647) ||
        !check(2147483647, 65535, 65537) ||
        !check(2147483647, -1, 32768) ||
        !check(1, -2147483647-1, -1)) return 3;
    // Invalid chunk limits are safe to query only with nonpositive counts here.
    if (!check(0, 0, 2147483647) || !check(-1, -7, -1)) return 4;
    for (unsigned i = 0; i < 3000; ++i) {
        const int32_t count = static_cast<int32_t>(random_word() % 10000u);
        const int32_t limit = 1 + static_cast<int32_t>(random_word() % 2048u);
        const int32_t step = signed_word(random_word());
        if (!check(count, limit, step)) return 5;
    }
    test_write("audio-resample-output-count: passed\n", 36);
    return 0;
}
