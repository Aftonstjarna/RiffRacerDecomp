#ifndef WIDE_ENTRY_GROWTH_POLICY_HPP
#define WIDE_ENTRY_GROWTH_POLICY_HPP
#include <stdint.h>

// 32-bit original vector fields are addresses; the middle field is the end.
struct WideEntryVector {
    uint32_t begin;
    uint32_t end;
    uint32_t capacity_end;
    uint32_t growth_policy(uint32_t requested) const;
};
#endif
