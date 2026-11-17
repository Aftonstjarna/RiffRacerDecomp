#ifndef RECORD6_GROWTH_HPP
#define RECORD6_GROWTH_HPP
#include <stdint.h>

// 32-bit address words from the original vector-like object. The middle word
// is its current end; growth reads only the allocation begin and end.
struct Record6Storage {
    uint32_t begin_address;
    uint32_t current_end_address;
    uint32_t allocation_end_address;
    uint32_t capacity_growth(uint32_t requested) const;
};
#endif
