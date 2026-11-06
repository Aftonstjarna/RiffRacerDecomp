#ifndef RIFF_MATRIX_EXTRACT_HPP
#define RIFF_MATRIX_EXTRACT_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Raw float representations avoid arithmetic or NaN canonicalization. Nearby
// 0x426fd0 copies 64 bytes; callers extract basis columns 0, 1 and 2.
struct Matrix {
    uint32_t words[16];
    uint32_t* RIFF_THISCALL column3(uint32_t* output, uint32_t column) const;
};
}
#endif
