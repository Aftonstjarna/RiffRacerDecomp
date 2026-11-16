#ifndef RIFF_SIMPLEX_REDUCE_HPP
#define RIFF_SIMPLEX_REDUCE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Bit storage for a 16-byte physics vector: copies must preserve the fourth
// lane, NaN payloads, signed zero, and denormals without arithmetic.
struct SimplexVectorBits { uint32_t lane[4]; };

// Recovered prefix only, not a declaration of the complete solver class.
// VA 0x546130..0x54623d: ECX=this, one pointer argument, callee pops 4.
struct SimplexSolverVertices {
    int32_t vertexCount;                 // +0x00, signed comparisons
    SimplexVectorBits difference[5];     // +0x04, Minkowski-space vertices
    SimplexVectorBits supportA[5];       // +0x54, paired support points
    SimplexVectorBits supportB[5];       // +0xa4

    void RIFF_THISCALL reduceVertices(const uint8_t* usedVertices);
private:
    void removeVertex(int index) {
        --vertexCount;
        difference[index] = difference[vertexCount];
        supportA[index] = supportA[vertexCount];
        supportB[index] = supportB[vertexCount];
    }
};
static_assert(sizeof(SimplexVectorBits) == 16, "vector size");
static_assert(offsetof(SimplexSolverVertices, difference) == 4, "difference offset");
static_assert(offsetof(SimplexSolverVertices, supportA) == 0x54, "support A offset");
static_assert(offsetof(SimplexSolverVertices, supportB) == 0xa4, "support B offset");
static_assert(sizeof(SimplexSolverVertices) == 0xf4, "recovered prefix size");
#endif
