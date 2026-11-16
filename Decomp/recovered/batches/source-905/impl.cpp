#include "impl.hpp"
namespace riff {
// Game.exe 0x4f4800..0x4f4864 (100 bytes). Original custom ABI:
// ECX=state, EDX=32-bit count, [entry ESP+4]=environment, caller pops stack.
// Callers 0x4f44bb and 0x4f5b82 zero-extend prototype byte +48 into EDX;
// both subsequently set closure.prototype (+10). Count is NOT narrowed for
// allocation or clearing, only for the stored byte (also true for count>255).
Closure* State::allocate_lua_closure(uint32_t count, Table* environment) {
    const uint32_t bytes = uint32_t(20) + count * uint32_t(4);
    Closure* const closure = static_cast<Closure*>(reallocate(this, 0, 0, bytes));
    // Reload after allocation: allocator/GC callbacks can change state.global.
    Global* const owner = global;
    closure->next = owner->root;
    const uint8_t white = owner->current_white;
    owner->root = closure;
    closure->marked = white & 3;
    closure->type = 6;
    closure->is_c = 0;
    closure->environment = environment;
    closure->upvalue_count = static_cast<uint8_t>(count);
    Upvalue** const slots = reinterpret_cast<Upvalue**>(
        reinterpret_cast<uint8_t*>(closure) + 20);
    // Original clears in descending address order. gc_list and prototype,
    // including their preexisting allocation contents, remain untouched.
    for (uint32_t remaining = count; remaining != 0; --remaining)
        slots[remaining - 1] = 0;
    return closure;
}
}
