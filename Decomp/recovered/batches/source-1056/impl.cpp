#include "impl.hpp"

// Game.exe 0x5a9680: thiscall, one unsigned count argument, ret 4.
// The x86 subtraction wraps before interpreting the difference as signed.
uint32_t Record6Storage::capacity_growth(uint32_t requested) const {
    const uint32_t difference = allocation_end_address - begin_address;
    // Signed division by six, truncated toward zero, expressed using unsigned
    // arithmetic so even the wrapped and negative cases are well-defined.
    const uint32_t capacity = (difference & 0x80000000u)
        ? 0u - ((0u - difference) / 6u) : difference / 6u;
    const uint32_t half = capacity / 2u;
    const uint32_t grown = (0x2aaaaaaau - half < capacity)
        ? 0u : capacity + half;
    return grown < requested ? requested : grown;
}
