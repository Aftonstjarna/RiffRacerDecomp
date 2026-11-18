#include "impl.hpp"
// Game.exe 0x5c2140: the pointer differences are 32-bit unsigned machine
// arithmetic, including the special null cases. The helpers own validation,
// allocation, overlap handling, termination and exceptions.
NarrowString* RIFF_THISCALL NarrowString::replace_range(const char* first, const char* last, const char* source_first, const char* source_last) {
    const char* base = capacity < 16 ? storage.local : storage.heap;
    uint32_t offset = first ? (uint32_t)((uintptr_t)first - (uintptr_t)base) : 0;
    uint32_t count = last ? (uint32_t)((uintptr_t)last - (uintptr_t)first) : 0;
    if (source_first == source_last)
        erase(offset, count);
    else
        replace(offset, count, source_first, (uint32_t)((uintptr_t)source_last - (uintptr_t)source_first));
    return this;
}
