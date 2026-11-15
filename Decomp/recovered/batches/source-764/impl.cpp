#include "impl.hpp"
namespace riff {
bool RIFF_STDCALL pointer_range_has_state_six_or_seven(
    uint32_t, int32_t index, const PointerRange32* range) {
    // SUB/SAR uses a wrapping 32-bit byte distance. A signed-negative
    // distance, zero distance, or a positive distance below four is empty.
    const uint32_t distance = range->end - range->begin;
    if ((distance & 0x80000000u) != 0 || distance < 4u) return false;
    const uint32_t count = distance / 4u;
    const uint32_t offset = static_cast<uint32_t>(index) * 100u + 0xd4u;
    uint32_t cursor = range->begin;
    for (uint32_t i = 0; i < count; ++i, cursor += 4u) {
        const uint32_t object = *reinterpret_cast<const uint32_t*>(
            static_cast<uintptr_t>(cursor));
        const uint32_t state = *reinterpret_cast<const uint32_t*>(
            static_cast<uintptr_t>(object + offset));
        if (state == 6u || state == 7u) return true;
    }
    return false;
}
}
// Caller evidence: calls at 0x4a7aed and 0x4a903b pass object+0x58
// as the descriptor. The second supplies index from another object's +0x488.
// Names/types of the enclosing objects and indexed records remain unresolved.
// No null checks, writes, calls, exceptions or FS access occur in this routine.
