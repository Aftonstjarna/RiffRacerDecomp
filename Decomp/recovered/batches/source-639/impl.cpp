#include "impl.hpp"
namespace riff {
// Game.exe 0x437fe0..0x43801a, RVA 0x37fe0. Original internal ABI:
// ECX=first, EDX=last, stack[0]=destination, caller pops; EAX=result.
// Callers 0x437e21 and 0x5a93c4/0x5a93d7/0x5a93ec use this while
// relocating/inserting 12-byte elements in a vector-like allocation.
// No allocation, destruction, ownership adjustment, or exception setup occurs.
// Keep word stores ordered: a forward overlapping range can propagate data.
Record12* record12_range_copy_construct(const Record12* first,
                                       const Record12* last,
                                       Record12* destination) {
    uintptr_t source = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (source != end) {
        if (output != 0) {
            const Record12* from = reinterpret_cast<const Record12*>(source);
            Record12* to = reinterpret_cast<Record12*>(output);
            to->words[0] = from->words[0];
            to->words[1] = from->words[1];
            to->words[2] = from->words[2];
        }
        source += 12;
        output += 12;
    }
    return reinterpret_cast<Record12*>(output);
}
}
