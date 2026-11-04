#ifndef RIFF_NARROW_ASSIGN_SUBSTRING_HPP
#define RIFF_NARROW_ASSIGN_SUBSTRING_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_NORETURN __declspec(noreturn)
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_NORETURN __attribute__((noreturn))
#endif
// Original i386 string layout. Capacity excludes the trailing NUL.
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL assign_substring(const NarrowString* source,
                                               uint32_t offset, uint32_t count);
    // Integration dependencies, outside this recovery's scope.
    NarrowString* RIFF_THISCALL erase(uint32_t offset, uint32_t count); // 0x416660
    void RIFF_THISCALL grow(uint32_t requested, uint32_t preserved); // 0x416890
};
// Supply original CRT-equivalent memcpy and nonreturning exception dispatch.
void* narrow_copy(void*, const void*, uint32_t); // thunk 0x8f8d66 -> IAT 0x92d494
RIFF_NORETURN void narrow_out_of_range(const char*); // IAT 0x92d16c
RIFF_NORETURN void narrow_length_error(const char*); // IAT 0x92d168
#endif
