#ifndef RIFF_UNSIGNED64_REMAINDER_HPP
#define RIFF_UNSIGNED64_REMAINDER_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
// Original 0x8fc300, 117 bytes: dividend then divisor, each low word first.
// Callee pops 16 bytes on x86; uint64_t result is returned in EDX:EAX.
// Precondition: divisor != 0. The original faults on zero (x86 DIV).
extern "C" uint64_t RIFF_STDCALL recovered_unsigned64_remainder(
    uint64_t dividend, uint64_t divisor);
#endif
