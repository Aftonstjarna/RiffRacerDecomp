#ifndef RECORD12_COPY_RANGE_HPP
#define RECORD12_COPY_RANGE_HPP
#include <stdint.h>
// Original 0x42bb40: raw 12-byte records; no field types are established.
// Precondition: end is reachable from begin by forward 12-byte steps.
// Each nonnull destination step must address 12 writable bytes; source must
// address 12 readable bytes. Overlap follows the ordered 8+4 transfers below.
void* record12_copy_range(const void* begin, const void* end, void* destination);
#endif
