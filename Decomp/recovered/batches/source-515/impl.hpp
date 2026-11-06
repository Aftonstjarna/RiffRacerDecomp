#ifndef RIFF_U64_MULTIPLY_LOW_HPP
#define RIFF_U64_MULTIPLY_LOW_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
// Original VA 0x8fc1f0, RVA 0x4fc1f0, 52 bytes. Two stack-passed
// 64-bit operands, EDX:EAX result, callee removes 16 bytes on i386.
extern "C" uint64_t RIFF_STDCALL u64_multiply_low(uint64_t a, uint64_t b);
#endif
