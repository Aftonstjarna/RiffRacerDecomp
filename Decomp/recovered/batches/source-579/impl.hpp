#ifndef RIFF_AFFINE_MATRIX_HPP
#define RIFF_AFFINE_MATRIX_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// Original float payloads are represented by their bits: conversion performs
// no floating-point arithmetic, including on signaling NaNs and subnormals.
struct Affine48 { uint32_t basis[3][3]; uint32_t translation[3]; };
struct Matrix64 {
    uint32_t row[4][4];
    Matrix64* RIFF_FASTCALL fromAffine(const void* source);
};
static_assert(sizeof(Affine48)==48, "affine layout");
static_assert(sizeof(Matrix64)==64, "matrix layout");
}
#endif
