#include "impl.hpp"

uint32_t RIFF_REGISTER_CALL FlagSelectedProduct::selected_product(uint32_t multiplier) const
{
    // IMUL retains only its low 32 bits, regardless of operand signedness.
    // Unsigned multiplication and shift preserve that behavior without C++ UB.
    if ((flags & 0x4000u) != 0)
        return (common_factor * multiplier) << 2;
    return common_factor * ordinary_factor * multiplier;
}
