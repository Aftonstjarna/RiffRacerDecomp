#include "impl.hpp"

// Original Game.exe RVA 0x51d10, VA 0x451d10, 64 bytes. cdecl, two
// stack arguments, plain ret; no meaningful return value and no callees.
// The sole direct call found in executable disassembly is 0x451bac, in
// narrow_storage_swap (thiscall). It selects this helper when both capacities
// at +0x14 are <16. Bytes +0..15 are inline storage; size +0x10 and capacity
// +0x14 are NOT touched here. Outer swap at 0x451a40 swaps those fields.
// EBX/ESI/EDI/EBP are preserved by the original ABI; flags/scratch registers
// are not API outputs. All 16 bytes, including unused string tail, are swapped.
void narrow_inline_swap(void* first, void* second) {
    if (first == second) return;
    using Address = decltype(sizeof(0));
    const Address start = reinterpret_cast<Address>(first);
    // x86 unsigned end-pointer comparison suppresses all access on wrap.
    // Address width follows the port; in the original i386 ABI it is 32 bits.
    if (static_cast<Address>(start + 16) < start) return;
    auto* a = static_cast<unsigned char*>(first);
    auto* b = static_cast<unsigned char*>(second);
    for (unsigned i = 0; i != 16; ++i) {
        // Preserve forward, byte-at-a-time order even with partial overlap.
        const unsigned char from_second = b[i];
        const unsigned char from_first = a[i];
        a[i] = from_second;
        b[i] = from_first;
    }
}
