#include "impl.hpp"
namespace riff {
uintptr_t copy_record513_range(const Record513* first, const Record513* last,
                               uintptr_t destination) {
    uintptr_t source = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    while (source != end) {
        if (destination != 0) {
            const unsigned char* input = reinterpret_cast<const unsigned char*>(source);
            unsigned char* output = reinterpret_cast<unsigned char*>(destination);
            // Original copies 128 dwords followed by one byte. Nonoverlapping
            // storage is the supported contract; this is not a memmove.
            for (unsigned i = 0; i != 513; ++i) output[i] = input[i];
        }
        source += 513;
        destination += 513;
    }
    return destination;
}
}
