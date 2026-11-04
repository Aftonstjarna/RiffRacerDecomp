#include "impl.hpp"
// Game.exe VA 0x415fe0..0x4160f7 (279 bytes), RVA 0x15fe0.
// ECX=this; source, offset, count on stack; EAX=this; RET 12.
// Direct original disassembly agrees with accepted narrow_assign_substring.S.
// Callers: pointer-range alias handling at 0x416564/0x41657a; full string
// copies at 0x43d03e/0x43d2bd use offset=0, count=UINT_MAX. Construction
// at 0x440ab9 first initializes length=0, capacity=15 and local[0]=0.
NarrowString* RIFF_THISCALL NarrowString::assign_substring(
    const NarrowString* source, uint32_t offset, uint32_t count) {
    if (offset > source->length)
        narrow_out_of_range("invalid string position");
    uint32_t selected = source->length - offset;
    if (count < selected) selected = count;
    if (source == this) {
        const uint32_t end = offset + selected;
        // Redundant for a valid object, but present in the original.
        if (end > length) narrow_out_of_range("invalid string position");
        length = end;
        (capacity < 16 ? storage.local : storage.heap)[end] = 0;
        // Do not replace this sequence with a single copy. The first NUL
        // can survive in the unused tail after the prefix is removed.
        erase(0, offset);
        return this;
    }
    if (selected > 0xfffffffeu) narrow_length_error("string too long");
    if (capacity < selected) {
        grow(selected, length);
        if (selected == 0) return this; // Original unreachable unsigned arm.
    } else if (selected == 0) {
        length = 0;
        (capacity < 16 ? storage.local : storage.heap)[0] = 0;
        return this;
    }
    const char* input = source->capacity < 16
        ? source->storage.local : source->storage.heap;
    char* output = capacity < 16 ? storage.local : storage.heap;
    if (selected) narrow_copy(output, input + offset, selected);
    length = selected;
    // The original re-reads storage selection after the copy call.
    (capacity < 16 ? storage.local : storage.heap)[selected] = 0;
    return this;
}
