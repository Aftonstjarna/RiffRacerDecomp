#include "impl.hpp"

extern "C" uint32_t RIFF_CDECL utf16_terminated_length(const uint16_t* text)
{
    const uint16_t* cursor = text;
    while (*cursor != 0)
        ++cursor;

    // The original advances past zero, subtracts text+1 in byte addresses,
    // then performs a 32-bit arithmetic right shift by one. Express that
    // signed-shift result without implementation-defined signed conversion.
    const uint32_t byteDistance = static_cast<uint32_t>(
        reinterpret_cast<uintptr_t>(cursor) - reinterpret_cast<uintptr_t>(text));
    return (byteDistance >> 1) | (byteDistance & UINT32_C(0x80000000));
}
// Direct original caller: 0x425ece passes a pointer from a pointer array;
// 0x425ed3 onward compares the result with a remaining length (signed jle).
// No object/this pointer, fields, imports, allocation, or FS registration.
// Null/unreadable/unterminated inputs fault or scan outside valid storage;
// no replacement error policy is introduced here. Address-wrapping scans
// cannot be represented by a portable C++ object and are outside the contract.
