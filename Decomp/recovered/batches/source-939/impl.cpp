#include "impl.hpp"

// Game.exe direct disassembly and accepted audio_stream_commit_position.S agree.
// The callback occupies +0x2c in tables 0xbaf500/530/560, referenced by the
// stream's +0x6d3c dispatch pointer. Callers at 0x58f59e, 0x58f8f0,
// 0x58fa60 and 0x58fab5 push the stream, clean the stack and ignore EAX.
// The returned word below preserves the observed EAX, without claiming that
// the original source declared a return value. No validation or null check
// exists in the original. Field names describe observed accounting, not units.
extern "C" uint32_t RIFF_CDECL audio_stream_commit_position(riff::AudioStream* stream)
{
    stream->buffer.commitConsumed();
    // Both reads must follow the helper: it can change both operands while
    // committing complete blocks. Unsigned arithmetic preserves ADD wraparound.
    const uint32_t position = stream->buffer.committedBase + stream->buffer.position;
    stream->committedPosition = position;
    return position;
}
