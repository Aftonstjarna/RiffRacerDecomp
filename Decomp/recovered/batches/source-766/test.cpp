#include "impl.hpp"
// regparm(3) puts dummy in EAX, last in EDX, first in ECX, and
// destination on the stack with caller cleanup: the observed custom ABI.
// The original overwrites EAX before using it. This is not MS fastcall.
extern "C" unsigned char* original_record520_range_copy(
    unsigned dummy, const unsigned char* last, const unsigned char* first,
    unsigned char* destination) __attribute__((regparm(3)));
static unsigned char actual[4096], expected[4096], before[4096];
static int run(unsigned src, unsigned dst, unsigned count) {
    for (unsigned i = 0; i < sizeof(actual); ++i) {
        unsigned char v = static_cast<unsigned char>((i * 37u) ^ (i >> 3) ^ 0xa5u);
        actual[i] = expected[i] = before[i] = v;
    }
    unsigned char* a = riff::copy_record520_range(actual + src,
        actual + src + count * 520, actual + dst);
    unsigned char* b = original_record520_range_copy(0,
        expected + src + count * 520, expected + src, expected + dst);
    if (a != actual + dst + count * 520 ||
        b != expected + dst + count * 520) return 1;
    for (unsigned i = 0; i < sizeof(actual); ++i) {
        if (actual[i] != expected[i]) return 2;
        if ((i < dst || i >= dst + count * 520) && actual[i] != before[i]) return 3;
    }
    return 0;
}
extern "C" int test_main() {
    // Empty null range performs no access, even with null destination.
    if (riff::copy_record520_range(0, 0, 0) != 0) return 1;
    if (original_record520_range_copy(0, 0, 0, 0) != 0) return 2;
    const unsigned cases[][3] = {
        {16, 2200, 0}, {16, 2200, 1}, {16, 2200, 3},
        {17, 2203, 2}, {16, 16, 3}, {16, 536, 3},
        {536, 16, 3}, {32, 33, 3}, {32, 34, 3},
        {32, 35, 3}, {32, 36, 3}, {35, 32, 3}
    };
    for (unsigned i = 0; i < sizeof(cases)/sizeof(cases[0]); ++i) {
        int result = run(cases[i][0], cases[i][1], cases[i][2]);
        if (result) return 10 + static_cast<int>(i) * 4 + result;
    }
    return 0;
}
