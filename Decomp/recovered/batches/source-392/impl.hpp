#ifndef RECORD44_IMPL_HPP
#define RECORD44_IMPL_HPP
#include <stdint.h>
#include <stddef.h>
namespace recovered {
// Field meanings are unresolved. Layout and copy granularity are evidenced at
// Game.exe 0x4b31e0..0x4b3253; bytes 25..27 are never read or written.
struct Record44 {
    uint32_t word0, word4, word8, word12, word16, word20;
    uint8_t byte24;
    uint8_t untouched25[3];
    uint32_t word28, word32, word36, word40;
};
static_assert(sizeof(Record44) == 44, "record stride");
static_assert(offsetof(Record44, word28) == 28, "field offset");
// Valid ranges have end reachable from begin by forward whole-record steps.
// Empty ranges do not dereference either source or destination. No allocation,
// destruction, bounds checks or reverse-copy handling occurs.
Record44* copy_range(const Record44* begin, const Record44* end, Record44* destination);
}
#endif
