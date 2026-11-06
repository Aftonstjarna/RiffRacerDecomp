#include "impl.hpp"
#include <stdint.h>

int double_integer_parity(double value)
{
    // Decode the IEEE-754 binary64 representation without floating arithmetic.
    // Original and supported Linux/Windows targets are little-endian.
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    uint64_t bits = 0;
    for (unsigned i = 0; i != 8; ++i)
        bits |= static_cast<uint64_t>(bytes[i]) << (8 * i);
    const uint64_t magnitude = bits & UINT64_C(0x7fffffffffffffff);
    if (magnitude == 0)
        return 2;
    const unsigned biased_exponent = static_cast<unsigned>(magnitude >> 52);
    if (biased_exponent < 1023 || biased_exponent == 2047)
        return 0;
    const unsigned exponent = biased_exponent - 1023;
    // At and above 2^53 every representable finite value is even.
    if (exponent >= 53)
        return 2;
    const uint64_t significand = (magnitude & UINT64_C(0x000fffffffffffff))
                             | UINT64_C(0x0010000000000000);
    const unsigned fractional_bits = 52 - exponent;
    const uint64_t fractional_mask = (UINT64_C(1) << fractional_bits) - 1;
    if ((significand & fractional_mask) != 0)
        return 0;
    return ((significand >> fractional_bits) & 1) ? 1 : 2;
}
