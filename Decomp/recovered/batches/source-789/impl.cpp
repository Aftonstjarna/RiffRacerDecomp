#include "impl.hpp"
namespace riff {
// Accepted instructions at 0x4f0110..0x4f018a; original jump-table data at
// 0x4f018c contains 0x4f0150,0x4f016a,0x4f0127,0x4f0133 (tags 1..4).
// Callers at 0x4f01f0 and 0x4f09f3 use the returned node for key comparison
// or insertion. This routine neither probes collisions nor modifies storage.
Node* RIFF_FASTCALL Table::mainBucket(const Value* key) const {
    // x86 SHL r32,CL ignores all but the low five count bits.
    const uint32_t mask = (uint32_t(1) << (hashLog2 & 31)) - 1;
    uint32_t bucket;
    switch (key->tag) {
    case 1: bucket = key->payload.bits & mask; break;
    case 4: bucket = key->payload.string->hash & mask; break;
    case 3:
        // Tail call to accepted numeric helper 0x4f00c0. Both signed zeros
        // map to bucket zero; unordered NaNs follow the raw-bit remainder.
        // Keep the floating comparison: original UCOMISS also obeys MXCSR
        // denormals-are-zero and can set floating exception status flags.
        if (key->payload.number == 0.0f) bucket = 0;
        else bucket = key->payload.bits % (mask | 1u);
        break;
    default: bucket = key->payload.bits % (mask | 1u); break;
    }
    // Use integer address calculation, avoiding out-of-array C++ pointer
    // arithmetic for malformed headers. On i386 the entire address wraps.
    // sizeof(Node) keeps the analogous native-pointer layout usable in ports.
    const uintptr_t offset = uintptr_t(bucket) * sizeof(Node);
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(nodes) + offset);
}
}
