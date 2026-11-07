#ifndef RIFF_RECORD68_HPP
#define RIFF_RECORD68_HPP
#include <stdint.h>
namespace riff {
// Field meanings are unresolved. All 68 bytes are copied; none are ownership-managed.
struct Record68 { uint32_t fields[13]; uint32_t tail[4]; };
static_assert(sizeof(Record68) == 68, "original record stride");
// Portable adapter for original 0x509e60 (RVA 0x109e60, 139 bytes).
// Original private ABI: ECX=first, EDX=last, stack=destination, caller pops.
// This is not standard MS fastcall (which pops its stack arguments).
Record68* record68_range_copy(const Record68* first, const Record68* last,
                              Record68* destination);
}
#endif
