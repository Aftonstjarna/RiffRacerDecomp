#include "impl.hpp"
// Game.exe VA 0x427110..0x427136 (RVA 0x27110).
// ECX is this, one pointer argument, callee pops 4, bool returned in AL.
// Vtable references at 0x9f8e54 and 0x9fa6a8; exact dynamic callers unresolved.
// The original first tests this.mask against other.group, then conditionally
// reads other.mask and this.group. Neither object is modified. Both pointers
// must designate readable prefixes; there is no null check in the original.
// Names group/mask express the reciprocal bit-filter operation, not recovered
// debug type names. No behavior of neighboring callback methods is inferred.
bool RIFF_THISCALL ConvexCallbackFilter::accepts(const ConvexCallbackFilter* other) const {
    return (mask & other->group) != 0 && (group & other->mask) != 0;
}
