#include "impl.hpp"
#ifdef _MSC_VER
#include <emmintrin.h>
#else
// GCC vector load/store avoids a dependency on unavailable 32-bit CRT headers.
typedef long long __m128i __attribute__((vector_size(16), aligned(1), may_alias));
static __m128i _mm_loadu_si128(const __m128i* p) { return *p; }
static void _mm_storeu_si128(__m128i* p, __m128i value) { *p = value; }
#endif
namespace riff {
// Caller at 0x422491 supplies vector begin/end from object +0/+4 and a
// newly allocated destination. It later updates begin/end/capacity (+0/+4/+8).
// Original private ABI: ECX=first, EDX=last, [ESP+4]=destination, caller cleanup.
// This portable entry deliberately exposes ordinary C++ arguments instead.
// No constructors, destructors, allocation, or external calls occur here.
uintptr_t copy_record36_range(const void* first, const void* last, void* destination) {
    uintptr_t source = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (source != end) {
        if (output != 0) {
            // Keep each load immediately before its corresponding store. A whole
            // record temporary or memmove would change partial-overlap behavior.
            const __m128i low = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
            _mm_storeu_si128(reinterpret_cast<__m128i*>(output), low);
            const __m128i high = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source + 16));
            _mm_storeu_si128(reinterpret_cast<__m128i*>(output + 16), high);
            // Byte assembly avoids alignment/aliasing assumptions for the DWORD.
            const unsigned char* s = reinterpret_cast<const unsigned char*>(source + 32);
            const uint32_t tail = uint32_t(s[0]) | (uint32_t(s[1]) << 8) |
                                  (uint32_t(s[2]) << 16) | (uint32_t(s[3]) << 24);
            unsigned char* d = reinterpret_cast<unsigned char*>(output + 32);
            d[0] = static_cast<unsigned char>(tail);
            d[1] = static_cast<unsigned char>(tail >> 8);
            d[2] = static_cast<unsigned char>(tail >> 16);
            d[3] = static_cast<unsigned char>(tail >> 24);
        }
        source += 36;
        output += 36;
    }
    return output;
}
}
