#ifndef RIFF_WIDE_MOVE_HPP
#define RIFF_WIDE_MOVE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    WideString* RIFF_THISCALL move_construct(WideString* source);
};
static_assert(sizeof(WideString) == 24, "Original requires 32-bit pointers");
#endif
