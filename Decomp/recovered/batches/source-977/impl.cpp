#include "impl.hpp"

// Game.exe 0x5960b0..0x5960e9 (RVA 0x1960b0), ECX=this,
// no stack arguments. No calls, allocations, FS registration or static data.
// Caller 0x5961c0 invokes this when full and growth is disabled/fails.
// The resize helper at 0x5960f0 also contains the same compaction logic.
// EAX is incidental (unspecified on the early return); callers use fields.
void RIFF_THISCALL AudioIndex::compactEven() {
    if (count < 2u)
        return;
    stride += stride;
    count >>= 1;
    for (uint32_t i = 0; i < count; ++i)
        entries[i] = entries[i * 2u];
    coveredUnits = count * stride;
}
// Valid objects provide a separate writable entries allocation large enough
// for the input count. No validation is added: the original trusts its object.
// Slots beyond the new count, capacity and growth remain unchanged. An odd
// input discards its final unpaired even-position entry. All arithmetic is
// unsigned to preserve x86 low-32-bit wraparound without signed overflow.
