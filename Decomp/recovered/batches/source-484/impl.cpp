#include "impl.hpp"

// Original: 31 bytes, three paths: CL < 32, 32 <= CL < 64, CL >= 64.
// SHLD/SHL combine the two input words on the first path. On the second,
// the low input word becomes the high output word; the low output is zero.
// The guard is essential: shifting a C++ uint64_t by 64 would be undefined.
// A direct caller at 0x5ca441 loads EAX=EDI, EDX=[ESI+4], CL=32;
// it subsequently stores EAX to [ESI]. No object/this pointer is involved.
uint64_t u64_shift_left(uint64_t value, uint32_t count)
{
    const uint32_t byte_count = count & 0xffu;
    if (byte_count >= 64u)
        return 0;
    return value << byte_count;
}
