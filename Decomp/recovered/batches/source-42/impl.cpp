#include "impl.hpp"
namespace riff {
// Game.exe VA 0x4a1bc0, RVA 0xa1bc0, 111 bytes. Called by request
// dispatcher 0x4a1900 case 1, which forwards the boolean result.
// Resource identities are unknown; slot +8 has a COM Release-compatible ABI.
// Return counts are ignored. Null owner, invalid interfaces, exceptions and
// concurrent access have no established safe behavior in the original.
bool __attribute__((thiscall)) request_cleanup(RequestOwner* owner) {
    Resource* current = owner->resource440;
    if (current) current->vtable->release(current);

    // Fetch BEFORE clearing: callbacks may change any of these fields.
    current = owner->resource43c;
    owner->resource440 = nullptr;
    if (current) current->vtable->release(current);

    current = owner->resource448;
    owner->resource43c = nullptr;
    if (current) current->vtable->release(current);

    current = owner->resource444;
    owner->resource448 = nullptr;
    if (current) current->vtable->release(current);

    owner->resource444 = nullptr;
    return true; // Only AL is defined in the original, not the full EAX.
}
}
