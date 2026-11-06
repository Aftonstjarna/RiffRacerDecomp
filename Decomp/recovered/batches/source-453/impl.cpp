#include "impl.hpp"
// Game.exe 0x440a90..0x440ac7 (RVA 0x40a90), ret 12:
// ECX is source; stack destination, offset, count; EAX is destination.
// Graphics-options callers 0x4a28f5/0x4a290b split a string into substrings.
NarrowString* RIFF_THISCALL NarrowString::construct_substring(
    NarrowString* destination, uint32_t offset, uint32_t count) const {
    // Construction into raw storage, not replacement assignment: do not free
    // an old heap pointer. Exactly these fields are initialized, in this order.
    // The other fifteen union bytes survive until the helper overwrites them.
    // With this==destination, the helper observes length zero/capacity fifteen;
    // only offset zero is then valid, regardless of the former source length.
    destination->capacity = 15;
    destination->length = 0;
    destination->storage.local[0] = 0;
    destination->assign_substring(this, offset, count);
    return destination;
}
