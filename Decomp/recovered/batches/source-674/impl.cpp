#include "impl.hpp"
// Game.exe VA 0x443110..0x44313b. ECX=this, EDX=channel, AL=result.
// Call sites: 0x44a75e, 0x44a7da, 0x44b362, 0x44b3fa.
// No calls, stores, stack arguments, or FS access. Only AL is a result;
// upper EAX bits in the original are incidental and are not a uint32 return.
bool RIFF_FASTCALL ObjectFlags::channel_enabled(uint32_t channel) const {
    if ((flags & 7u) != 7u)
        return false;
    return (channel_mask & (uint32_t(1) << (channel & 31u))) != 0;
}
