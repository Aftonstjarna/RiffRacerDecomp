#include "impl.hpp"
namespace riff {
// Game.exe RVA 0x22be0, VA 0x422be0, 100 bytes. ECX=this, four stack
// arguments, ret 16. Reads length +16, capacity +20, storage +0 only.
int RIFF_THISCALL NarrowString::compare(uint32_t position, uint32_t count,
                                        const unsigned char* right,
                                        uint32_t right_count) const {
    if (position > length) narrow_out_of_range("invalid string position");
    const uint32_t remaining = length - position;
    const uint32_t selected = count < remaining ? count : remaining;
    const unsigned char* left = capacity < 16 ? storage.small : storage.heap;
    const uint32_t common = selected < right_count ? selected : right_count;
    // Original delegates min(selected,right_count) bytes to 0x4225c0.
    // That helper returns exactly -1/0/+1, ordering unsigned bytes, including
    // embedded NUL. Byte loads express its result without unaligned word UB.
    for (uint32_t i=0; i<common; ++i) {
        const unsigned char a=left[position+i], b=right[i];
        if (a != b) return a < b ? -1 : 1;
    }
    if (selected < right_count) return -1;
    return selected != right_count ? 1 : 0;
}
}
// Callers 0x422ac5, 0x422b5e, 0x422c6b, 0x423354 and 0x423918 pass
// position zero and string lengths, then test the result's sign for tree
// ordering. Capacity (not length) chooses storage. No terminator is read.
// No writes, allocations, locale operations or SEH registration on valid paths.
// Invalid-position CRT exception handling is an external port dependency;
// invalid memory, inconsistent objects, and concurrent mutation are unsupported.
