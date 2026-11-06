#ifndef RECOVERED_RECORD48_HPP
#define RECOVERED_RECORD48_HPP
#include <stdint.h>

// Original 0x427010..0x42708b: twelve raw 32-bit fields, no vptr.
// Caller evidence: 0x423f57 and 0x424014 construct stack temporaries;
// 0x440b32 and 0x4413d4 construct the +0x24 member of 0x54-byte records.
// Some consumers read floats, but a semantic type/name is not established.
struct Record48 {
    uint32_t words[12];
    // The opaque source pointer preserves the instruction-level ability to
    // read unaligned storage; the original C++ parameter type is unresolved.
    explicit Record48(const void* source);
};
static_assert(sizeof(Record48) == 48, "original record size");
#endif
