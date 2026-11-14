#include "impl.hpp"
// Direct Game.exe disassembly and accepted random_range_inclusive.S agree.
// The only touched field is the state word at this+0. The observed direct
// caller at 0x432d52 uses this=edi+0x36c, lower=0, upper=count-derived-1.
// No allocation, global RNG, imports, floating point, or FS access occurs.
uint32_t RiffRandom::inclusive(uint32_t lower, uint32_t upper) {
    const uint32_t mixed = state * 39u + 0x27a39e8fu;
    // Original SAR 19 followed by AND 0x1fff is equivalent to logical shift.
    state = (mixed << 13) | (mixed >> 19);
    const uint32_t width = upper - lower + 1u;
    // Deliberately no sorting/clamping. Width zero is outside the portable
    // contract: original DIV faults, after storing the updated state.
    return lower + ((state & 0x7fffffffu) % width);
}
