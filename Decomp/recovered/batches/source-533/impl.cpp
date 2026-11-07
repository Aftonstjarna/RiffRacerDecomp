#include "impl.hpp"
// VA 0x511e90, 46 bytes, ECX=this, one stack argument, callee pops 4.
// Direct original disassembly agrees with resource_index_acquire.S.
// Callers at 0x4feeb0, 0x507982 and 0x5085cc use index zero as the
// unnamed/default alternative to the adjacent name-based acquire routine.
uint32_t RIFF_THISCALL ResourceIndex::acquire(uint32_t index) {
    const uint32_t bytes = entriesEnd - entriesBegin;
    // Explicit SAR-by-two in unsigned arithmetic: preserve even malformed,
    // reversed or unaligned spans without C++ pointer subtraction UB.
    const uint32_t count = (bytes >> 2) | ((bytes & 0x80000000u) ? 0xc0000000u : 0u);
    if (index >= count)
        return 0;
    uint32_t* counts = reinterpret_cast<uint32_t*>(static_cast<uintptr_t>(counters));
    ++counts[index]; // non-atomic, modulo 2^32; no overflow or null check
    // Reload begin after increment: aliasing counters can alter the entry or
    // this field. No resource object is dereferenced by this routine.
    const uint32_t* entries = reinterpret_cast<const uint32_t*>(static_cast<uintptr_t>(entriesBegin));
    return entries[index];
}
