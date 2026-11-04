#include "impl.hpp"
// Game.exe 0x48d630..0x48d6d6, ECX=this, no arguments, no return value.
// Calls at 0x44f0e9 (+0x140), 0x48d89c (+0x20), 0x56cc78 (+0x20)
// pass embedded strings. No allocator/proxy field precedes the 16-byte union.
// Original constructs an empty SSO temporary, swaps storage via 0x451b60,
// swaps length/capacity, then destroys the old heap via IAT 0x92d4b0.
// Its SSO/SSO helper swaps all 16 bytes, but only temporary byte 0 is
// initialized: bytes 1..15 become unspecified stack residue. We retain those
// inactive bytes instead of reading uninitialized C++ memory. Heap cases copy
// exactly one initialized byte to this, leaving bytes 1..15 untouched.
// Compiler GS/SEH bookkeeping is not a portable string effect. The original
// restores FS:[0] on normal return; exception/unwind behavior is unrecovered.
void RIFF_THISCALL NarrowString::reset() {
    const bool was_heap = capacity >= 16u;
    char* old_allocation = was_heap ? storage.heap : 0;
    storage.inline_bytes[0] = 0;
    length = 0;
    capacity = 15;
    if (was_heap)
        recovered_narrow_delete(old_allocation);
}
