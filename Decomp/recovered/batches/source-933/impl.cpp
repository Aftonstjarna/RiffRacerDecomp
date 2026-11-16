#include "impl.hpp"
// Game.exe VA 0x55dd90, RVA 0x15dd90, 61 bytes (padding excluded).
// Registered at 0x55dcff in decoder +0x6d68; context passed from +0x6d4c.
// Indirect calls at 0x58d915, 0x58dcff and 0x58dd93 clean up 12 bytes:
// this is a free cdecl callback, not a thiscall member.
// Only +0x34 is written. No clamping, allocation, imports or error path.
// A valid context is required even for an unrecognized origin.
extern "C" uint32_t RIFF_CDECL audio_memory_seek_callback(
    AudioMemoryState* state, int32_t displacement, int32_t origin)
{
    const uint32_t offset = static_cast<uint32_t>(displacement);
    switch (origin) {
    case 0: state->position = offset; break;
    case 1: state->position += offset; break;
    case 2: state->position = state->length + offset; break;
    default: break;
    }
    // Unsigned arithmetic preserves the original modulo-2^32 ADD behavior,
    // including negative displacements and signed overflow boundaries.
    return state->position;
}
