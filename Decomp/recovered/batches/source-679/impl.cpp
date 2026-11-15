#include "impl.hpp"
// Game.exe 0x4420b0..0x442162, thiscall, callee pops 12 argument bytes.
// append_range at 0x4421b4/0x4421ca dispatches here for an interior source
// pointer, passing this as source and converting the pointer to an offset.
NarrowString* RIFF_THISCALL NarrowString::append_substring(
    const NarrowString* source, uint32_t position, uint32_t count) {
    if (position > source->length) {
        narrow_position_error("invalid string position");
    }
    const uint32_t available = source->length - position;
    if (count > available) {
        count = available;
    }
    const uint32_t old_length = length;
    // Strict comparison: length+count must remain below UINT32_MAX.
    // This check precedes the zero-count return too.
    if (0xffffffffu - old_length <= count) {
        narrow_length_error("string too long");
    }
    if (count != 0 && prepare_capacity(old_length + count, false)) {
        // Reload after preparation: self-append can relocate inline/heap data.
        const char* from = source->capacity < 16 ? source->storage.local : source->storage.heap;
        char* to = capacity < 16 ? storage.local : storage.heap;
        narrow_copy(to + length, from + position, count);
        length = old_length + count;
        to = capacity < 16 ? storage.local : storage.heap;
        to[length] = 0;
    }
    return this;
}
