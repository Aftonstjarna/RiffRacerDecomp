#ifndef RIFF_NARROW_RANGE_HPP
#define RIFF_NARROW_RANGE_HPP
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
    NarrowString* RIFF_THISCALL assign_range(const char* source, uint32_t count);
    // Original integration dependencies, outside this bounded recovery.
    NarrowString* RIFF_THISCALL assign_substring(const NarrowString*, uint32_t, uint32_t); // 0x415fe0
    void RIFF_THISCALL grow(uint32_t requested, uint32_t preserved); // 0x416890
};
void* narrow_copy(void*, const void*, uint32_t); // memcpy thunk 0x8f8d66
RIFF_NORETURN void narrow_length_error(const char*); // nonreturning IAT 0x92d168
#endif
