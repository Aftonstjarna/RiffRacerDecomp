#include "impl.hpp"

// Original: Game.exe RVA 0x225c0, VA 0x4225c0, size 112, cdecl.
// The original checks unaligned 32-bit words for equality, then orders the
// first differing word byte by byte. Word numeric order would be incorrect
// on little-endian machines. Explicit byte loads avoid alignment/aliasing UB.
static uint32_t load_word(const unsigned char* p) {
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) |
           (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}

extern "C" int RIFF_CDECL byte_range_compare(const void* left, const void* right,
                                            uint32_t count) {
    const unsigned char* a = static_cast<const unsigned char*>(left);
    const unsigned char* b = static_cast<const unsigned char*>(right);
    while (count >= 4) {
        if (load_word(a) != load_word(b)) {
            for (unsigned i = 0; i < 4; ++i) {
                if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
            }
        }
        a += 4;
        b += 4;
        count -= 4;
    }
    while (count != 0) {
        if (*a != *b) return *a < *b ? -1 : 1;
        ++a;
        ++b;
        --count;
    }
    return 0;
}
// No helpers, imports, globals, object fields, or SEH dependencies. Direct
// callers at 0x422c1e/0x423879 compare min(lengths) and break ties themselves;
// 0x440c7d uses equality for a substring candidate. No string terminator rule.
// Invalid pointers for nonzero counts, races, and volatile/device memory are
// outside the recovered valid-memory contract. No byte-identical build claim.
