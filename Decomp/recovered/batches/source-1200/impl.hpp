#ifndef SCRIPT_OPERAND_VALIDATE_HPP
#define SCRIPT_OPERAND_VALIDATE_HPP
#include <stdint.h>

// Only the two observed fields are identified. Names are descriptive, not original.
struct ScriptOperandContext {
    uint8_t unknown00[0x28];
    int32_t flagged_limit;
    uint8_t unknown2c[0x1f];
    uint8_t register_limit;
    int validate_operand(int32_t operand, int32_t type) const;
};
#endif
