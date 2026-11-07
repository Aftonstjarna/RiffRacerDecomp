#ifndef RIFF_VECTOR3_DOT_HPP
#define RIFF_VECTOR3_DOT_HPP
#ifdef _MSC_VER
#include <xmmintrin.h>
#else
// GCC SSE value type, without allocator/CRT dependencies from xmmintrin.h.
typedef float __m128 __attribute__((vector_size(16), aligned(16)));
#endif
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
// Only offsets 0,4,8 are established. No alignment or fourth field is assumed.
struct Vector3 {
    float x, y, z;
    // Original 0x4383e0, 46 bytes: ECX=this, stack rhs, callee pops 4.
    // An SSE return models the observed XMM0 ABI; ordinary float would use
    // ST(0) on i386. The result is in lane zero; other lanes are zero.
    __m128 RIFF_THISCALL dot_sse(const Vector3* rhs) const;
};
}
#endif
