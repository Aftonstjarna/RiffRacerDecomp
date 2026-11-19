#include "impl.hpp"

// Game.exe 0x49c050. The original subtracts addresses in 32 bits, then
// interprets that difference as signed before dividing by sizeof(entry)=28.
uint32_t WideEntryVector::growth_policy(uint32_t requested) const {
    const uint32_t difference = capacity_end - begin;
    const int32_t signed_difference = difference < 0x80000000u
        ? static_cast<int32_t>(difference)
        : static_cast<int32_t>(static_cast<int64_t>(difference) - INT64_C(0x100000000));
    const uint32_t capacity = static_cast<uint32_t>(signed_difference / 28);
    const uint32_t half = capacity >> 1;
    const uint32_t candidate = (UINT32_C(0x09249249) - half < capacity)
        ? 0u : capacity + half;
    return candidate < requested ? requested : candidate;
}
