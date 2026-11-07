#include "impl.hpp"
namespace riff {
// ECX is the sole input; no meaningful return value is established by callers.
// All sixteen fields are overwritten without reading the previous contents.
// This is a three-axis basis with a zero fourth vector, not a 4x4 identity.
// Caller evidence: 0x46316b / 0x463180 initialize embedded +0x44 / +0x84;
// 0x45a9df initializes a stack temporary. Original routine has no dependencies.
void RIFF_THISCALL Matrix64::initialize_basis() {
    entries[0] = 1.0f;
    entries[1] = 0.0f;
    entries[2] = 0.0f;
    entries[3] = 0.0f;
    entries[4] = 0.0f;
    entries[5] = 1.0f;
    entries[6] = 0.0f;
    entries[7] = 0.0f;
    entries[8] = 0.0f;
    entries[9] = 0.0f;
    entries[10] = 1.0f;
    entries[11] = 0.0f;
    entries[12] = 0.0f;
    entries[13] = 0.0f;
    entries[14] = 0.0f;
    entries[15] = 0.0f;
}
}
