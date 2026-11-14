#include "impl.hpp"
// Constructor body represented as a member returning this to expose EAX.
// The direct caller at 0x47cd72 subsequently overwrites the vtable at +0
// and initializes a derived member at +0x58. No stack arguments, no FS use.
PolyhedralConvexAabb* RIFF_THISCALL PolyhedralConvexAabb::initialize() {
    shape_type = 0x23;
    unknown08 = 0;
    local_scaling[0] = 1.0f;
    local_scaling[1] = 1.0f;
    local_scaling[2] = 1.0f;
    local_scaling[3] = 0.0f;
    collision_margin = 0.04f; // original IEEE-754 bits 0x3d23d70a
    vtable_address = 0x9fb030;
    cached_aabb_min[0] = 1.0f;
    cached_aabb_min[1] = 1.0f;
    cached_aabb_min[2] = 1.0f;
    cached_aabb_min[3] = 0.0f;
    cached_aabb_max[0] = -1.0f;
    cached_aabb_max[1] = -1.0f;
    cached_aabb_max[2] = -1.0f;
    cached_aabb_max[3] = 0.0f;
    cached_aabb_valid = 0;
    return this;
}
