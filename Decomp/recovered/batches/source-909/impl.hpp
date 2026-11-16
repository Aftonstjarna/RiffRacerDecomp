#ifndef RIFF_SIMPLEX_IMPL_HPP
#define RIFF_SIMPLEX_IMPL_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
struct SimplexVector { float x, y, z, w; };
// Partial layout, not a recovered declaration of the complete solver type.
// Valid simplex storage is modeled as four entries. The original trusts count:
// <=0 skips the scan; corrupt counts >4 and invalid pointers are outside this
// typed interface's contract. The remaining solver fields are unresolved.
struct SimplexSolver {
    int32_t vertex_count;                      // +0x000
    SimplexVector vertices[4];                 // +0x004, stride 16
    unsigned char unresolved[0xe0];            // +0x044
    SimplexVector cached_vertex;               // +0x124
    float distance_squared_threshold;          // +0x134
    bool RIFF_THISCALL contains_vertex(const SimplexVector* vertex) const;
};
static_assert(offsetof(SimplexSolver, cached_vertex) == 0x124, "layout");
static_assert(offsetof(SimplexSolver, distance_squared_threshold) == 0x134, "layout");
#endif
