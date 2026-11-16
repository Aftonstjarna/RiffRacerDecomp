#include "impl.hpp"
// Original VA 0x58e2a0..0x58e2c8, cdecl, three stack arguments.
// Callback pointer is stored at 0xbaf508 (table 0xbaf500, slot +8).
// Setup at 0x4f882b and 0x55dcc7 installs that table at stream+0x6d3c.
// The callback itself only accesses the embedded buffer at +0x6d7c.
// No rollback on a short read: preserve all dependency side effects.
extern "C" int32_t RIFF_CDECL audio_buffered_read_exact_callback(
    BufferedAudioStream* stream, void* destination, int32_t count) {
    const int32_t result = stream->buffer.read_range(destination, count);
    if (result < 0 || result == count) return result;
    return -1;
}
