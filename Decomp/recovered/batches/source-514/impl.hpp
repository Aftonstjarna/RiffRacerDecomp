#ifndef RIFF_MATRIX64_COPY_HPP
#define RIFF_MATRIX64_COPY_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Opaque matrix storage: element interpretation is not established by this copy.
// Alignment is deliberately one byte, as original MOVDQU requires no alignment.
struct Matrix64 {
    uint8_t bytes[64];
    Matrix64* RIFF_THISCALL copy_from(const void* source);
};
static_assert(sizeof(Matrix64) == 64, "matrix storage size");
#endif
