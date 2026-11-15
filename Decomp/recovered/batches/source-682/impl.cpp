#include "impl.hpp"
#ifdef _MSC_VER
#include <xmmintrin.h>
#endif
namespace riff {
// Explicit scalar SSE preserves operand order for NaN payload selection and
// observes the caller's MXCSR rounding/denormal modes, as the original MULSS.
static float scaled(float scale, float coordinate) {
#ifdef _MSC_VER
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(scale), _mm_set_ss(coordinate)));
#else
    typedef float SseFloats __attribute__((vector_size(16)));
    const SseFloats a = {scale, 0, 0, 0};
    const SseFloats b = {coordinate, 0, 0, 0};
    return __builtin_ia32_mulss(a, b)[0];
#endif
}
// VA 0x47d1d0, 171 bytes. ECX=this; stack=(edge, &a, &b), ret 12.
// The vtable contains this address at 0x9fb180. No direct calls were found.
// Constructor at 0x47cd81 installs vtable 0x9fb128: this is slot +0x58.
// This is cyclic adjacency in stored point order, not a topological hull-edge
// search. There is no margin addition, bounds check, allocation, or callback.
void RIFF_THISCALL ConvexHull::edgeWithoutMargin(int32_t edge, Vector4& a, Vector4& b) {
    // Requires nonzero count, readable remainder-selected points and writable
    // outputs. INT_MIN % -1 traps in the original (not a normal-path contract).
    const int32_t count = vertexCount; // Original keeps this across output stores.
    const Vector4* p = vertices + edge % count;
    Vector4 value;
    value.x = scaled(scaling.x, p->x);
    value.y = scaled(scaling.y, p->y);
    value.z = scaled(scaling.z, p->z);
    value.w = 0.0f;
    a = value;
    // LEA in the original wraps at 32 bits, including INT_MAX -> INT_MIN.
    const int32_t next = static_cast<int32_t>(static_cast<uint32_t>(edge) + 1u);
    p = vertices + next % count;
    value.x = scaled(scaling.x, p->x);
    value.y = scaled(scaling.y, p->y);
    value.z = scaled(scaling.z, p->z);
    value.w = 0.0f;
    b = value;
}
}
