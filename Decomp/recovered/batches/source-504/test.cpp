#include "impl.hpp"
#include <stddef.h>
extern "C" bool __attribute__((thiscall)) original_nested_record_pair_copy(PairCopyOwner*, void*, void*);
extern "C" void test_write(const char*, unsigned);
static_assert(offsetof(PairCopyOwner, nested) == 0x44, "original pointer offset");
struct Arena { PairCopyOwner owner; unsigned char data[512]; };
static Arena arena;
static unsigned char expected[sizeof(Arena)];
static void initialize(unsigned seed, bool absent) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&arena);
    for (unsigned i = 0; i < sizeof arena; ++i) bytes[i] = static_cast<unsigned char>((i * 37 + seed * 19) ^ (i >> 2));
    arena.owner.nested = absent ? 0 : arena.data;
}
static bool run(unsigned seed, int a, int b, bool absent, bool replace) {
    bool result = false;
    for (unsigned pass = 0; pass < 2; ++pass) {
        initialize(seed, absent);
        if (replace) {
            // First 8-byte store starts at owner+0x40 and redirects nested.
            unsigned char* replacement = arena.data + 256;
            const unsigned char* p = reinterpret_cast<const unsigned char*>(&replacement);
            for (unsigned j = 0; j < sizeof replacement; ++j) arena.data[0x74+j] = p[j];
        }
        unsigned char* base = reinterpret_cast<unsigned char*>(&arena);
        void* first = a < 0 ? static_cast<void*>(base + 0x40) : static_cast<void*>(arena.data + a);
        void* second = arena.data + b;
        if (absent) { first = 0; second = 0; }
        bool value = pass == 0 ? original_nested_record_pair_copy(&arena.owner, first, second) : arena.owner.copyRecordPair(first, second);
        if (value != !absent) return false;
        if (pass == 0) {
            result = value;
            for (unsigned i = 0; i < sizeof arena; ++i) expected[i] = base[i];
        } else {
            if (value != result) return false;
            for (unsigned i = 0; i < sizeof arena; ++i) {
                if (expected[i] != base[i]) return false;
            }
        }
    }
    return true;
}
extern "C" int test_main() {
    if (!run(0, 0, 0, true, false)) return 1;
    const int offsets[] = {0, 1, 0x60, 0x64, 0x65, 0x68, 0x6c, 0x70, 0x71, 0x74, 0x78, 0x7b, 200, 201};
    for (unsigned seed = 0; seed < 12; ++seed) {
        for (unsigned a = 0; a < sizeof offsets / sizeof offsets[0]; ++a) {
            for (unsigned b = 0; b < sizeof offsets / sizeof offsets[0]; ++b) {
                if (!run(seed, offsets[a], offsets[b], false, false)) return 2;
            }
        }
        if (!run(seed, -1, 200, false, true)) return 3;
    }
    test_write("pair-copy differential checks passed\n", 37);
    return 0;
}
