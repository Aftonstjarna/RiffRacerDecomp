#ifndef RIFF_MATRIX3_IDENTITY_HPP
#define RIFF_MATRIX3_IDENTITY_HPP

// Twelve consecutive floats; the last three values' semantic role is not
// established by this constructor alone.
struct Matrix3Identity {
    float values[12];
    Matrix3Identity* initialize_identity();
};

#endif
