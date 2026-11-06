#include "impl.hpp"
// GCC regparm(3) assigns EAX, EDX, ECX in that order and uses caller
// stack cleanup. The ignored first argument adapts this custom internal ABI
// without a machine-code wrapper. This is NOT MS fastcall (callee cleanup).
extern "C" void original_record24_rotate(uint32_t ignored_eax,
    unsigned char* middle, unsigned char* first, unsigned char* last)
    __attribute__((regparm(3)));
extern "C" void test_write(const char*, unsigned);
static unsigned char expected[24 * 101 + 64];
static unsigned char actual[sizeof(expected)];
static unsigned char before[sizeof(expected)];

extern "C" int test_main()
{
    unsigned cases = 0;
    // Every split for lengths 0..100 covers coprime and multiple-cycle cases,
    // shift 0/count, singleton, balanced halves and highly unequal blocks.
    for (unsigned n = 0; n <= 100; ++n) {
        for (unsigned split = 0; split <= n; ++split) {
            for (unsigned align = 0; align < 4; ++align) {
                const unsigned base = 19 + align;
                for (unsigned i = 0; i < sizeof(expected); ++i) {
                    before[i] = static_cast<unsigned char>(
                        (i * 73u + (i >> 4) * 19u + n * 11u + split) ^ (i >> 8));
                    actual[i] = expected[i] = before[i];
                }
                original_record24_rotate(0, expected + base + split * 24,
                    expected + base, expected + base + n * 24);
                record24_rotate(actual + base, actual + base + split * 24,
                    actual + base + n * 24);
                for (unsigned i = 0; i < sizeof(expected); ++i) {
                    if (actual[i] != expected[i]) return 1;
                    unsigned char wanted = before[i];
                    if (i >= base && i < base + n * 24) {
                        unsigned relative = i - base;
                        unsigned record = (relative / 24 + split) % n;
                        wanted = before[base + record * 24 + relative % 24];
                    }
                    // Includes all 24 payload bytes and every untouched guard.
                    if (expected[i] != wanted) return 2;
                }
                ++cases;
            }
        }
    }
    if (cases != 20604) return 3;
    static const char message[] = "record24-rotate: 20604 cases passed\n";
    test_write(message, sizeof(message) - 1);
    return 0;
}
