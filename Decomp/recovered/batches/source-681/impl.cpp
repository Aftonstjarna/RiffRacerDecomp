#include "impl.hpp"
#ifdef _MSC_VER
#include <xmmintrin.h>
#endif
namespace riff {
static bool orderedGreater(float a, float b) {
#ifdef _MSC_VER
    return _mm_comigt_ss(_mm_set_ss(a), _mm_set_ss(b)) != 0;
#elif defined(__i386__) || defined(__x86_64__)
    typedef float SseVector __attribute__((vector_size(16)));
    SseVector x={a,0,0,0}, y={b,0,0,0};
    return __builtin_ia32_comigt(x,y) != 0;
#else
    return a>b;
#endif
}
// Original 0x47d0c0..0x47d1b9, vtable 0x9fb128 + 0x40.
// Constructor 0x47cd40 stores that vtable and builds the vertex array at +0x58.
// A three-argument virtual caller is visible at 0x4644e4 (count pushed first).
// No margin, normalization, allocation, or hull mutation occurs here.
void RIFF_THISCALL ConvexHull::batchedSupportWithoutMargin(
    const Vector4* directions, Vector4* support, int32_t directionCount) const {
    // The immediate 0xdd5e0b6b is the float rounding of -1e18.
    for (int32_t j=0; j<directionCount; ++j) support[j].w=-1.0e18f;
    for (int32_t i=0; i<vertexCount; ++i) {
        // Volatile rounding points preserve scalar single-precision evaluation,
        // including the original scaling work when directionCount <= 0.
        const volatile float x=vertices[i].x*localScaling.x;
        const volatile float y=vertices[i].y*localScaling.y;
        const volatile float z=vertices[i].z*localScaling.z;
        for (int32_t j=0; j<directionCount; ++j) {
            const volatile float dx=directions[j].x*x;
            const volatile float dy=directions[j].y*y;
            const volatile float dz=directions[j].z*z;
            const volatile float xy=dx+dy;
            const float dot=xy+dz;
            // COMISS + JBE: unordered and equal scores do not replace a winner.
            if (orderedGreater(dot,support[j].w)) {
                support[j].x=x;
                support[j].y=y;
                support[j].z=z;
                support[j].w=dot;
            }
        }
    }
}
}
