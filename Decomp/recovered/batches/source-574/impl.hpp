#ifndef RIFF_U32_VECTOR_GROWTH_HPP
#define RIFF_U32_VECTOR_GROWTH_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original 32-bit address layout. Address words permit inspection on a 64-bit
// port without dereferencing or subtracting unrelated host pointers.
struct U32Vector {
    uint32_t begin;
    uint32_t end;
    uint32_t limit;
    uint32_t RIFF_THISCALL growth_capacity(uint32_t requested) const;
};
#endif
