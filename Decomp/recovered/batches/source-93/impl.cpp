#include "impl.hpp"
// Game.exe [0x536160,0x536220), ECX=this, RET 8, EAX=this.
// Caller 0x535f82 appends a counted path prefix, then a backslash.
WideString* RIFF_THIS WideString::append_pointer(const uint16_t* source, uint32_t count) {
    // Integer comparisons preserve x86's unsigned address ordering, including
    // odd byte addresses (the original SAR rounds their offset down).
    const uintptr_t address = reinterpret_cast<uintptr_t>(source);
    const uintptr_t base = reinterpret_cast<uintptr_t>(data());
    const uintptr_t end = base + uint32_t(length * 2u);
    if (source && address >= base && address < end)
        return append_substring(this, uint32_t(address-base)/2u, count);
    // Strict comparison: equality would make the resulting length UINT32_MAX.
    if (0xffffffffu - length <= count)
        riff_length_error("string too long");
    if (count) {
        const uint32_t new_length = length + count;
        if (reserve(new_length, false)) {
            riff_copy(data() + length, source, uint32_t(count * 2u));
            set_length(new_length);
        }
    }
    return this;
}
