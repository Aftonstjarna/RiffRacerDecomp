#include "impl.hpp"

// Callers at 0x4b2881 and 0x543437..0x5434b6 use vector-like begin/end
// fields and 24-byte strides. No record field types or ownership are known.
// Each load group precedes its store; this is NOT a memmove operation.
unsigned char* record24_range_copy(const void* first, const void* last, void* destination)
{
    uintptr_t source = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (source != end) {
        if (output != 0) {
            const unsigned char* in = reinterpret_cast<const unsigned char*>(source);
            unsigned char* out = reinterpret_cast<unsigned char*>(output);
            unsigned char head[16];
            for (unsigned i = 0; i < 16; ++i) head[i] = in[i];
            for (unsigned i = 0; i < 16; ++i) out[i] = head[i];
            unsigned char tail[8];
            for (unsigned i = 0; i < 8; ++i) tail[i] = in[16+i];
            for (unsigned i = 0; i < 8; ++i) out[16+i] = tail[i];
        }
        source += 24;
        output += 24;
    }
    return reinterpret_cast<unsigned char*>(output);
}
