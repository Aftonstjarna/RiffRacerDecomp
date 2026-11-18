#include "impl.hpp"
#ifdef _MSC_VER
#include <emmintrin.h>
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)
typedef __m128i Block;
static Block load_block(const unsigned char* p) { _ReadWriteBarrier(); Block v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p)); _ReadWriteBarrier(); return v; }
static void store_block(unsigned char* p, Block v) { _ReadWriteBarrier(); _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v); _ReadWriteBarrier(); }
#else
typedef long long Block __attribute__((vector_size(16), aligned(1), may_alias));
static Block load_block(const unsigned char* p) { return *reinterpret_cast<const volatile Block*>(p); }
static void store_block(unsigned char* p, Block v) { *reinterpret_cast<volatile Block*>(p) = v; }
#endif
void* worker_record64_range_construct(const void* first, const void* last, void* destination) {
    uintptr_t in = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t out = reinterpret_cast<uintptr_t>(destination);
    while (in != end) {
        if (out) {
            unsigned char* d = reinterpret_cast<unsigned char*>(out);
            const unsigned char* s = reinterpret_cast<const unsigned char*>(in);
            Block b = load_block(s);
            store_block(d, b);
            // The 48-byte member constructor zeros twelve words before its
            // three sequential 16-byte snapshots. Aliasing makes this visible.
            for (unsigned i = 0; i != 48; ++i) reinterpret_cast<volatile unsigned char*>(d)[16 + i] = 0;
#ifdef _MSC_VER
            _ReadWriteBarrier();
#endif
            for (unsigned i = 0; i != 48; i += 16) {
                b = load_block(s + 16 + i);
                store_block(d + 16 + i, b);
            }
        }
        in += 64;
        out += 64;
    }
    return reinterpret_cast<void*>(out);
}
