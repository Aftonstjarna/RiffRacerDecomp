#include "impl.hpp"

void* record56_range_transfer(const void* first, const void* last, void* destination) {
    uintptr_t src = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t dst = reinterpret_cast<uintptr_t>(destination);
    while (src != end) {
        if (dst != 0) {
            const unsigned char* s = reinterpret_cast<const unsigned char*>(src);
            unsigned char* d = reinterpret_cast<unsigned char*>(dst);
            // Each group is loaded before it is stored, matching the original's
            // 16-byte load followed by nine 4-byte loads and two byte loads.
            unsigned char group[16];
            unsigned i;
            for (i = 0; i < 16; ++i) group[i] = s[i];
            for (i = 0; i < 16; ++i) d[i] = group[i];
            for (unsigned offset = 16; offset < 52; offset += 4) {
                for (i = 0; i < 4; ++i) group[i] = s[offset + i];
                for (i = 0; i < 4; ++i) d[offset + i] = group[i];
            }
            d[52] = s[52];
            d[53] = s[53];
        }
        src += 56;
        dst += 56;
    }
    return reinterpret_cast<void*>(dst);
}
