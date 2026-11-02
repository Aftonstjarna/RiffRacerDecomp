#include "impl.hpp"
namespace riff {
// Original 0x4268f0..0x426930: cdecl, caller pops arguments. Caller
// 0x44eb9f supplies two extra unused allocator/tag arguments and separately
// frees the backing array. No this pointer, return value, or local EH cleanup.
// Only equality terminates traversal; invalid/reversed ranges are not checked.
void destroy_narrow_range(NarrowString32* first, NarrowString32* last, Delete release) {
    while (first != last) {
        if (first->capacity >= 16u) {
            unsigned address = 0;
            for (unsigned i = 0; i < 4; ++i)
                address |= unsigned(first->storage[i]) << (8 * i);
            release(reinterpret_cast<void*>(address));
        }
        // Ordering matters: the dependency sees the original element state.
        first->capacity = 15;
        first->size = 0;
        first->storage[0] = 0;
        ++first;
    }
}
}
// Other inspected original call sites include 0x42640a (array disposal),
// 0x42647c (tail erasure, then updates end), 0x426741 (stdcall wrapper),
// and 0x48dd66 (clear, retains allocation). All pass begin/end on stack;
// none requires the range destructor to free array storage or update end.
