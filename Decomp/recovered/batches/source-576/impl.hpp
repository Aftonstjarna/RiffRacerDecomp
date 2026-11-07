#ifndef RIFF_MATRIX64_HPP
#define RIFF_MATRIX64_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Sequential binary32 fields; row/column convention is not established here.
// Original VA 0x438480, size 112. No alignment beyond four bytes is required.
struct Matrix64 {
    float entries[16];
    void RIFF_THISCALL initialize_basis();
};
static_assert(sizeof(Matrix64) == 64, "original matrix storage size");
}
#endif
