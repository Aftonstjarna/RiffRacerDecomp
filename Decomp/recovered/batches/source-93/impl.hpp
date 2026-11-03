#ifndef RIFF_APPEND_POINTER_HPP
#define RIFF_APPEND_POINTER_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THIS __thiscall
#else
#define RIFF_THIS __attribute__((thiscall))
#endif
// Original x86 layout; uint16_t is a Windows WCHAR on every port.
struct WideString {
    union { uint16_t text[8]; uint16_t* heap; } storage;
    uint32_t length, capacity;
    uint16_t* data() { return capacity < 8 ? storage.text : storage.heap; }
    WideString* RIFF_THIS append_pointer(const uint16_t* source, uint32_t count);
    // Unrecovered dependencies: 0x5360b0, 0x44fc30 and 0x44fab0.
    WideString* RIFF_THIS append_substring(const WideString*, uint32_t, uint32_t);
    bool RIFF_THIS reserve(uint32_t, bool);
    void RIFF_THIS set_length(uint32_t);
};
// Bind to the platform CRT when porting. length_error must not return.
void riff_length_error(const char*);
void* riff_copy(void*, const void*, uint32_t);
#endif
