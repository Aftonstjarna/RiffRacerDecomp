#ifndef RIFF_RECORD12_HPP
#define RIFF_RECORD12_HPP
#include <stdint.h>
namespace riff {
// Field meanings are unresolved. These are opaque bits, not floating values.
#pragma pack(push, 4)
struct Record12 {
    uint64_t payload;
    uint32_t tail;
};
#pragma pack(pop)
static_assert(sizeof(Record12) == 12, "original record stride");
Record12* copy_assign_range(const Record12* first, const Record12* last,
                            Record12* destination);
}
#endif
