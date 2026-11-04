#ifndef RIFF_WIDE_SUBSTRING_HPP
#define RIFF_WIDE_SUBSTRING_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Original i386 layout: UTF-16 small buffer/pointer, length +16, capacity +20.
// Capacity is in code units, excluding the terminator; <8 selects inline.
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    WideString* RIFF_THISCALL assign_substring(const WideString* source,
                                              uint32_t position, uint32_t count);
    // Reference dependencies, not recovered in this slice.
    WideString* RIFF_THISCALL truncate(uint32_t length); // 0x44fcf0
    WideString* RIFF_THISCALL erase(uint32_t position, uint32_t count); // 0x44fd30
    void RIFF_THISCALL grow(uint32_t requested, uint32_t preserved); // 0x44fde0
};
// Port integration hooks: errors must not return and must preserve the CRT's
// exception contract. copy is memcpy, not memmove; distinct overlapping objects
// have no newly defined semantics. No allocation policy is invented here.
void wide_out_of_range(const char* message); // IAT 0x92d16c
void wide_length_error(const char* message); // IAT 0x92d168
void* wide_copy(void* destination, const void* source, uint32_t bytes); // 0x8f8d66
#endif
