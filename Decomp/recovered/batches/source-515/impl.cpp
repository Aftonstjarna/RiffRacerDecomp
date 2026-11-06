#include "impl.hpp"

// Unsigned arithmetic expresses the original modulo-2^64 behavior even for
// bit patterns used by signed callers. No pointers, object state or imports.
extern "C" uint64_t RIFF_STDCALL u64_multiply_low(uint64_t a, uint64_t b)
{
    const uint32_t a_low = static_cast<uint32_t>(a);
    const uint32_t b_low = static_cast<uint32_t>(b);
    const uint32_t a_high = static_cast<uint32_t>(a >> 32);
    const uint32_t b_high = static_cast<uint32_t>(b >> 32);
    const uint64_t low_product = static_cast<uint64_t>(a_low) * b_low;
    if ((a_high | b_high) == 0)
        return low_product;
    // Only the low 32 bits of each cross-product contribute. The high-high
    // product begins at bit 64 and is discarded by the original routine.
    const uint32_t cross = a_high * b_low + a_low * b_high;
    const uint32_t high = static_cast<uint32_t>(low_product >> 32) + cross;
    return (static_cast<uint64_t>(high) << 32) | static_cast<uint32_t>(low_product);
}
