#include "impl.hpp"
namespace riff {
Record48* record48_range_copy_retain(const Record48* first, const Record48* last, Record48* destination) {
    // Integer arithmetic expresses the original 32-bit address advancement,
    // including the skipped first write when destination is null.
    uintptr_t src = reinterpret_cast<uintptr_t>(first);
    uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t dst = reinterpret_cast<uintptr_t>(destination);
    while (src != end) {
        if (dst) {
            const Record48* from = reinterpret_cast<const Record48*>(src);
            Record48* to = reinterpret_cast<Record48*>(dst);
            for (unsigned i = 0; i != 4; ++i) {
                RetainedHeader* p = from->retained[i];
                to->retained[i] = p;
                if (p) ++p->references;
            }
            for (unsigned i = 0; i != 8; ++i) to->words[i] = from->words[i];
        }
        src += 48;
        dst += 48;
    }
    return reinterpret_cast<Record48*>(dst);
}
}
