#include "impl.hpp"
// Game.exe 0x415b90..0x415bc6. ECX=this, one stack argument,
// callee pops 4 bytes, EAX is the range helper's result. Callers at
// 0x4311a1 and 0x44d6ec pass a terminated pointer and destination in ECX.
// No direct field writes, allocation or null-pointer check occur here.
// A readable NUL-terminated source is required, even for an empty assignment.
NarrowString* RIFF_THISCALL NarrowString::assign_terminated(const char* source) {
    uint32_t count = 0;
    if (*source != '\0') {
        const char* end = source;
        do { ++end; } while (end[-1] != '\0');
        count = static_cast<uint32_t>(end - (source + 1));
    }
    return assign_range(source, count);
}
