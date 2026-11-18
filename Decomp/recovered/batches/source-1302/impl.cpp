#include "impl.hpp"

Record40* record40_range_copy(const Record40* first, const Record40* last,
                              Record40* destination) {
    // Integer address arithmetic also describes the original's null destination
    // special case: it skips that record and advances the address by 40.
    uintptr_t dst = reinterpret_cast<uintptr_t>(destination);
    while (first != last) {
        if (dst != 0) {
            uint32_t* out = reinterpret_cast<uint32_t*>(dst);
            for (unsigned i = 0; i != 10; ++i)
                out[i] = first->words[i];
        }
        ++first;
        dst += 40;
    }
    return reinterpret_cast<Record40*>(dst);
}
