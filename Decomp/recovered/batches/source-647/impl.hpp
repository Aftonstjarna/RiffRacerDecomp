#ifndef RIFF_POLYHEDRAL_CONVEX_AABB_HPP
#define RIFF_POLYHEDRAL_CONVEX_AABB_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Original VA 0x47bec0, 118 bytes. Fixed-width vtable token retains the
// original 32-bit layout; a Linux port must supply a relocated dispatch table.
// Field meanings follow the polyhedral convex AABB layout; unknown slots
// deliberately remain untouched. No virtual calls or allocation occur here.
struct PolyhedralConvexAabb {
    uint32_t vtable_address;                 // +00
    uint32_t shape_type;                     // +04
    uint32_t unknown08;                      // +08 (written zero)
    float local_scaling[4];                  // +0c
    uint32_t untouched1c[4];                 // +1c through +2b
    float collision_margin;                 // +2c
    uint32_t untouched30;                    // +30
    float cached_aabb_min[4];                // +34
    float cached_aabb_max[4];                // +44
    uint8_t cached_aabb_valid;               // +54
    uint8_t untouched55[3];
    PolyhedralConvexAabb* RIFF_THISCALL initialize();
};
static_assert(offsetof(PolyhedralConvexAabb, collision_margin)==0x2c,"layout");
static_assert(offsetof(PolyhedralConvexAabb, cached_aabb_valid)==0x54,"layout");
static_assert(sizeof(PolyhedralConvexAabb)==0x58,"layout");
#endif
