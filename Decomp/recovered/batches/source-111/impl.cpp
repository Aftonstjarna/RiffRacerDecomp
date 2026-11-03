#include "impl.hpp"
// Game.exe VA 0x44fb30..0x44fc27, RVA 0x4fb30, 247 bytes.
// ECX=this; source,position,count on stack; EAX=this; RET 12.
// Accepted assembly checked against direct Game.exe disassembly. Caller
// 0x44f9fb (assign-range alias path) passes this as source and an interior
// offset; prefix construction at 0x536099 passes position zero and a limit.
WideString* RIFF_THISCALL WideString::assign_substring(
    const WideString* source, uint32_t position, uint32_t count) {
    if (position > source->length)
        wide_out_of_range("invalid string position");
    const uint32_t remaining = source->length - position;
    const uint32_t selected = count < remaining ? count : remaining;
    if (source == this) {
        // Ordering matters: truncation writes a NUL at position+selected,
        // which can remain in the unused tail after prefix erasure.
        truncate(position + selected);
        erase(0, position);
        return this;
    }
    if (selected > 0x7ffffffeu)
        wide_length_error("string too long");
    if (capacity < selected) {
        grow(selected, length);
        if (!selected) return this; // Original post-growth zero arm.
    } else if (!selected) {
        length = 0;
        (capacity < 8 ? storage.local : storage.heap)[0] = 0;
        return this;
    }
    const uint16_t* input = source->capacity < 8
        ? source->storage.local : source->storage.heap;
    uint16_t* output = capacity < 8 ? storage.local : storage.heap;
    if (selected) wide_copy(output, input + position, selected * 2u);
    length = selected;
    // Original re-reads capacity/pointer after memcpy.
    (capacity < 8 ? storage.local : storage.heap)[selected] = 0;
    return this;
}
