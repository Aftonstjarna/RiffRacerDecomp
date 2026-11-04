#ifndef RIFF_NARROW_RESET_HPP
#define RIFF_NARROW_RESET_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_CDECL __cdecl
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_CDECL __attribute__((cdecl))
#else
#define RIFF_THISCALL
#define RIFF_CDECL
#endif
// Port integration hook for the game's scalar operator delete import.
// Called even for a null pointer when the old capacity selects heap storage.
extern "C" void RIFF_CDECL recovered_narrow_delete(void* allocation);
struct NarrowString {
    union Storage {
        unsigned char inline_bytes[16];
        char* heap;
    } storage;
    uint32_t length;
    uint32_t capacity;
    void RIFF_THISCALL reset();
};
static_assert(sizeof(NarrowString) == 24, "original string extent");
#endif
