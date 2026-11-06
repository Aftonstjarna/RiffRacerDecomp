#ifndef RECORD16_IMPL_HPP
#define RECORD16_IMPL_HPP
#include <stdint.h>
// Original 0x4b3df0: ECX=begin, EDX=end, stack=destination; caller pops.
// Opaque 16-byte records; no evidence establishes field names or types.
// End must be reachable by successive 16-byte advances. No bounds checks.
void* record16_range_copy(const void* begin, const void* end, void* destination);
#endif
