#ifndef RIFF_APPEND_HPP
#define RIFF_APPEND_HPP
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
    uint32_t length, capacity;
    NarrowString* RIFF_THISCALL append_range(const char*, uint32_t);
    // External port bindings, not recovered in this slice.
    NarrowString* RIFF_THISCALL append_substring(const NarrowString*, uint32_t, uint32_t); // 0x4420b0
    bool RIFF_THISCALL prepare_append(uint32_t, bool); // 0x416730
};
void* narrow_copy(void*, const void*, uint32_t); // cdecl memcpy thunk 0x8f8d66
RIFF_NORETURN void narrow_length_error(const char*); // IAT 0x92d168
#endif
