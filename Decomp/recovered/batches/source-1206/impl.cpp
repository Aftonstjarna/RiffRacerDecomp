#include "impl.hpp"

// Game.exe 0x486150: callers pass an instruction word loaded from an array.
// Bits 0..5 select the operation; bits 23..31 must all be zero. The meaning
// of the remaining instruction fields and operation names is not established.
uint32_t script_instruction_open_result(uint32_t instruction) {
    const uint32_t opcode = instruction & 0x3fu;
    return ((opcode >= 0x1cu && opcode <= 0x1eu) || opcode == 0x22u) &&
           (instruction & 0xff800000u) == 0u;
}
