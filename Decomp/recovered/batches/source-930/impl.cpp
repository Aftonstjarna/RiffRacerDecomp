#include "impl.hpp"
namespace {
int32_t signedBits(uint32_t bits) {
    return bits <= 0x7fffffffu ? static_cast<int32_t>(bits) : -1-static_cast<int32_t>(~bits);
}
}
// Original 0x58e2d0..0x58e323. Both inputs are stack arguments, with plain
// RET: this is a cdecl callback, not a thiscall member. No calls or FS access.
// Pointer at 0xbaf514 is slot +0x14 of table 0xbaf500, installed at
// object+0x6d3c by 0x4f882b and 0x55dcc7. No direct CALL references found;
// specific indirect callers remain unresolved. Field names are inferred uses,
// not a claim that the complete decoder class declaration has been recovered.
extern "C" int32_t RIFF_CDECL audio_buffer_advance_position(AudioBufferPosition* state, int32_t amount) {
    if (amount < 0) return -1; // Does not even dereference state.
    const uint32_t available = state->bufferedEnd - state->position;
    if (signedBits(available) < amount) {
        state->position = state->checkpoint;
        return -10;
    }
    state->position += static_cast<uint32_t>(amount);
    if (state->position & 0x80000000u) return signedBits(state->position);
    return signedBits(state->basePosition + state->position);
}
// All arithmetic above wraps as x86 DWORD arithmetic, including malformed
// states. A negative updated position is returned raw without adding base.
