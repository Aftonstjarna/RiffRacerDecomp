#include "impl.hpp"
#include <stddef.h>
// Test-only placement construction, without a C++ runtime dependency.
void* operator new(size_t, void* address) noexcept { return address; }
extern "C" Record48* __attribute__((thiscall))
original_record48_zero_copy_construct(void* destination, const void* source);
extern "C" void test_write(const char*, unsigned);

static unsigned char expected[256];
alignas(16) static unsigned char actual[256];
alignas(16) static unsigned char oracle[256];

static void model(unsigned dest, unsigned src) {
    for (unsigned i = 0; i < 48; ++i) expected[dest+i] = 0;
    for (unsigned block = 0; block < 48; block += 16) {
        unsigned char saved[16];
        for (unsigned i = 0; i < 16; ++i) saved[i] = expected[src+block+i];
        for (unsigned i = 0; i < 16; ++i) expected[dest+block+i] = saved[i];
    }
}

extern "C" int test_main() {
    unsigned cases = 0;
    // Every byte source displacement includes all overlap distances, exact
    // self-alias, adjacent/disjoint records and unaligned SSE input addresses.
    // Destination is validly aligned for the recovered C++ object (4 bytes),
    // but takes each of the four possible alignments relative to an SSE block.
    for (unsigned pattern = 0; pattern < 8; ++pattern) {
        for (unsigned dest = 96; dest <= 108; dest += 4) {
            for (unsigned src = 16; src <= 192; ++src) {
                for (unsigned i = 0; i < 256; ++i) {
                    unsigned value = (i * 73u + pattern * 29u) ^ (i >> (pattern % 5));
                    if (pattern == 0) value = 0;
                    if (pattern == 1) value = 255;
                    expected[i] = actual[i] = oracle[i] = static_cast<unsigned char>(value);
                }
                model(dest, src);
                Record48* result = new (actual + dest) Record48(actual + src);
                Record48* original = original_record48_zero_copy_construct(oracle + dest, oracle + src);
                if (result != reinterpret_cast<Record48*>(actual + dest)) return 1;
                if (original != reinterpret_cast<Record48*>(oracle + dest)) return 2;
                // Compare the entire arena: source changes due to aliasing and
                // all untouched surrounding bytes are checked, not just output.
                for (unsigned i = 0; i < 256; ++i) {
                    if (actual[i] != oracle[i]) return 3;
                    if (actual[i] != expected[i]) return 4;
                }
                ++cases;
            }
        }
    }
    if (cases != 5664) return 5;
    const char message[] = "PASS: 5664 record48 differential cases\n";
    test_write(message, sizeof(message)-1);
    return 0;
}
