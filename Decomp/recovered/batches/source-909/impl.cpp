#include "impl.hpp"
#ifdef _MSC_VER
#include <xmmintrin.h>
static bool threshold_contains(float threshold, float distance) {
    return _mm_comige_ss(_mm_set_ss(threshold), _mm_set_ss(distance)) != 0;
}
#else
// Compiler SSE intrinsic without xmmintrin.h's optional libc dependency.
typedef float SseFloats __attribute__((vector_size(16)));
static bool threshold_contains(float threshold, float distance) {
    SseFloats a = {threshold, 0, 0, 0};
    SseFloats b = {distance, 0, 0, 0};
    return __builtin_ia32_comige(a, b) != 0;
}
#endif
// Game.exe 0x546a30..0x546aec, ECX=this, one pointer argument, ret 4;
// only AL is the Boolean result. Callers 0x4c27dc and 0x54c368 test AL.
// No writes or calls. Do not stop at the first hit: subsequent floating-point
// operations can still set MXCSR exception flags. The threshold is already
// squared; the original does not square it here. Vertex W is ignored in the
// distance scan, but participates in the final cached-vertex comparison.
bool RIFF_THISCALL SimplexSolver::contains_vertex(const SimplexVector* vertex) const {
    bool found = false;
    for (int32_t i = 0; i < vertex_count; ++i) {
        float dx = vertex->x - vertices[i].x;
        float dy = vertex->y - vertices[i].y;
        float dz = vertex->z - vertices[i].z;
        float xx = dx * dx;
        float yy = dy * dy;
        float zz = dz * dz;
        float distance = (yy + xx) + zz;
        // COMISS (including its masked invalid flag on quiet NaNs), not
        // an unordered comparison or an epsilon approximation.
        if (threshold_contains(distance_squared_threshold, distance))
            found = true;
    }
    // UCOMISS equality is ordered: even identical NaN bit patterns fail.
    if (vertex->w == cached_vertex.w && vertex->z == cached_vertex.z &&
        vertex->y == cached_vertex.y && vertex->x == cached_vertex.x)
        return true;
    return found;
}
