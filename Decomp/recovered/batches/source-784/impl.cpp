#include "impl.hpp"
#include <stddef.h>
static_assert(offsetof(ScriptTable, array) == 0x0c, "32-bit table layout required");
static_assert(offsetof(ScriptTable, hash) == 0x10, "hash offset");
static_assert(offsetof(ScriptTable, arraySize) == 0x1c, "size offset");
// Game.exe RVA 0xf0e90, VA 0x4f0e90, 82 bytes. Callers at
// 0x4847a2, 0x487773 and 0x4f3d9f pass ECX, consume EAX, no stack args.
// No writes. Tags, not payloads, decide occupancy; any nonzero tag counts.
// Holes do not imply a unique length: retain the original bisection choices.
uint32_t RIFF_THISCALL ScriptTable::length() const {
    uint32_t upper = arraySize;
    if (upper != 0 && array[upper - 1].tag == 0) {
        uint32_t lower = 0;
        while (upper - lower > 1) {
            const uint32_t middle = (lower + upper) >> 1;
            if (array[middle - 1].tag == 0) {
                upper = middle;
            } else {
                lower = middle;
            }
        }
        return lower;
    }
    if (hash == reinterpret_cast<const void*>(static_cast<uintptr_t>(0x99a424))) {
        return upper;
    }
    return script_table_hash_boundary(this, upper);
}
