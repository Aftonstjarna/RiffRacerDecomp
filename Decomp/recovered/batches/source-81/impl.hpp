#ifndef RIFF_WIDE_APPEND_HPP
#define RIFF_WIDE_APPEND_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif

// Game.exe 0x44f8f0: x86 basic_string-like object, 24 bytes.
// WCHAR is always 16 bits, including on Linux. Capacity excludes the NUL.
struct WideString {
    union Storage {
        uint16_t inline_text[8];
        uint16_t* heap_text;
    } storage;
    uint32_t length;
    uint32_t capacity;

    WideString* RIFF_THISCALL append_char(uint32_t unused, uint16_t character);

    // External dependency, original 0x44fde0. Not recovered in this slice.
    // Must allocate/retain old_length units, update storage/capacity/length,
    // and propagate allocation exceptions. Its original ABI is thiscall RET 8.
    void RIFF_THISCALL grow(uint32_t new_length, uint32_t old_length);
};
// External std::_Xlength_error binding (original IAT 0x92d168).
// Must not return; deliberately no invented exception implementation here.
void wide_string_length_error(const char* message);
#endif
