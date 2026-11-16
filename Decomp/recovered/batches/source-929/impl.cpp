#include "impl.hpp"

namespace {
// Interpret x86 two's-complement bits without signed overflow or an
// implementation-defined out-of-range unsigned-to-signed conversion.
int32_t signedValue(uint32_t bits) {
    if (bits <= 0x7fffffffu) return static_cast<int32_t>(bits);
    return -1 - static_cast<int32_t>(~bits);
}
int32_t status(uint32_t bits) {
    return (bits & 0x80000000u) ? -1 : 0;
}
}

// Original VA 0x58e330, 158 bytes; cdecl, NOT thiscall (both inputs are
// stack arguments and RET does not pop them). No calls, imports or FS use.
// The original normalizes all negative internal results, including -10, to -1.
// Only position is writable. Arithmetic deliberately wraps like x86 DWORDs.
extern "C" int32_t RIFF_CDECL audio_buffer_adjust_position(AudioBufferPosition* state, int32_t amount) {
    if (amount >= 0) {
        if (amount > signedValue(state->position)) return -1;
        state->position -= static_cast<uint32_t>(amount);
        return status(state->position);
    }
    if (amount == (-2147483647 - 1)) return -1;
    const uint32_t advance = static_cast<uint32_t>(-amount);
    const uint32_t available = state->bufferedEnd - state->position;
    if (signedValue(available) < static_cast<int32_t>(advance)) {
        state->position = state->checkpoint;
        return -1;
    }
    state->position += advance;
    if (status(state->position) < 0) return -1;
    return status(state->basePosition + state->position);
}

// Evidence: no direct CALL xrefs in original disassembly; pointer 0x58e330
// occurs at VA 0xbaf51c, slot +0x1c of callback table 0xbaf500. Table is
// installed at object+0x6d3c by 0x4f882b and 0x55dcc7. Concrete indirect
// invocations of this slot have not been uniquely identified. Nearby routine
// 0x58e2d0 advances using these same fields and returns the raw position/-10;
// it is evidence for names, not an implementation dependency.
