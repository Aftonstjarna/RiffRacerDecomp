#ifndef RIFF_MATRIX48_HPP
#define RIFF_MATRIX48_HPP
#include <stdint.h>
// Storage order follows the original offsets; row/column convention is unresolved.
struct Matrix48 {
    float basis[3][4];
    void initialize_basis();
};
static_assert(sizeof(float) == 4, "32-bit floats required");
static_assert(sizeof(Matrix48) == 48, "original object extent");
#endif
