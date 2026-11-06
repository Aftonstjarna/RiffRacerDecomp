#include "impl.hpp"
#ifdef _MSC_VER
#include <emmintrin.h>
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)
typedef __m128i CopyBlock;
static CopyBlock load_block(const unsigned char* p) {
    _ReadWriteBarrier();
    CopyBlock value = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
    _ReadWriteBarrier();
    return value;
}
static void store_block(unsigned char* p, CopyBlock value) {
    _ReadWriteBarrier();
    _mm_storeu_si128(reinterpret_cast<__m128i*>(p), value);
    _ReadWriteBarrier();
}
#else
// Volatile block accesses keep copying ordered after all volatile zero stores.
// GCC's unaligned aliasing vector type avoids pulling hosted allocation
// headers into this freestanding build. It models the same SSE2 block loads.
typedef long long CopyBlock __attribute__((vector_size(16), aligned(1), may_alias));
static CopyBlock load_block(const unsigned char* p) {
    return *reinterpret_cast<const volatile CopyBlock*>(p);
}
static void store_block(unsigned char* p, CopyBlock value) {
    *reinterpret_cast<volatile CopyBlock*>(p) = value;
}
#endif

// Native member constructor: MSVC x86 uses thiscall automatically.
// No allocation, imports, refcount operations, FS registration or FP arithmetic.
Record48::Record48(const void* source) {
    // Do not eliminate the initialization: source may alias the destination.
    volatile uint32_t* destination = words;
    destination[0] = 0;
    destination[1] = 0;
    destination[2] = 0;
    destination[3] = 0;
    destination[4] = 0;
    destination[5] = 0;
    destination[6] = 0;
    destination[7] = 0;
    destination[8] = 0;
    destination[9] = 0;
    destination[10] = 0;
    destination[11] = 0;

    // Explicit block snapshots preserve the observed forward 16-byte copy,
    // including partial overlap. Neither memcpy nor memmove specifies this.
    const unsigned char* input = static_cast<const unsigned char*>(source);
    unsigned char* output = reinterpret_cast<unsigned char*>(words);
    CopyBlock block = load_block(input);
    store_block(output, block);
    block = load_block(input + 16);
    store_block(output + 16, block);
    block = load_block(input + 32);
    store_block(output + 32, block);
}
