#include "impl.hpp"
// Original 0x425c40..0x425c7b, RVA 0x25c40. Free cdecl function, no
// object fields, imports, globals or FS accesses. Direct callers 0x4157b8
// and 0x415832 pass 0x200 bytes and ignore EAX. EAX happens to be zero
// for nonempty input and destination for empty input; no useful return
// contract is established, so this interface deliberately returns void.
extern "C" void RIFF_CDECL recovered_byte_widen_terminated(
    uint16_t* destination, const unsigned char* source, uint32_t destination_bytes)
{
    uint32_t remaining = destination_bytes >> 1;
    if (*source != 0) {
        do {
            if (remaining <= 1)
                break;
            const uint16_t value = *source;
            --remaining;
            ++source;
            *destination = value;
            ++destination;
            // Keep this read after the store: overlapping input can change.
        } while (*source != 0);
    }
    *destination = 0;
}
