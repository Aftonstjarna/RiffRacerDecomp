#include "impl.hpp"

// Game.exe VA 0x58eb00, RVA 0x18eb00, 59 bytes.
// Original takes a scalar header in ECX, returns int in EAX, and has no
// stack arguments, memory accesses, imports or object fields. A portable
// scalar API avoids pretending that ECX is an object pointer.
// Observed direct caller at 0x59018b supplies a local header word and gates
// a further parser call (0x58f460) on success. That parser is outside scope.
namespace riff {
int audio_frame_header_plausible(uint32_t header)
{
    if ((header & 0xffe00000u) != 0xffe00000u)
        return 0; // All eleven sync bits must be set.
    if ((header & 0x00060000u) == 0)
        return 0; // Layer value zero is reserved.
    if ((header & 0x0000f000u) == 0x0000f000u)
        return 0; // Bitrate index fifteen is reserved; zero is accepted.
    if ((header & 0x00000c00u) == 0x00000c00u)
        return 0; // Sample-rate index three is reserved.
    // Version, protection, padding, private, channel mode, mode extension,
    // copyright, original and emphasis bits are intentionally unchecked.
    return 1;
}
}
