#include "impl.hpp"
namespace riff {
// Original 0x4f03e0..0x4f0457. ECX=this, EDX=histogram, EAX=result.
// Slot indices are one-based here: bucket 0 covers 1, bucket 1 covers 2,
// bucket 2 covers 3..4, then 5..8, etc. Only tag != 0 means occupied;
// payload bits do not participate. The original caps processing at bucket 26.
uint32_t RIFF_FASTCALL ScriptTable::countArrayHistogram(uint32_t* histogram) const {
    uint32_t total = 0;
    int32_t next = 1;
    int32_t upper = 1;
    for (int bucket = 0; bucket <= 26; ++bucket) {
        int32_t end = upper;
        if (upper > arraySize) {
            end = arraySize;
            if (next > end)
                return total;
        }
        uint32_t occupied = 0;
        if (next <= end) {
            const ScriptArraySlot* slot = array + (next - 1);
            int32_t remaining = end - next + 1;
            next += remaining;
            do {
                if (slot->tag != 0)
                    ++occupied;
                ++slot;
            } while (--remaining != 0);
        }
        upper += upper;
        histogram[bucket] += occupied; // modulo 2^32, including prefilled bins
        total += occupied;
    }
    return total;
}
}
