#ifndef RIFF_WIDE_ASSIGN_RANGE_HPP
#define RIFF_WIDE_ASSIGN_RANGE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Original x86 layout: inline WCHAR[8] or pointer; length +16, capacity +20.
// WCHAR is a UTF-16 code unit, independent of the platform's wchar_t.
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    WideString* RIFF_THISCALL assign_range(const uint16_t* source, uint32_t count);
    // External dependencies, not recovered by this slice. Original thiscall ABIs.
    WideString* RIFF_THISCALL assign_substring(const WideString* source,
                                               uint32_t position, uint32_t count); // 0x44fb30
    void RIFF_THISCALL grow(uint32_t requested, uint32_t preserved); // 0x44fde0
};
// Bind to the port's CRT. Error must throw/otherwise not return.
void wide_length_error(const char* message); // original IAT 0x92d168
void* wide_copy(void* destination, const void* source, uint32_t bytes); // 0x8f8d66, memcpy
#endif
