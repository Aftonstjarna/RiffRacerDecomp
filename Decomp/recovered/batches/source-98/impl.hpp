#ifndef RIFF_WIDE_PREPEND_HPP
#define RIFF_WIDE_PREPEND_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THIS __thiscall
#else
#define RIFF_THIS __attribute__((thiscall))
#endif
// Original x86 string layout. These are 16-bit code units, not Linux wchar_t.
struct WideString {
    union Storage { uint16_t text[8]; uint16_t* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    uint16_t* data() { return capacity < 8 ? storage.text : storage.heap; }
    const uint16_t* data() const { return capacity < 8 ? storage.text : storage.heap; }
    WideString* RIFF_THIS prepend(uint32_t unused1, const WideString* prefix,
                                 uint32_t unused3, uint32_t unused4);
    // External 0x44fc30, thiscall RET 8. May relocate storage or throw.
    bool RIFF_THIS reserve(uint32_t requested, bool trim);
    // External 0x44fab0, thiscall RET 4. Publishes length and terminator.
    void RIFF_THIS set_length(uint32_t size);
};
// Port bindings for original WCHAR traits helpers (0x44e120, 0x44e140).
// Count is in code units. copy requires distinct storage; move permits overlap.
void wide_copy(uint16_t* dst, const uint16_t* src, uint32_t count);
void wide_move(uint16_t* dst, const uint16_t* src, uint32_t count);
// Original std::_Xlength_error import; must not return.
void wide_length_error(const char* message);
#endif
