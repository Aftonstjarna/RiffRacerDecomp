#ifndef RIFF_WIDE_ASSIGN_POINTER_HPP
#define RIFF_WIDE_ASSIGN_POINTER_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Original x86 UTF-16 string layout. Capacity counts code units, not bytes.
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    WideString* RIFF_THISCALL assign_pointer(const uint16_t* source);
    // Integration dependency: original VA 0x44f9b0, not recovered here.
    WideString* RIFF_THISCALL assign_range(const uint16_t* source, uint32_t count);
};
#endif
