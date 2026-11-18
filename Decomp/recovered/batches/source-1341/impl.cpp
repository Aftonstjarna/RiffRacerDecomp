#include "impl.hpp"

void* worker_record40_range_transfer(const void* begin, const void* end, void* destination)
{
    uintptr_t source = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t finish = reinterpret_cast<uintptr_t>(end);
    uintptr_t target = reinterpret_cast<uintptr_t>(destination);
    while (source != finish) {
        if (target != 0) {
            const unsigned char* from = reinterpret_cast<const unsigned char*>(source);
            unsigned char* to = reinterpret_cast<unsigned char*>(target);
            // Preserve the original load/store grouping even for overlapping ranges.
            unsigned char first[16];
            for (unsigned i = 0; i != 16; ++i) first[i] = from[i];
            for (unsigned i = 0; i != 16; ++i) to[i] = first[i];
            for (unsigned offset = 16; offset != 40; offset += 4) {
                unsigned char field[4];
                for (unsigned i = 0; i != 4; ++i) field[i] = from[offset + i];
                for (unsigned i = 0; i != 4; ++i) to[offset + i] = field[i];
            }
        }
        source += 40;
        target += 40;
    }
    return reinterpret_cast<void*>(target);
}
