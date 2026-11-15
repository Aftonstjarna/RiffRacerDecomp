#include "impl.hpp"
namespace riff {
// Game.exe 0x4f7d10..0x4f7d95. Original custom register ABI: ECX=state,
// EDX=memory, two caller-cleaned stack sizes. A genuine portable member
// method models the state ownership; the oracle adapter lives only in test.cpp.
void* State::reallocate(void* memory, uint32_t old_bytes, uint32_t new_bytes,
                        const ErrorServices& errors) {
    Global* const accounting_global = global; // captured before allocator callback
    void* const result = accounting_global->allocator(
        accounting_global->allocator_user, memory, old_bytes, new_bytes);
    if (!result && new_bytes != 0) {
        if (error_frame) {
            error_frame->status = 4;
            errors.jump(error_frame->jump_buffer, 1);
        }
        // Reload global after callbacks, as in the original. The CRT jump
        // normally never returns; do not turn failed allocation into an exception.
        status = 4;
        if (global->panic) {
            errors.prepare(this, 4);
            global->panic(this);
        }
    }
    // Even a failed allocation that returns normally changes accounting.
    accounting_global->allocated_bytes += new_bytes - old_bytes;
    return result;
}
}
