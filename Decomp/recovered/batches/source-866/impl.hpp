#ifndef RIFF_SCRIPT_BUFFER_HPP
#define RIFF_SCRIPT_BUFFER_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct ScriptState;
// Dependencies retain VM allocation/accounting and error policy outside this slice.
struct BufferServices {
    void* (*reallocate)(ScriptState*, void*, uint32_t, uint32_t);
    void (*runtime_error)(ScriptState*, const char*);
};
struct ScriptBuffer {
    void* data;                 // +0
    uint32_t unknown04;          // untouched, not proven to be a length
    uint32_t capacity;           // +8, unsigned byte count
    void* ensure_capacity(ScriptState*, uint32_t requested, const BufferServices&);
};
static_assert(offsetof(ScriptBuffer, capacity)==8,"original 32-bit buffer layout");
}
#endif
