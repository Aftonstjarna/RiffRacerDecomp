#include "impl.hpp"
extern "C" void* memcpy(void*, const void*, size_t);
// Game.exe 0x55dd50..0x55dd82, cdecl, three stack arguments, plain ret.
// Registration at 0x55dcf5 stores this callback into decoder +0x6d64;
// 0x55dd3f passes the audio owner as decoder user data (EDX to 0x58e750).
// Adjacent seek callback 0x55dd90 also reads length/cursor at +0x30/+0x34.
extern "C" uint32_t RIFF_CDECL audio_memory_read_callback(
    AudioMemoryState* state, void* destination, uint32_t requested)
{
    const uint32_t remaining = state->length - state->cursor;
    const uint32_t count = requested > remaining ? remaining : requested;
    // Integer address addition models the original address arithmetic, including
    // a cursor beyond length. Caller must still supply valid copy addresses.
    const unsigned char* source = reinterpret_cast<const unsigned char*>(
        reinterpret_cast<uintptr_t>(state->data) + state->cursor);
    memcpy(destination, source, count); // original calls even when count is zero
    // Read cursor after copying: destination may alias the state itself.
    state->cursor += count;
    return count;
}
