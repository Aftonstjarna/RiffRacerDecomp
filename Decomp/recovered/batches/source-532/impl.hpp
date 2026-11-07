#ifndef RIFF_MATRIX3_REFS_HPP
#define RIFF_MATRIX3_REFS_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Storage representation: three 16-byte rows. Words preserve floating-point
// payloads without interpreting them or performing floating-point arithmetic.
struct Matrix3 {
    uint32_t words[12];
    Matrix3* RIFF_THISCALL construct_refs(
        const uint32_t& a, const uint32_t& b, const uint32_t& c,
        const uint32_t& d, const uint32_t& e, const uint32_t& f,
        const uint32_t& g, const uint32_t& h, const uint32_t& i);
};
static_assert(sizeof(Matrix3) == 48, "original matrix storage size");
#endif
