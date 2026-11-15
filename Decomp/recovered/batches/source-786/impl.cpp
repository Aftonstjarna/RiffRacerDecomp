#include "impl.hpp"

// Define the original ADD's wraparound without C++ signed-overflow UB or
// implementation-defined out-of-range unsigned-to-signed conversions.
static int32_t signed_bits(uint32_t value)
{
    return value <= 0x7fffffffu ? static_cast<int32_t>(value)
        : -1 - static_cast<int32_t>(~value);
}

int32_t RIFF_FASTCALL choose_array_capacity(const int32_t* buckets, int32_t* total)
{
    int32_t occupied = 0;
    int32_t selected_entries = 0;
    int32_t selected_capacity = 0;
    int32_t capacity = 1;
    if (*total > 0) {
        do {
            if (*buckets > 0) {
                occupied = signed_bits(static_cast<uint32_t>(occupied)
                                     + static_cast<uint32_t>(*buckets));
                // IDIV-equivalent truncation toward zero, including a wrapped
                // negative capacity. The original uses CDQ/SUB/SAR for /2.
                if (occupied > capacity / 2) {
                    selected_capacity = capacity;
                    selected_entries = occupied;
                }
            }
            if (occupied == *total)
                break;
            ++buckets;
            capacity = signed_bits(static_cast<uint32_t>(capacity) * 2u);
        } while (capacity / 2 < *total);
    }
    *total = selected_capacity;
    return selected_entries;
}
// Caller at 0x4f08cc passes stack histogram [ebp-0x70] and count
// [ebp-0x74], subtracts the returned entries from the hash-entry count,
// and passes the overwritten capacity to 0x4f0660. No object fields,
// allocation, calls, globals or FS registration occur in this helper.
