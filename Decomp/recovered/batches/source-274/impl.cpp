#include "impl.hpp"
// Game.exe RVA 0x16520, VA 0x416520..0x416617. ECX=this,
// source/count on stack, EAX=this, RET 8. Layout is 24 bytes on i386;
// capacity >=16 selects pointer storage, length/capacity at +16/+20.
// Callers include literal/count assignment at 0x413b5c and pointer-range
// assignment at 0x414023. No local exception registration occurs here.
NarrowString* RIFF_THISCALL NarrowString::assign_range(const char* source, uint32_t count) {
    char* base = capacity >= 16 ? storage.heap : storage.local;
    // Integer comparisons model the original unsigned address comparisons,
    // including its exclusive end. A terminator pointer is NOT an alias here.
    const uintptr_t address = reinterpret_cast<uintptr_t>(source);
    const uintptr_t begin = reinterpret_cast<uintptr_t>(base);
    if (source && address >= begin && address < begin + length) {
        return assign_substring(this, static_cast<uint32_t>(address - begin), count);
    }
    // Only UINT_MAX is rejected; alias delegation precedes this check and
    // therefore permits UINT_MAX as a clamped substring count.
    if (count > 0xfffffffeu) {
        narrow_length_error("string too long");
    }
    if (capacity < count) {
        grow(count, length);
        // The original has this early return even though count==0 cannot
        // trigger growth for a valid unsigned capacity.
        if (count == 0) return this;
    }
    if (count != 0) {
        base = capacity >= 16 ? storage.heap : storage.local;
        narrow_copy(base, source, count);
    }
    length = count;
    base = capacity >= 16 ? storage.heap : storage.local;
    base[count] = '\0';
    return this;
}
