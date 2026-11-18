#include "impl.hpp"

// VA 0x486180: original uses ECX=context, EDX=operand and a caller-cleaned
// stack argument for type. This ordinary member method exposes the semantics;
// its compiler-generated ABI is not the original custom register convention.
int ScriptOperandContext::validate_operand(int32_t operand, int32_t type) const {
    if (type == 0)
        return operand == 0;
    if (type == 2)
        return operand < static_cast<int32_t>(register_limit);
    if (type == 3) {
        if (operand & 0x100)
            return (operand & ~int32_t(0x100)) < flagged_limit;
        return operand < static_cast<int32_t>(register_limit);
    }
    return 1;
}
