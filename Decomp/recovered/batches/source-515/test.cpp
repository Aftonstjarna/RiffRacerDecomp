#include "impl.hpp"
extern "C" uint64_t __attribute__((stdcall)) original_u64_multiply_low(uint64_t, uint64_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_write(const char*, unsigned);

// Independent shift-and-add expectation; no 64-bit multiply helper required.
static uint64_t expected(uint64_t a, uint64_t b)
{
    uint64_t result = 0;
    for (unsigned i = 0; i != 64; ++i) {
        if (b & 1) result += a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}
struct Probe { uint32_t before; uint64_t a, b; uint32_t after; };
static int check(uint64_t a, uint64_t b)
{
    volatile Probe p = {0x13579bdfU, a, b, 0x2468ace0U};
    const unsigned mxcsr = test_get_mxcsr();
    const uint64_t want = expected(a, b);
    const uint64_t actual = original_u64_multiply_low(p.a, p.b);
    if (test_get_fs_head() != 0xffffffffU) return 1;
    if (test_get_mxcsr() != mxcsr) return 2;
    if (actual != want || u64_multiply_low(p.a, p.b) != actual) return 3;
    if (p.before != 0x13579bdfU || p.after != 0x2468ace0U || p.a != a || p.b != b) return 4;
    return 0;
}
extern "C" int test_main()
{
    uint32_t fs_storage[8] = {0xffffffffU, 0, 0, 0, 0, 0, 0, 0};
    if (test_install_fs(fs_storage) != 0) return 10;
    static const uint64_t values[] = {
        0, 1, 2, 0x7fffffffULL, 0x80000000ULL, 0xfffffffeULL,
        0xffffffffULL, 0x100000000ULL, 0x100000001ULL,
        0x7fffffffffffffffULL, 0x8000000000000000ULL,
        0xffffffff00000000ULL, 0xffffffff00000001ULL,
        0xffffffffffffffffULL, 0x0123456789abcdefULL, 0xaaaaaaaa55555555ULL
    };
    for (unsigned i = 0; i != sizeof(values)/sizeof(values[0]); ++i)
        for (unsigned j = 0; j != sizeof(values)/sizeof(values[0]); ++j)
            if (check(values[i], values[j])) return 11;
    for (unsigned i = 0; i != 64; ++i)
        for (unsigned j = 0; j != 64; ++j)
            if (check(uint64_t(1) << i, uint64_t(1) << j)) return 12;
    uint32_t state = 0x19d3b72fU;
    for (unsigned i = 0; i != 10000; ++i) {
        state ^= state << 13; state ^= state >> 17; state ^= state << 5;
        uint64_t a = uint64_t(state) << 32;
        state ^= state << 13; state ^= state >> 17; state ^= state << 5;
        a |= state;
        state ^= state << 13; state ^= state >> 17; state ^= state << 5;
        uint64_t b = uint64_t(state) << 32;
        state ^= state << 13; state ^= state >> 17; state ^= state << 5;
        b |= state;
        if (check(a, b)) return 13;
    }
    test_write("u64-multiply-low: 14352 cases passed\n", 37);
    return 0;
}
