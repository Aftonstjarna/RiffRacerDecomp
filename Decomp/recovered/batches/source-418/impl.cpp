#include "impl.hpp"

// Original: ECX=this, one uint32_t stack argument, callee RET 4, no
// meaningful return value. Capacity is compared unsigned against 16.
// Call sites 0x441022, 0x47ac2b and 0x47ad4d finalize copied string data;
// 0x868a60 and 0x8d3ba1 reset length to zero after setting capacity to 15.
// This primitive neither validates capacity nor allocates/frees storage.
// Caller must supply a writable terminator location. Invalid pointers and
// out-of-object inline indices are outside the portable C++ contract.
void RIFF_THISCALL NarrowString::set_length(uint32_t new_length) {
    const bool heap = capacity >= 16u;
    length = new_length;
    if (heap)
        storage.heap_data[new_length] = '\0';
    else
        storage.inline_data[new_length] = '\0';
}
