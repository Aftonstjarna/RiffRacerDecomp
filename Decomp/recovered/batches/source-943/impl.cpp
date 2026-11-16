#include "impl.hpp"

// Original Game.exe VA [0x58dc90,0x58dcb9), RVA 0x18dc90.
// One stack argument, caller cleanup, EAX result: cdecl, not thiscall.
// Original operation tables at 0xbaf4a0/4d0/500/530/560 hold this
// routine at +0x24. E.g. callers 0x58dba8, 0x58dbe2, 0x58dc32 load
// the table from stream+0x6d3c and push the stream, cleaning the stack.
// Direct disassembly agrees with accepted audio_stream_query_position.S.
// No helper calls, synchronization, validation, or exceptional path occurs.
// A valid stream is required; null/invalid pointers have no defined recovery.
extern "C" uint32_t RIFF_CDECL audio_stream_query_position(AudioStream* stream)
{
    if ((stream->flags & 0x08u) != 0) {
        // Unsigned arithmetic deliberately preserves x86 ADD modulo 2^32.
        stream->cachedPosition = stream->bufferBasePosition + stream->bufferOffset;
    }
    return stream->cachedPosition;
}
