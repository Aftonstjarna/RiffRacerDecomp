#include "impl.hpp"
extern "C" void* memcpy(void*, const void*, size_t);
namespace recovered {
// VA 0x58f4a0, thiscall, no explicit arguments, integer result.
// Caller 0x58f57a branches to its ready-frame path only when the result is 1.
int AudioFrame::reuse_buffered() {
    if (frame_count == 0) return 0;
    if (repeats == 0) {
        repeats = frame_count - 1u;
        return 0;
    }
    uint8_t* destination = buffered;
    flag_b = 1;
    flag_a = 1;
    --repeats; // Deliberately unsigned: all nonzero 32-bit values take this path.
    bit_offset = 0;
    cursor = destination;
    if (mode == 3) memcpy(destination, saved_bytes, copy_size);
    if (read_prefix != 0) prefix = read16();
    return 1;
}
}
