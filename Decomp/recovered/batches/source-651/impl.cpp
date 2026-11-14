#include "impl.hpp"

namespace {
// Portable counterpart of x86 DIV with a 64-bit dividend and a quotient
// known to fit in 32 bits (high < divisor). Avoids a compiler 64-bit division
// runtime dependency on freestanding i386. The widened remainder keeps the
// carry bit when the divisor is above 0x80000000.
uint32_t divide_limb(uint32_t high, uint32_t low, uint32_t divisor) {
    uint64_t remainder = high;
    uint32_t quotient = 0;
    for (unsigned bit = 32; bit != 0; --bit) {
        remainder = (remainder << 1) | ((low >> (bit - 1)) & 1u);
        quotient <<= 1;
        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= 1u;
        }
    }
    return quotient;
}
}

static uint64_t divide_magnitude(uint64_t numerator,
                                                           uint64_t divisor) {
    const uint32_t numeratorLow = static_cast<uint32_t>(numerator);
    const uint32_t numeratorHigh = static_cast<uint32_t>(numerator >> 32);
    const uint32_t divisorLow = static_cast<uint32_t>(divisor);
    const uint32_t divisorHigh = static_cast<uint32_t>(divisor >> 32);
    if (divisorHigh == 0) {
        const uint32_t quotientHigh = numeratorHigh / divisorLow;
        const uint32_t remainderHigh = numeratorHigh % divisorLow;
        const uint32_t quotientLow = divide_limb(remainderHigh, numeratorLow,
                                                divisorLow);
        return (static_cast<uint64_t>(quotientHigh) << 32) | quotientLow;
    }

    // Shift both operands until the divisor fits in one limb. The estimate
    // can exceed the true quotient by one, corrected using the unshifted
    // operands below, exactly as in the original normalization loop.
    uint64_t scaledDivisor = divisor;
    uint64_t scaledNumerator = numerator;
    do {
        scaledDivisor >>= 1;
        scaledNumerator >>= 1;
    } while ((scaledDivisor >> 32) != 0);
    uint32_t estimate = divide_limb(static_cast<uint32_t>(scaledNumerator >> 32),
                                    static_cast<uint32_t>(scaledNumerator),
                                    static_cast<uint32_t>(scaledDivisor));
    const uint32_t upperProduct = static_cast<uint32_t>(
        static_cast<uint64_t>(estimate) * divisorHigh);
    const uint64_t lowerProduct = static_cast<uint64_t>(estimate) * divisorLow;
    const uint32_t lowerProductHigh = static_cast<uint32_t>(lowerProduct >> 32);
    const uint32_t productHigh = lowerProductHigh + upperProduct;
    const bool carry = productHigh < lowerProductHigh;
    if (carry || productHigh > numeratorHigh ||
        (productHigh == numeratorHigh &&
         static_cast<uint32_t>(lowerProduct) > numeratorLow)) {
        --estimate;
    }
    return estimate;
}

// Game.exe VA 0x8f9830, size 170: signed CRT-style helper, not a member.
// Callers 0x562f9d and 0x564878 push divisor then numerator (high then low),
// consume EDX:EAX, and rely on RET 16. No object, globals, imports or FS use.
// Original writes only its by-value argument slots while taking magnitudes.
// Unsigned arithmetic preserves MIN/-1 wrapping without signed overflow.
// Zero divisor reaches a native 32-bit divide by zero; its exception delivery
// is platform-specific and is outside the portable nonzero-input contract.
extern "C" int64_t RIFF_STDCALL recovered_signed64_divide(int64_t numerator,
                                                        int64_t divisor) {
    uint64_t n = static_cast<uint64_t>(numerator);
    uint64_t d = static_cast<uint64_t>(divisor);
    if (numerator < 0) n = uint64_t(0) - n;
    if (divisor < 0) d = uint64_t(0) - d;
    uint64_t q = divide_magnitude(n, d);
    if ((numerator < 0) != (divisor < 0)) q = uint64_t(0) - q;
    // Both target ABIs use two's-complement signed conversion.
    return static_cast<int64_t>(q);
}
