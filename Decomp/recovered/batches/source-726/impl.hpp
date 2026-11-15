#ifndef RIFF_POINTER_SLOT_COPY_HPP
#define RIFF_POINTER_SLOT_COPY_HPP
#include <stdint.h>
namespace riff {
// Only the observed prefix is known; word zero is never interpreted.
struct RetainedObject { uint32_t opaque; uint32_t references; };
// Source and destination must describe valid forward-traversable slot ranges.
// This constructs/retains slots; it does not release old destination contents.
void pointer_slot_range_copy_retain(RetainedObject* const* begin,
                                   RetainedObject* const* end,
                                   RetainedObject** destination);
}
#endif
