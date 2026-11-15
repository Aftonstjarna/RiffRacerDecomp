#ifndef RECORD513_IMPL_HPP
#define RECORD513_IMPL_HPP
#include <stdint.h>
namespace riff {
// Opaque record: the routine gives no evidence for individual field meanings.
struct Record513 { unsigned char bytes[513]; };
// VA 0x416aa0, 53 bytes. Valid complete source range and writable destination
// required. Integer addresses preserve the original null-skip and 32-bit wrap.
uintptr_t copy_record513_range(const Record513* first, const Record513* last,
                               uintptr_t destination);
}
#endif
