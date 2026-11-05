#include "impl.hpp"
namespace riff {
// Original VA 0x49ca20..0x49caa7, thiscall, ret 4, bool in AL.
// resource+4 is a vbptr; vbtable[1] is a signed displacement relative
// to that vbptr, locating a vptr followed by a 32-bit reference count.
static ReferenceBase* referenceBase(ResourcePrefix* resource) {
    return reinterpret_cast<ReferenceBase*>(
        reinterpret_cast<char*>(resource) + 4 + resource->virtualBaseOffsets[1]);
}
static void releaseReference(ResourcePrefix* resource) {
    ReferenceBase* base = referenceBase(resource);
    // Unsigned subtraction deliberately preserves the original zero underflow.
    if (--base->references == 0)
        base->vtable->destroy(base, 1);
}
bool RIFF_THISCALL GraphicsEntry::release(bool force) {
    if (resource && (ownership == 0 || force)) {
        if (force) {
            // Original uses an unsigned comparison, reloads resource after
            // each decrement, and does not validate the vbtable or pointers.
            while (referenceBase(resource)->references > 1U)
                releaseReference(resource);
        }
        if (resource) {
            releaseReference(resource);
            resource = 0; // Even a destructor's replacement is overwritten.
        }
    }
    return resource == 0;
}
// Callers 0x49beb5 and 0x49bf85 pass false and inspect AL before further
// cleanup; 0x4b2450 passes true for each 12-byte table entry. No other entry
// fields are written here. Counts are non-atomic; no concurrency guarantee.
}
