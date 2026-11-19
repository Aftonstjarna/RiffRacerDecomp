#include "impl.hpp"
extern "C" uint32_t __attribute__((fastcall)) original_unicode_scalar_cp1252_map(uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

static uint32_t fs_storage[16];
static int check(uint32_t value) {
    uint32_t before = fs_storage[0];
    uint32_t expected = original_unicode_scalar_cp1252_map(value);
    return test_get_fs_head() == before && fs_storage[0] == before &&
           unicode_scalar_cp1252_map(value) == expected;
}
extern "C" int test_main() {
    fs_storage[0] = 0x12345678;
    if (test_install_fs(fs_storage) != 0) return 1;
    // Exhaust all BMP values, including every exception and adjacent values,
    // C1 controls, surrogates, and values the caller would later replace.
    for (uint32_t i = 0; i != 0x10000; ++i)
        if (!check(i)) return 2;
    const uint32_t edge[] = {0x10000, 0x10ffff, 0x110000, 0x7fffffff,
                             0x80000000, 0xfffffffe, 0xffffffff};
    for (unsigned i = 0; i != sizeof(edge)/sizeof(edge[0]); ++i)
        if (!check(edge[i])) return 3;
    uint32_t x = 0x12345678;
    for (unsigned i = 0; i != 10000; ++i) {
        x = x * 1664525u + 1013904223u;
        if (!check(x)) return 4;
    }
    return 0;
}
