#include "impl.hpp"

void* record12_copy_range(const void* begin, const void* end, void* destination)
{
    uintptr_t source = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t finish = reinterpret_cast<uintptr_t>(end);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (source != finish) {
        if (output != 0) {
            const unsigned char* from = reinterpret_cast<const unsigned char*>(source);
            unsigned char* to = reinterpret_cast<unsigned char*>(output);
            // The original MOVQ snapshots eight bytes before storing them.
            // The last four bytes are read only AFTER that store (overlap matters).
            unsigned char first[8];
            for (unsigned i = 0; i != 8; ++i) first[i] = from[i];
            for (unsigned i = 0; i != 8; ++i) to[i] = first[i];
            unsigned char last[4];
            for (unsigned i = 0; i != 4; ++i) last[i] = from[8 + i];
            for (unsigned i = 0; i != 4; ++i) to[8 + i] = last[i];
        }
        source += 12;
        output += 12;
    }
    return reinterpret_cast<void*>(output);
}
// Original uses ECX=begin, EDX=end, stack=destination, caller cleanup.
// Callers 0x429b91 and 0x43e45f use vector-like begin/end fields at +0/+4.
// The latter stores EAX into a destination end field. No other object fields
// or ownership operations occur here. No record field interpretation is known.
// A null destination skips only that iteration; it still advances by 12.
// Invalid/unreachable bounds and wrapping addresses are not made safe here.
