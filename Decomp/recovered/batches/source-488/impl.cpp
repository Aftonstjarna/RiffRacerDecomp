#include "impl.hpp"

// Game.exe VA 0x8fc260, RVA 0x4fc260, 33 bytes.
// Original helper ABI: EDX:EAX input/result, CL count, plain RET, no stack
// arguments or memory accesses. Call sites 0x59b22d and 0x5cbf01 confirm it.
// This portable API replaces that compiler-private ABI. ECX and flags are
// scratch in the original (CL is masked on the 32..63 path).
uint64_t signed64_arithmetic_shift_right(uint64_t bits, uint32_t count)
{
    const uint32_t shift = count & 255u;
    const uint64_t sign_fill = (bits >> 63) ? ~uint64_t(0) : uint64_t(0);
    if (shift >= 64u)
        return sign_fill;
    if (shift == 0u)
        return bits;
    // Unsigned operations avoid implementation-defined negative right shifts
    // and avoid shifting by the type width at either boundary.
    return (bits >> shift) | (sign_fill << (64u - shift));
}
