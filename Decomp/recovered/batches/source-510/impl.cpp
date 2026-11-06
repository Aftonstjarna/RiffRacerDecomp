#include "impl.hpp"
namespace riff {
uint8_t** transformBytes(uint8_t** result, const uint8_t* begin,
                         const uint8_t* end, uint8_t* destination,
                         ByteTransform callback) {
    // Unsigned address comparison, rather than undefined subtraction of
    // unrelated C++ pointers. The original is a 32-bit address-space routine.
    const uintptr_t first = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t last = reinterpret_cast<uintptr_t>(end);
    const uintptr_t count = first <= last ? last - first : 0;
    for (uintptr_t i = 0; i != count; ++i) {
        // Explicit sign extension is independent of the host's plain char mode.
        const unsigned byte = *begin;
        const int argument = byte < 128 ? static_cast<int>(byte)
                                       : static_cast<int>(byte) - 256;
        const int transformed = callback(argument);
        *destination = static_cast<uint8_t>(transformed);
        ++begin;
        ++destination;
    }
    *result = destination;
    return result;
}
}
