#ifndef RIFF_NARROW_APPEND_HPP
#define RIFF_NARROW_APPEND_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_NORETURN __declspec(noreturn)
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_NORETURN __attribute__((noreturn))
#endif
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL append_substring(const NarrowString*, uint32_t position, uint32_t count);
    // External original member at 0x416730; allocation is outside this slice.
    bool RIFF_THISCALL prepare_capacity(uint32_t, bool);
};
// External CRT bindings: copy is memcpy, not memmove.
void* narrow_copy(void*, const void*, uint32_t);
RIFF_NORETURN void narrow_length_error(const char*);
RIFF_NORETURN void narrow_position_error(const char*);
#endif
