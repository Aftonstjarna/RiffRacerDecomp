#include "impl.hpp"
// Direct callers at 0x4bda9b and 0x4bdab6 pass EDI as rhs and consume
// XMM0 with MOVSS. This is a scalar dot of matrix rows selected by the
// neighboring 0x438410 helper (16-byte stride); no fourth float is read here.
namespace riff {
#ifndef _MSC_VER
static __m128 _mm_load_ss(const float* p) { return __m128{*p, 0.0f, 0.0f, 0.0f}; }
static __m128 _mm_mul_ss(__m128 a, __m128 b) { return __builtin_ia32_mulss(a,b); }
static __m128 _mm_add_ss(__m128 a, __m128 b) { return __builtin_ia32_addss(a,b); }
#endif
__m128 RIFF_THISCALL Vector3::dot_sse(const Vector3* rhs) const {
    // Preserve operand order (including NaN selection), rounding at each
    // operation, and MXCSR behavior. No fused operations or reassociation.
    const __m128 px = _mm_mul_ss(_mm_load_ss(&rhs->x), _mm_load_ss(&x));
    const __m128 py = _mm_mul_ss(_mm_load_ss(&rhs->y), _mm_load_ss(&y));
    const __m128 xy = _mm_add_ss(py, px);
    const __m128 pz = _mm_mul_ss(_mm_load_ss(&rhs->z), _mm_load_ss(&z));
    return _mm_add_ss(xy, pz);
}
}
