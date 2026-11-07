#ifndef RIFF_BODY_VECTOR_PAIR_HPP
#define RIFF_BODY_VECTOR_PAIR_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Partial object, not an assertion of original class name or physical units.
struct BodyVectorAccumulator {
    uint8_t unknown000[0x100];
    float rows[3][4];              // 0x100: padded matrix rows
    float firstSum[3];             // 0x130
    uint8_t unknown13c[4];
    float secondSum[3];            // 0x140
    uint8_t unknown14c[4];
    float factor;                  // 0x150
    float componentScale[3];       // 0x154
    uint8_t unknown160[0xb8];
    float transformedScale[3];     // 0x218
    // VA 0x4386f0: ECX=this; two stack pointers; ret 8; void.
    void RIFF_THISCALL accumulatePair(const float* vector, const float* arm);
};
static_assert(offsetof(BodyVectorAccumulator,firstSum)==0x130,"first sum");
static_assert(offsetof(BodyVectorAccumulator,secondSum)==0x140,"second sum");
static_assert(offsetof(BodyVectorAccumulator,factor)==0x150,"factor");
static_assert(offsetof(BodyVectorAccumulator,componentScale)==0x154,"component scale");
static_assert(offsetof(BodyVectorAccumulator,transformedScale)==0x218,"transformed scale");
static_assert(sizeof(BodyVectorAccumulator)==0x224,"partial size");
}
#endif
