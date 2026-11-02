#include "impl.hpp"
// Game.exe VA 0x4a4d20, length 83. ECX is owner; no stack arguments.
// query_create (0x4a4c50) makes types 10,10,12 in each group.
// device_release (0x4a6330) and device_destroy (0x4a5c40) also call this.
// COM slot +8 is stdcall with an explicit object pointer; its count is ignored.
// No null-owner check, exception handling, or deduplication exists in the original.
extern "C" void __attribute__((thiscall)) recovered_query_release(QueryOwner* owner) {
    for (unsigned group = 0; group != 2; ++group) {
        Query** slots = owner->queries[group];
        Query* current = slots[2];
        if (current) current->vtable->release(current);
        // Keep the original read-before-clear order, including callback visibility.
        current = slots[1];
        slots[2] = nullptr;
        if (current) current->vtable->release(current);
        current = slots[0];
        slots[1] = nullptr;
        if (current) current->vtable->release(current);
        slots[0] = nullptr;
    }
}
