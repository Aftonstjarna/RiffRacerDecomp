#include "impl.hpp"
extern "C" uint32_t __attribute__((fastcall))
original_flag_selected_product(const FlagSelectedProduct*, uint32_t);

extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];

struct GuardedObject {
    uint32_t before[4];
    FlagSelectedProduct object;
    uint32_t after[4];
};
static GuardedObject input, snapshot;
static const uint32_t values[] = {
    0u, 1u, 2u, 3u, 4u, 0x10000u, 0x3fffffffu, 0x40000000u,
    0x7fffffffu, 0x80000000u, 0xfffffffeu, 0xffffffffu
};
static const uint32_t flag_values[] = {
    0u, 0x4000u, 0x3fffu, 0x4001u, 0x80000000u, 0xffffbfffu, 0xffffffffu
};
static void save() {
    const unsigned char* s = reinterpret_cast<const unsigned char*>(&input);
    unsigned char* d = reinterpret_cast<unsigned char*>(&snapshot);
    for (unsigned i = 0; i < sizeof(input); ++i) d[i] = s[i];
}
static bool unchanged() {
    const unsigned char* a = reinterpret_cast<const unsigned char*>(&input);
    const unsigned char* b = reinterpret_cast<const unsigned char*>(&snapshot);
    for (unsigned i = 0; i < sizeof(input); ++i) if (a[i] != b[i]) return false;
    return true;
}
static int check(uint32_t flags, uint32_t ordinary, uint32_t common, uint32_t multiplier) {
    input.object.flags = flags;
    input.object.ordinary_factor = ordinary;
    input.object.common_factor = common;
    save();
    const uint32_t original = original_flag_selected_product(&input.object, multiplier);
    if (test_get_fs_head() != fs_storage[0]) return 7;
    if (!unchanged()) return 1;
    const uint32_t recovered = input.object.selected_product(multiplier);
    if (!unchanged()) return 2;
    if (original != recovered) return 3;
    return 0;
}
static uint32_t random_word(uint32_t& state) {
    state = state * 1664525u + 1013904223u;
    return state;
}
extern "C" int test_main() {
    fs_storage[0] = 0xffffffffu;
    if (test_install_fs(fs_storage) != 0) return 6;
    if (test_get_fs_head() != fs_storage[0]) return 7;
    unsigned char* p = reinterpret_cast<unsigned char*>(&input);
    for (unsigned i = 0; i < sizeof(input); ++i) p[i] = static_cast<unsigned char>(i * 37u + 0xa5u);
    // Exhaustive cross-product of representative bit patterns, with guards and
    // every byte of the object checked after each individual original/C++ call.
    for (unsigned f = 0; f < sizeof(flag_values)/sizeof(flag_values[0]); ++f)
        for (unsigned a = 0; a < sizeof(values)/sizeof(values[0]); ++a)
            for (unsigned b = 0; b < sizeof(values)/sizeof(values[0]); ++b)
                for (unsigned m = 0; m < sizeof(values)/sizeof(values[0]); ++m) {
                    int result = check(flag_values[f], values[a], values[b], values[m]);
                    if (result) return result;
                }
    uint32_t seed = 0x55d190u;
    for (unsigned i = 0; i < 1024; ++i) {
        const uint32_t flags = random_word(seed);
        const uint32_t a = random_word(seed);
        const uint32_t b = random_word(seed);
        const uint32_t m = random_word(seed);
        int result = check(flags, a, b, m);
        if (result) return result;
    }
    // Explicit known outcomes also detect a shared test declaration mistake.
    input.object.flags = 0; input.object.ordinary_factor = 3; input.object.common_factor = 5;
    if (input.object.selected_product(7) != 105u) return 4;
    input.object.flags = 0x4000;
    if (input.object.selected_product(7) != 140u) return 5;
    return 0;
}
