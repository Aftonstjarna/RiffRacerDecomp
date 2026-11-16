#include "impl.hpp"
namespace riff {
static_assert(offsetof(AudioStream, backend) == 0x6d3c, "stream layout");
static_assert(offsetof(AudioBackend, read) == 2 * sizeof(void (*)()), "backend layout");
// Direct Game.exe disassembly agrees with accepted audio_stream_shift_byte.S.
// Tables at 0xbaf4a0/0xbaf4d0/0xbaf500/0xbaf530 contain this function
// at +0x10, and the stream points to a backend table at +0x6d3c.
// The original uses a byte in its incoming stream argument's stack slot as
// scratch. A local byte preserves the defined callback contract without
// exposing that compiler-specific stack arrangement.
int32_t RIFF_CDECL audio_stream_shift_byte(AudioStream* stream, uint32_t* accumulator) {
    unsigned char byte;
    const int32_t count = stream->backend->read(stream, &byte, 1);
    if (count == -10) return -10;
    if (count != 1) return 0;
    // Read accumulator AFTER callback: callbacks can alter it or stream fields.
    *accumulator = (*accumulator << 8) | static_cast<uint32_t>(byte);
    return 1;
}
}
