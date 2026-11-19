#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_visual_colour_set(Visual*, const float*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

union Bits { uint32_t u; float f; };
static float number(uint32_t u) { Bits x; x.u = u; return x.f; }
static uint32_t fs[64];
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x = (const unsigned char*)a;
    const unsigned char* y = (const unsigned char*)b;
    for (unsigned i = 0; i < n; ++i) if (x[i] != y[i]) return false;
    return true;
}
static bool run(const uint32_t* oldv, const uint32_t* newv, uint32_t flags, bool changed) {
    Visual a, b;
    unsigned char* p = (unsigned char*)&a;
    for (unsigned i = 0; i < sizeof(a); ++i) p[i] = (unsigned char)(i * 37 + 11);
    for (int i = 0; i < 4; ++i) a.colour[i] = number(oldv[i]);
    a.flags = flags; b = a;
    float input[4]; for (int i = 0; i < 4; ++i) input[i] = number(newv[i]);
    float saved[4]; for (int i = 0; i < 4; ++i) saved[i] = input[i];
    const unsigned head = test_get_fs_head();
    original_visual_colour_set(&a, input);
    if (test_get_fs_head() != head) return false;
    b.set_colour(input);
    if (!same(&a, &b, sizeof a) || !same(input, saved, sizeof input)) return false;
    if (a.flags != (flags | (changed ? 0x100u : 0u))) return false;
    for (int i = 0; i < 4; ++i) {
        Bits result; result.f = a.colour[i];
        if (result.u != (changed ? newv[i] : oldv[i])) return false;
    }
    return true;
}
extern "C" int test_main() {
    if (offsetof(Visual, colour) != 0x90 || offsetof(Visual, flags) != 0x170) return 1;
    fs[0] = 0xffffffffu;
    if (test_install_fs(fs) != 0 || test_get_fs_head() != fs[0]) return 2;
    const uint32_t base[4] = {0x3f800000, 0x40000000, 0x40400000, 0x40800000};
    if (!run(base, base, 0x40000200, false)) return 3;
    for (int i = 0; i < 4; ++i) {
        uint32_t value[4]; for (int j = 0; j < 4; ++j) value[j] = base[j];
        value[i] = 0xc0800000;
        if (!run(base, value, 0x80000004, true)) return 4 + i;
        value[i] = 0x7fc12345;
        if (!run(base, value, 0x100, true)) return 8 + i;
        if (!run(value, value, 0, true)) return 12 + i;
    }
    const uint32_t zeros1[4] = {0, 0x80000000, 0, 0x80000000};
    const uint32_t zeros2[4] = {0x80000000, 0, 0x80000000, 0};
    if (!run(zeros1, zeros2, 0, false)) return 16;
    const uint32_t inf[4] = {0x7f800000, 0xff800000, 0x00800000, 0x80800000};
    if (!run(inf, inf, 0x100, false)) return 17;
    return 0;
}
extern "C" void* memcpy(void* destination, const void* source, unsigned n) {
    unsigned char* d = (unsigned char*)destination;
    const unsigned char* s = (const unsigned char*)source;
    for (unsigned i = 0; i < n; ++i) d[i] = s[i];
    return destination;
}
