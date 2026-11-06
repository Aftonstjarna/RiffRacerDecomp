#ifndef RECOVERED_WIDE_CONSTRUCT_HPP
#define RECOVERED_WIDE_CONSTRUCT_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    WideString* RIFF_FASTCALL construct_terminated(const uint16_t* source);
    // Reference helper, not recovered here: original VA 0x44f9b0.
    // Port integration must supply range assignment, including heap growth.
    WideString* RIFF_THISCALL assign_range(const uint16_t* source, uint32_t count);
};
#endif
