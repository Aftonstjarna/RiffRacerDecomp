#include "impl.hpp"
namespace riff {
// Game.exe VA 0x58f460, RVA 0x18f460, 57 bytes. No object or memory access.
// Direct caller 0x590197 supplies headers from stack locals; the preceding
// call to 0x58eb00 checks the candidate's validity (outside this scope).
// Bits 31..17 and 11..10 must match: sync/version/layer/protection and
// sample-rate fields. Other differences, including bitrate and padding,
// are allowed. Channel modes 0, 1 and 2 are equivalent here; mode 3 (mono)
// must agree. No table lookups, allocation, exceptions or global state.
int RIFF_HEADER_CALL audio_frame_headers_compatible(uint32_t first, uint32_t second)
{
    if (((first ^ second) & 0xfffe0c00u) != 0)
        return 0;
    const bool first_mono = (first & 0xc0u) == 0xc0u;
    const bool second_mono = (second & 0xc0u) == 0xc0u;
    return first_mono == second_mono ? 1 : 0;
}
}
