#include "impl.hpp"
// Game.exe RVA 0x18dc60, VA [0x58dc60,0x58dc88). cdecl, not thiscall.
// Direct disassembly agrees with accepted audio_stream_read_exact.S.
// Tables 0xbaf4a0/4d0/500/530/560 contain this wrapper at +0x18;
// it delegates to their +8 slot. No direct CALL xrefs were found. Concrete
// indirect callers and original signedness/type names remain unresolved.
// This partial layout names only the dispatch field. The wrapper itself writes
// no fields; backend side effects survive success and failure alike. No retry,
// pointer validation, count validation or rollback is performed, even for zero.
extern "C" int32_t RIFF_CDECL audio_stream_read_exact(
    AudioStream* stream, void* destination, uint32_t count)
{
    const int32_t result = stream->backend->read(stream, destination, count);
    return static_cast<uint32_t>(result) == count ? result : -10;
}
