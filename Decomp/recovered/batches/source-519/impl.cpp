#include "impl.hpp"

namespace {
// Portable equivalent of x86 DIV for a 64/32 division whose quotient fits
// in 32 bits (high < divisor). Avoids requiring a compiler's 64-bit divide
// runtime in a freestanding Linux port. The carry retains the 33rd bit.
uint32_t divide_words(uint32_t high, uint32_t low, uint32_t divisor,
                      uint32_t& remainder) {
    uint32_t quotient = 0;
    for (unsigned bit = 32; bit != 0; --bit) {
        const bool carry = (high >> 31) != 0;
        high = (high << 1) | ((low >> (bit - 1)) & 1u);
        quotient <<= 1;
        if (carry || high >= divisor) {
            high -= divisor;
            quotient |= 1u;
        }
    }
    remainder = high;
    return quotient;
}
}

// Evidence: /reference/Decomp/native/unsigned64_remainder.S and direct
// Game.exe disassembly [0x8fc300,0x8fc375). No memory or global side effects.
// One direct call found at 0x5a27fb: dividend derives from a queried 64-bit
// value minus [edi+0x128] plus [esi+0xa8]; divisor is [esi+0xf0/+0xf4].
// The caller guards zero and converts the resulting unsigned value to double.
// Those caller fields are context only, not additional recovered functions.
extern "C" uint64_t RIFF_STDCALL recovered_unsigned64_remainder(
    uint64_t dividend, uint64_t divisor) {
    const uint32_t dividendLow = static_cast<uint32_t>(dividend);
    const uint32_t dividendHigh = static_cast<uint32_t>(dividend >> 32);
    const uint32_t divisorLow = static_cast<uint32_t>(divisor);
    const uint32_t divisorHigh = static_cast<uint32_t>(divisor >> 32);
    if (divisorHigh == 0) {
        // Two divisions, with the first remainder feeding the second.
        const uint32_t highRemainder = dividendHigh % divisorLow;
        uint32_t remainder;
        divide_words(highRemainder, dividendLow, divisorLow, remainder);
        return remainder;
    }

    uint64_t scaledDivisor = divisor;
    uint64_t scaledDividend = dividend;
    do {
        scaledDivisor >>= 1;
        scaledDividend >>= 1;
    } while ((scaledDivisor >> 32) != 0);

    uint32_t unusedRemainder;
    const uint32_t estimate = divide_words(
        static_cast<uint32_t>(scaledDividend >> 32),
        static_cast<uint32_t>(scaledDividend),
        static_cast<uint32_t>(scaledDivisor), unusedRemainder);

    // Build estimate * divisor, retaining overflow beyond bit 63. Original
    // MUL/ADD carry and unsigned comparisons detect an estimate one too high.
    const uint64_t lowProduct = static_cast<uint64_t>(estimate) * divisorLow;
    const uint64_t highProduct = static_cast<uint64_t>(estimate) * divisorHigh
                               + (lowProduct >> 32);
    uint64_t product = (highProduct << 32) | static_cast<uint32_t>(lowProduct);
    if ((highProduct >> 32) != 0 || product > dividend)
        product -= divisor;
    return dividend - product;
}
