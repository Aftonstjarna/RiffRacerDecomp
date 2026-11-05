#ifndef RIFF_WIDE_SET_LENGTH_HPP
#define RIFF_WIDE_SET_LENGTH_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original 32-bit string layout. Capacity counts UTF-16 code units, excluding
// the terminator. This helper assumes the caller already provided storage.
struct WideString {
    union Storage {
        uint16_t inline_units[8];
        uint16_t* heap;
    } storage;
    uint32_t length;
    uint32_t capacity;
    void RIFF_THISCALL set_length(uint32_t new_length);
};
static_assert(offsetof(WideString, length) == 16, "length offset");
static_assert(offsetof(WideString, capacity) == 20, "capacity offset");
static_assert(sizeof(WideString) == 24, "string size");
#endif
