#include "impl.hpp"
// VA 0x4a4c50, 201 bytes: ECX owner, no stack arguments, no defined result.
// Callers 0x4a3a09 and 0x4a6611 proceed without testing EAX/AL.
// Device COM slot 118 is CreateQuery; signed HRESULT >= 0 includes S_FALSE.
void RR_THISCALL QueryOwner::createQueries() {
    for (unsigned group = 0; group < 2; ++group) {
        Query** slots = queries[group];
        // Reload device for every invocation: callbacks can replace it.
        if (device->vtable->createQuery(device, 10, &slots[0]) < 0) {
            clearQueries();
            return;
        }
        if (device->vtable->createQuery(device, 10, &slots[1]) < 0 ||
            device->vtable->createQuery(device, 12, &slots[2]) < 0) {
            clearQueries();
            return;
        }
    }
}
// Bounded cleanup dependency: first-call failure inlines this in the original;
// second/third-call failure invokes 0x4a4d20, with identical observable steps.
void RR_THISCALL QueryOwner::clearQueries() {
    for (unsigned group = 0; group < 2; ++group) {
        Query** slots = queries[group];
        Query* q = slots[2];
        if (q) q->vtable->release(q);
        q = slots[1];
        slots[2] = 0;
        if (q) q->vtable->release(q);
        q = slots[0];
        slots[1] = 0;
        if (q) q->vtable->release(q);
        slots[0] = 0;
    }
}
