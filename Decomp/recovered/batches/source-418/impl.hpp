#ifndef RIFF_NARROW_SET_LENGTH_HPP
#define RIFF_NARROW_SET_LENGTH_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Recovered 32-bit string layout at Game.exe 0x416700 (RVA 0x16700).
// Only this operation is recovered; ownership and allocation are caller concerns.
struct NarrowString {
    union Storage {
        char inline_data[16];
        char* heap_data;
    } storage;
    uint32_t length;
    uint32_t capacity;
    void RIFF_THISCALL set_length(uint32_t new_length);
};
static_assert(offsetof(NarrowString, length) == 16, "length offset");
static_assert(offsetof(NarrowString, capacity) == 20, "capacity offset");
static_assert(sizeof(NarrowString) == 24, "string size");
#endif
