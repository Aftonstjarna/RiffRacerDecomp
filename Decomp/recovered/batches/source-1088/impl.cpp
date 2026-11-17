#include "impl.hpp"
// 0x52c610, thiscall, one stack argument. A caller at 0x528e29 passes
// the vector at object+12 and a 20-byte local record. Its contents are opaque.
void Record20Vector::append(const void* source) {
    uintptr_t src = reinterpret_cast<uintptr_t>(source);
    uintptr_t first = reinterpret_cast<uintptr_t>(begin);
    uintptr_t last = reinterpret_cast<uintptr_t>(end);
    bool internal = src >= first && src < last;
    int32_t index = 0;
    if (internal) {
        // Original uses signed 32-bit byte difference divided by 20.
        index = static_cast<int32_t>(static_cast<uint32_t>(src - first)) / 20;
    }
    if (end == capacity_end) ensure_spare(end);
    if (internal) {
        src = reinterpret_cast<uintptr_t>(begin) + static_cast<uint32_t>(index) * 20u;
    }
    uintptr_t dst = reinterpret_cast<uintptr_t>(end);
    if (dst) {
        // The first 16 bytes are loaded before any of them are stored; the
        // final four are loaded afterwards. This matters for overlapping data.
        unsigned char chunk[16];
        for (unsigned i = 0; i != 16; ++i) chunk[i] = reinterpret_cast<const unsigned char*>(src)[i];
        for (unsigned i = 0; i != 16; ++i) reinterpret_cast<unsigned char*>(dst)[i] = chunk[i];
        unsigned char tail[4];
        for (unsigned i = 0; i != 4; ++i) tail[i] = reinterpret_cast<const unsigned char*>(src)[16+i];
        for (unsigned i = 0; i != 4; ++i) reinterpret_cast<unsigned char*>(dst)[16+i] = tail[i];
    }
    end = reinterpret_cast<unsigned char*>(dst + 20u);
}
