#ifndef RIFF_RECORD12_IMPL_HPP
#define RIFF_RECORD12_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif

// Field meanings are unresolved. Original offsets are 0, 4, 8; stride is 12.
struct Record12 {
    uint32_t field0;
    uint32_t field4;
    uint32_t field8;
};
static_assert(sizeof(Record12) == 12, "Original record stride");

// Original 0x41db10: ECX = destination, EDX = count, no stack arguments.
// This is a register-argument range helper, not a thiscall object method.
void RIFF_FASTCALL record12_default_initialize(Record12* destination, uint32_t count);
#endif
