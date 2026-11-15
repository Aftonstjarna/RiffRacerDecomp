#ifndef RIFF_MATRIX3_STORAGE_HPP
#define RIFF_MATRIX3_STORAGE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original VA 0x467e10, size 61. Three 16-byte rows, including padding.
// Byte storage avoids imposing floating-point interpretation or alignment.
struct Matrix3Storage {
    unsigned char storage[3][16];
    void RIFF_THISCALL copy_storage(const void* source);
};
static_assert(sizeof(Matrix3Storage) == 48, "original storage extent");
#endif
