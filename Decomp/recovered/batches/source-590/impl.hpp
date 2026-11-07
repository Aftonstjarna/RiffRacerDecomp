#ifndef RIFF_MATRIX_SCALED_VECTOR_ACCUMULATE_HPP
#define RIFF_MATRIX_SCALED_VECTOR_ACCUMULATE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Partial object view only. Unknown words and row padding are preserved.
// Original 0x4385f0: ECX=this, one vector pointer on stack, ret 4, no return value.
struct MatrixAccumulator {
    uint8_t unknown000[0x100];
    float row0[4];                         // 0x100
    float row1[4];                         // 0x110
    float row2[4];                         // 0x120
    uint8_t unknown130[0x10];
    float accumulated[3];                  // 0x140
    uint8_t unknown14c[0xcc];
    float scale[3];                        // 0x218
    void RIFF_THISCALL accumulate(const float* vector);
};
static_assert(offsetof(MatrixAccumulator, row0) == 0x100, "row offset");
static_assert(offsetof(MatrixAccumulator, accumulated) == 0x140, "sum offset");
static_assert(offsetof(MatrixAccumulator, scale) == 0x218, "scale offset");
static_assert(sizeof(MatrixAccumulator) == 0x224, "partial view size");
}
#endif
