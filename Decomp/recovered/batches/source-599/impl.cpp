#include "impl.hpp"
namespace riff {
// VA 0x438d30, 184 bytes. ECX=this; stack: index, output; ret 8.
// The table at 0x9f98d0 contains this method at +0x5c (0x9f992c).
// Edge-query code 0x438f00 calls that slot at 0x438f89/0x438f94,
// pushing an output pointer followed by the selected vertex index.
// Only bits 0..2 matter, even for negative or out-of-range indices.
// Do not replace this arithmetic by +/-extent: 0*infinity is observable.
static float coordinate(float extent, uint32_t bit) {
    const float selected = static_cast<float>(bit);
    const float opposite = static_cast<float>(1u - bit);
    const float positive_part = opposite * extent;
    const float negative_part = selected * extent;
    return positive_part - negative_part;
}
void RIFF_THISCALL BoxShape::vertex_without_margin(int32_t index, Vector4* output) const {
    const uint32_t bits = static_cast<uint32_t>(index);
    // Complete the calculation before writing: original loads all 16 extent
    // bytes before any output store, including when output aliases the object.
    Vector4 result;
    result.x = coordinate(half_extents_without_margin.x, bits & 1u);
    result.y = coordinate(half_extents_without_margin.y, (bits >> 1) & 1u);
    result.z = coordinate(half_extents_without_margin.z, (bits >> 2) & 1u);
    result.w = 0.0f;
    *output = result;
}
}
