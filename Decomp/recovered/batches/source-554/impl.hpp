#ifndef RIFF_RECORD12_ZERO_HPP
#define RIFF_RECORD12_ZERO_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif

// Only widths and offsets are established; semantic field types are unresolved.
struct Record12 {
    uint32_t field0;
    uint32_t field4;
    uint32_t field8;
};
static_assert(sizeof(Record12) == 12, "Original record stride");

// VA 0x437ed0, size 35: ECX=destination, EDX=count, plain RET.
// Register-argument range helper, not a thiscall object method; no return value.
void RIFF_FASTCALL record12_zero_initialize(Record12* destination, uint32_t count);
#endif
