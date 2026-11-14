#ifndef RIFF_RECORD12_HPP
#define RIFF_RECORD12_HPP
#include <stdint.h>
namespace riff {
// Field meanings and the original template/type names are not established.
struct Record12 { uint32_t words[3]; };
static_assert(sizeof(Record12) == 12, "original record stride");
Record12* record12_range_copy_construct(const Record12* first,
                                       const Record12* last,
                                       Record12* destination);
}
#endif
