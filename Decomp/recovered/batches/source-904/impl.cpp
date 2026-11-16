#include "impl.hpp"
namespace riff {
// Restricted semantics of accepted script-reallocate (0x4f7d10), new size 0.
// Capture the owner before the callback; even a nonnull callback result is
// ignored by disposal. No allocation-failure path is possible with new size 0.
static void release(State* state, void* block, uint32_t bytes) {
    Global* owner = state->global;
    owner->allocator(owner->allocator_user, block, bytes, 0);
    owner->allocated_bytes -= bytes;
}
// Game.exe 0x4f4bb0..0x4f4c3c. Original ECX=State, EDX=Prototype,
// caller-clean register ABI. Callers 0x4f1a8d and 0x4f1e96 are GC dispatches.
// Array names follow the observed Lua-style Proto layout; this does not
// recover traversal or element ownership. No recursive child/string disposal.
void State::dispose_prototype(Prototype* p) {
    release(this, p->code, p->code_count * uint32_t(4));
    release(this, p->prototypes, p->prototype_count * uint32_t(4));
    release(this, p->constants, p->constant_count * uint32_t(8));
    release(this, p->line_info, p->line_count * uint32_t(4));
    release(this, p->local_variables, p->local_count * uint32_t(12));
    release(this, p->upvalue_names, p->upvalue_count * uint32_t(4));
    release(this, p, 0x4c);
    // Do not inspect p again: the final callback may have freed it.
}
}
