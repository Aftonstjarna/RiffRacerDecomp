#ifndef RIFF_MATRIX3_IDENTITY_HPP
#define RIFF_MATRIX3_IDENTITY_HPP
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Original 0x422700..0x422754. Nine packed basis floats and three trailing
// floats are all written. Row/column convention and the trailing fields' role
// are not established by this routine; names deliberately avoid that claim.
struct Matrix3 {
    float basis[9];
    float trailing[3];
    void RIFF_THISCALL initialize_identity();
};
static_assert(sizeof(float) == 4, "Requires 32-bit float");
static_assert(sizeof(Matrix3) == 48, "Original destination spans 48 bytes");
#endif
