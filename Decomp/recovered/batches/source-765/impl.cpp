#include "impl.hpp"

// ECX is this on original i386; no stack arguments and no return value.
// Original performs twelve ordered DWORD stores, without reading the object.
// Callers at 0x4332d0, 0x4472ec, 0x459743 and 0x517c12 discard the
// return registers. This is a reset operation, not an allocating constructor.
void RIFF_THISCALL Matrix3::initialize_identity() {
    basis[0] = 1.0f;
    basis[1] = 0.0f;
    basis[2] = 0.0f;
    basis[3] = 0.0f;
    basis[4] = 1.0f;
    basis[5] = 0.0f;
    basis[6] = 0.0f;
    basis[7] = 0.0f;
    basis[8] = 1.0f;
    trailing[0] = 0.0f;
    trailing[1] = 0.0f;
    trailing[2] = 0.0f;
}
