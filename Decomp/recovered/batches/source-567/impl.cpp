#include "impl.hpp"
namespace riff {
Record68* record68_range_copy(const Record68* first, const Record68* last,
                              Record68* destination) {
    // Integer cursors retain the observed null-destination skip and 32-bit
    // address arithmetic without C++ arithmetic on a null pointer.
    uintptr_t source = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (source != end) {
        if (output != 0) {
            const Record68* from = reinterpret_cast<const Record68*>(source);
            Record68* to = reinterpret_cast<Record68*>(output);
            // Preserve forward scalar load/store order, including overlap effects.
            for (unsigned i = 0; i != 13; ++i)
                to->fields[i] = from->fields[i];
            // Original MOVDQU loads the entire final block before storing it.
            const uint32_t a = from->tail[0], b = from->tail[1];
            const uint32_t c = from->tail[2], d = from->tail[3];
            to->tail[0] = a; to->tail[1] = b;
            to->tail[2] = c; to->tail[3] = d;
        }
        source += 68;
        output += 68;
    }
    return reinterpret_cast<Record68*>(output);
}
}
// Evidence: sole direct caller 0x509e05 in the reallocation routine uses
// container [0]=begin, [4]=end, pushes newly allocated storage, then adds 16
// to ESP (destination plus caller padding/other argument). No calls/imports,
// allocation, FS registration, floating arithmetic, or record destructor here.
