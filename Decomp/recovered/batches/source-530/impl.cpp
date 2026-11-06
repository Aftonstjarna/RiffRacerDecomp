#include "impl.hpp"
namespace riff {
// Game.exe VA 0x426fa0, 43 bytes. ECX=this, stack=(output,column),
// EAX=output, callee removes 8 bytes. No calls or floating-point operations.
// Output represents (m[0][column],m[1][column],m[2][column],+0).
// Keep the original load/store order, including for overlapping buffers.
// No index validation exists in the original. Valid memory is required.
uint32_t* RIFF_THISCALL Matrix::column3(uint32_t* output, uint32_t column) const {
    output[3] = 0;
    output[0] = words[column];
    const uint32_t y = words[column + 4];
    const uint32_t z = words[column + 8];
    output[1] = y;
    output[2] = z;
    return output;
}
}
