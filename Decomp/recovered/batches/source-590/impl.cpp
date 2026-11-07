#include "impl.hpp"
namespace riff {
// Direct instructions and the call at 0x438815 establish these offsets and
// arithmetic, but not the original class name or physical units. The caller
// forms a three-component difference-of-products vector on its stack.
// All input components and transformed/scaled values precede the first store,
// so vector may point at accumulated, rows, scales, or other object storage.
void RIFF_THISCALL MatrixAccumulator::accumulate(const float* vector) {
    const float x = vector[0];
    const float y = vector[1];
    const float z = vector[2];
    // Explicit float steps retain scalar SSE rounding and association. No
    // translation column, homogeneous coordinate, normalization, or clamp.
    const float ax = row0[0] * x;
    const float ay = row0[1] * y;
    const float az = row0[2] * z;
    const float bx = row1[0] * x;
    const float by = row1[1] * y;
    const float bz = row1[2] * z;
    const float cx = row2[0] * x;
    const float cy = row2[1] * y;
    const float cz = row2[2] * z;
    const float axy = ay + ax;
    const float bxy = by + bx;
    const float cxy = cy + cx;
    const float a = axy + az;
    const float b = bxy + bz;
    const float c = cxy + cz;
    const float da = scale[0] * a;
    const float db = scale[1] * b;
    const float dc = scale[2] * c;
    accumulated[0] = accumulated[0] + da;
    accumulated[1] = accumulated[1] + db;
    accumulated[2] = accumulated[2] + dc;
}
}
