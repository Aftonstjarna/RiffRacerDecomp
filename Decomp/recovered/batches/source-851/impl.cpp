#include "impl.hpp"
// Evidence: original Game.exe [0x4f5ff0,0x4f6032), accepted
// script_stream_refill.S. Callers at 0x4f64f7, 0x4f6c5e, 0x4f7039,
// 0x4f7516 and 0x4f7b0c use this after a post-decrement found no bytes.
// This method itself does not check or decrement the old remaining count.
int RIFF_THISCALL ScriptStream::refill() {
    uint32_t length;
    const unsigned char* buffer = reader(state, data, &length);
    if (!buffer || length == 0)
        return -1;
    cursor = buffer;
    remaining = length - 1;
    const int first = *buffer;
    cursor = buffer + 1;
    return first;
}
