#include "impl.hpp"
namespace riff {
void RIFF_THISCALL BodyVectorAccumulator::accumulatePair(const float* vector, const float* arm) {
    // UCOMISS/LAHF/TEST 0x44/JNP skips equality, including either zero sign.
    // Unordered comparisons proceed. With DAZ, subnormal factors compare as zero.
    const float f = factor;
    if (f == 0.0f) return;
    const float z = componentScale[2] * vector[2];
    const float x = vector[0] * componentScale[0];
    const float y = componentScale[1] * vector[1];
    const float dx = f * x;
    const float dz = f * z;
    const float dy = f * y;
    firstSum[0] = firstSum[0] + dx;
    firstSum[1] = firstSum[1] + dy;
    firstSum[2] = firstSum[2] + dz;

    // The original tests this+0x218 for null, not the stored scale values.
    // A valid C++ object cannot wrap its field address to zero. No scale-zero
    // early out is valid: it would change NaNs and floating-point exceptions.
    // Reload vector AFTER firstSum writes: both arguments may alias the object.
    const float sy = componentScale[1] * vector[1];
    const float sz = componentScale[2] * vector[2];
    const float ay = arm[1];
    const float az = arm[2];
    const float sx = vector[0] * componentScale[0];
    const float cx = ay * sz - az * sy;
    const float cy = az * sx - arm[0] * sz;
    const float cz = arm[0] * sy - ay * sx;

    // Semantics of accepted dependency 0x4385f0, kept local to this operation.
    // Each row is (Y+X)+Z, then scale; all deltas precede any secondSum store.
    const float a = (rows[0][1] * cy + rows[0][0] * cx) + rows[0][2] * cz;
    const float b = (rows[1][1] * cy + rows[1][0] * cx) + rows[1][2] * cz;
    const float c = (rows[2][1] * cy + rows[2][0] * cx) + rows[2][2] * cz;
    const float da = transformedScale[0] * a;
    const float db = transformedScale[1] * b;
    const float dc = transformedScale[2] * c;
    secondSum[0] = secondSum[0] + da;
    secondSum[1] = secondSum[1] + db;
    secondSum[2] = secondSum[2] + dc;
}
// Callers observed directly: 0x43b86a copies two triples to stack; 0x4d62ae
// and 0x4d62d6 select input records with flag bits 1/2 and test body pointer.
// Additional calls occur in 0x4de3xx-0x4de5xx and at 0x4dfa26. They support
// two vector pointers and thiscall, not definitive force/torque terminology.
}
