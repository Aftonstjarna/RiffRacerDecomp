#include "impl.hpp"
#if defined(_MSC_VER)
#include <xmmintrin.h>
#endif
static float scaledComponent(float scale, float vertex) {
#if defined(_MSC_VER)
    // Preserve scalar SSE operand order, including two-NaN payload choice.
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(scale), _mm_set_ss(vertex)));
#elif defined(__SSE__)
    typedef float ScalarSse __attribute__((vector_size(16)));
    ScalarSse left = {scale, 0, 0, 0};
    ScalarSse right = {vertex, 0, 0, 0};
    return __builtin_ia32_mulss(left, right)[0];
#else
    return scale * vertex; // Non-SSE NaN payload and FP-environment parity unverified.
#endif
}
// Game.exe VA 0x47d280, RVA 0x7d280, 84 bytes. ECX=this;
// stack args index, output pointer; callee pops 8. Vtable pointer at
// 0x9fb184; no direct E8 callers found in the executable sections.
// No margin, count lookup, index modulo, allocation, or bounds check.
void RIFF_THISCALL ConvexHull::vertexWithoutMargin(int32_t index, HullVector& output) const {
    const HullVector& point = vertices[index];
    // Stage all components before writing: output may alias input storage.
    HullVector result;
    result.x = scaledComponent(localScaling.x, point.x);
    result.y = scaledComponent(localScaling.y, point.y);
    result.z = scaledComponent(localScaling.z, point.z);
    result.w = 0.0f;
    output = result;
}
