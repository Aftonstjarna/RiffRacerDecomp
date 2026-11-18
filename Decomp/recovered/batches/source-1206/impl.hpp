#ifndef RIFF_SCRIPT_INSTRUCTION_OPEN_RESULT_HPP
#define RIFF_SCRIPT_INSTRUCTION_OPEN_RESULT_HPP
#include <stdint.h>

// The original receives the instruction word in ECX, not a pointer to an object.
// This portable interface expresses its value semantics.
uint32_t script_instruction_open_result(uint32_t instruction);
#endif
