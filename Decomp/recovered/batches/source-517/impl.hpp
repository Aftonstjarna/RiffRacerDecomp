#ifndef RIFF_UNSIGNED64_DIVIDE_HPP
#define RIFF_UNSIGNED64_DIVIDE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#endif
// Original 0x8fc290, 104 bytes. Stack: numerator low/high, divisor low/high;
// result EDX:EAX; callee pops 16 bytes. No object, globals, or memory outputs.
// Precondition: divisor != 0. The original raises x86 #DE on zero.
extern "C" uint64_t RIFF_STDCALL recovered_unsigned64_divide(uint64_t numerator,
                                                           uint64_t divisor);
#endif
