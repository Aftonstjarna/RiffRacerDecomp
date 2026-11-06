#include "impl.hpp"
#include <stdint.h>
extern "C" int original_double_integer_parity(double);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);

static int check(uint64_t bits, int expected)
{
    struct Guarded { uint32_t before; double value; uint32_t after; } input;
    input.before = 0x12345678; input.after = 0xabcdef01;
    unsigned char* p = reinterpret_cast<unsigned char*>(&input.value);
    for (unsigned i = 0; i < 8; ++i) p[i] = static_cast<unsigned char>(bits >> (8*i));
    const unsigned control = test_get_mxcsr();
    int reference = original_double_integer_parity(input.value);
    if (test_get_mxcsr() != control) return 1;
    int recovered = double_integer_parity(input.value);
    if (test_get_mxcsr() != control) return 2;
    if (reference != recovered || (expected >= 0 && recovered != expected)) return 3;
    if (input.before != 0x12345678 || input.after != 0xabcdef01) return 4;
    for (unsigned i = 0; i < 8; ++i)
        if (p[i] != static_cast<unsigned char>(bits >> (8*i))) return 5;
    return 0;
}
extern "C" int test_main()
{
    const unsigned saved = test_get_mxcsr();
    const uint64_t special[] = {0, UINT64_C(0x8000000000000000), 1,
        UINT64_C(0x000fffffffffffff), UINT64_C(0x0010000000000000),
        UINT64_C(0x3fefffffffffffff), UINT64_C(0x3ff0000000000000),
        UINT64_C(0x4000000000000000), UINT64_C(0x4008000000000000),
        UINT64_C(0x400c000000000000), UINT64_C(0x7fefffffffffffff),
        UINT64_C(0x7ff0000000000000), UINT64_C(0x7ff0000000000001),
        UINT64_C(0x7ff8000000000000), UINT64_C(0x7fffffffffffffff)};
    const int expected[] = {2,2,0,0,0,0,1,2,1,0,2,0,0,0,0};
    for (unsigned mode = 0; mode < 16; ++mode) {
        test_set_mxcsr(0x1f80u | ((mode & 3) << 13) | ((mode & 4) ? 0x8040u : 0) | ((mode & 8) ? 0x3fu : 0));
        for (unsigned i = 0; i < sizeof(special)/sizeof(special[0]); ++i)
            for (unsigned sign = 0; sign < 2; ++sign)
                if (check(special[i] | (static_cast<uint64_t>(sign) << 63), expected[i])) return 10;
        // Every exponent, adjacent encodings around powers of two, and each
        // fraction bit independently exercise both original word-split paths.
        for (unsigned e = 0; e < 2048; ++e) {
            uint64_t base = static_cast<uint64_t>(e) << 52;
            for (unsigned sign = 0; sign < 2; ++sign) {
                uint64_t b = base | (static_cast<uint64_t>(sign) << 63);
                if (check(b, -1) || check(b | UINT64_C(0xfffffffffffff), -1)) return 11;
                for (unsigned bit = 0; bit < 52; ++bit)
                    if (check(b | (UINT64_C(1) << bit), -1)) return 12;
            }
        }
    }
    uint64_t state = UINT64_C(0x12345678abcdef01);
    for (unsigned i = 0; i < 100000; ++i) {
        state ^= state << 13; state ^= state >> 7; state ^= state << 17;
        if (check(state, -1)) return 13;
    }
    test_set_mxcsr(saved);
    return 0;
}
