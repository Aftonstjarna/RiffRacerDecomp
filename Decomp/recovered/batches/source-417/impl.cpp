#include "impl.hpp"
// Only the load/store intrinsics are used; avoid the hosted allocation helpers
// pulled in by GCC SSE headers in a freestanding 32-bit build.
#if defined(__GNUC__) && !defined(_MSC_VER)
#define _MM_MALLOC_H_INCLUDED
#endif
#include <emmintrin.h>

void* record20_range_copy(const void* begin, const void* end, void* destination) {
    uintptr_t source = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t limit = reinterpret_cast<uintptr_t>(end);
    uintptr_t target = reinterpret_cast<uintptr_t>(destination);
    while (source != limit) {
        if (target != 0) {
            // Preserve the original chunk ordering, including overlapping ranges.
            const __m128i first = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
            _mm_storeu_si128(reinterpret_cast<__m128i*>(target), first);
            unsigned char tail[4];
            for (unsigned i = 0; i != 4; ++i)
                tail[i] = reinterpret_cast<const unsigned char*>(source)[16 + i];
            for (unsigned i = 0; i != 4; ++i)
                reinterpret_cast<unsigned char*>(target)[16 + i] = tail[i];
        }
        source += 20;
        target += 20;
    }
    return reinterpret_cast<void*>(target);
}
// Caller evidence: 0x4b2999, 0x52c791 allocate/copy vector-like storage;
// 0x561a28/44 and 0x561ac2/0x561b1b copy insertion subranges. Object +0/+4
// provide begin/end; this helper does not update those fields. No external calls.
