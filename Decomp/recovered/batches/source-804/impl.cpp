#include "impl.hpp"
namespace riff {
// Restricted use of accepted script-reallocate (0x4f7d10): new size is always
// zero, so its allocation-failure/error/longjmp paths cannot be entered.
static void release(State* state, void* memory, uint32_t bytes) {
    Global* const owner = state->global;
    owner->allocator(owner->allocator_user, memory, bytes, 0);
    owner->allocated_bytes -= bytes; // modulo 2^32, after the callback
}
// Game.exe 0x4f0980..0x4f09d4. Original custom register ABI: ECX=State,
// EDX=Table, no stack arguments. Caller at 0x4f1ad3 dispatches table GC
// cleanup here. A normal member models state ownership without an asm adapter.
void State::destroy_table(Table* table) {
    void* const hash = table->hash;
    if (hash != empty_hash()) {
        // x86 variable shifts mask the byte count to five bits. Unsigned
        // arithmetic preserves even malformed size fields without C++ UB.
        const uint32_t nodes = uint32_t(1) << (table->hash_log2 & 31);
        release(this, hash, nodes * uint32_t(20));
    }
    // Read these after the hash callback, which may modify the table/state.
    release(this, table->array, table->array_count * uint32_t(8));
    release(this, table, 32);
    // No table reads after release, field clearing, or element finalization.
}
}
