#ifndef RECORD20_RANGE_COPY_HPP
#define RECORD20_RANGE_COPY_HPP
#include <stdint.h>
// Original 0x4b3e80..0x4b3eaf: ECX=begin, EDX=end, stack=destination,
// caller stack cleanup, EAX=result. This is an internal optimized helper ABI,
// not a member thiscall (there is no object). Portable entry below.
// Requires end reachable from begin by successive 20-byte increments and
// accessible storage for every load/store actually performed. No bounds checks.
// The 20 record bytes are opaque; no constructors, allocation or ownership work.
void* record20_range_copy(const void* begin, const void* end, void* destination);
#endif
