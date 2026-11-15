#include "impl.hpp"

void* record32_copy_construct_range(const void* begin, const void* end, void* destination)
{
    uintptr_t source = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t finish = reinterpret_cast<uintptr_t>(end);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    // Integer cursors preserve the original null-placement guard and advance.
    // A null destination skips only that record, not the entire range.
    while (source != finish) {
        if (output != 0) {
            const unsigned char* from = reinterpret_cast<const unsigned char*>(source);
            unsigned char* to = reinterpret_cast<unsigned char*>(output);
            unsigned char prefix[16];
            for (unsigned i = 0; i != 16; ++i) prefix[i] = from[i];
            for (unsigned i = 0; i != 16; ++i) to[i] = prefix[i];
            // Each word is read after the preceding store, as in the original.
            for (unsigned offset = 16; offset != 32; offset += 4) {
                unsigned char word[4];
                for (unsigned i = 0; i != 4; ++i) word[i] = from[offset + i];
                for (unsigned i = 0; i != 4; ++i) to[offset + i] = word[i];
            }
        }
        source += 32;
        output += 32;
    }
    return reinterpret_cast<void*>(output);
}
// Callers at 0x5200c4 and 0x52095e..0x5209cb use this for allocation/
// insertion copies, with destination passed on the stack and caller cleanup.
// No ownership, allocation, destruction, FS registration or external effects.
