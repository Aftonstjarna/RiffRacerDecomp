#include "impl.hpp"
namespace riff {
// Game.exe 0x43e7a0..0x43e7cb. Internal free-function ABI:
// ECX=first, EDX=last, caller-owned stack argument=destination; EAX=result.
// Callers at 0x43e3b6 and 0x43e412 pass vector-like begin/end pairs.
// Valid nonempty ranges must reach last by increments of exactly 12 bytes.
// No allocation, destruction, capacity checks, or ownership transfer occurs.
Record12* copy_assign_range(const Record12* first, const Record12* last,
                            Record12* destination) {
    while (first != last) {
        // Preserve the original two-stage assignment, including forward overlap.
        const uint64_t payload = first->payload;
        destination->payload = payload;
        const uint32_t tail = first->tail;
        destination->tail = tail;
        ++first;
        ++destination;
    }
    return destination;
}
}
