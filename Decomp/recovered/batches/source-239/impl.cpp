#include "impl.hpp"
namespace riff {
// Original VA 0x415b60, 39 bytes. ECX=this; no arguments or return value.
// Callers at 0x4a38bc/0x4a38cb clean up adjacent 24-byte stack objects.
// Only capacity selects storage: length and pointer validity are not checked.
// Reset happens AFTER delete returns; bytes 1..15 of storage survive unchanged.
// This is explicit cleanup, not a C++ destructor, so callers may inspect/reuse
// the reset object without a second automatic cleanup.
void NarrowString::destroy() {
    if (capacity >= 16u)
        scalar_delete(storage.heap);
    capacity = 15u;
    length = 0u;
    storage.inline_bytes[0] = '\0';
}
}
