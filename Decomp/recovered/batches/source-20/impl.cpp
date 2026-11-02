#include "impl.hpp"
// Game.exe VA 0x536070, RVA 0x136070, 55 bytes. Caller 0x5359ce
// passes a prefix ending just after a path separator; ECX is the source.
// Stack: destination, unused slot (caller happens to push capacity), count.
// EAX returns destination; callee removes 12 bytes. No local EH frame.
extern "C" WideString* __attribute__((thiscall)) recovered_wide_prefix_construct(
    const WideString* source, WideString* destination, u32, u32 maximum) {
    // This is construction, not assignment: old storage is not freed. The
    // other 14 storage bytes remain untouched before calling the helper.
    // Preserve this order, including for source == destination: aliasing
    // makes the helper see an empty inline string, irrespective of old size.
    destination->capacity = 7;
    destination->length = 0;
    destination->storage.inline_data[0] = 0;
    // Reference helper at 0x44fb30: clamps count to source length, chooses
    // inline/heap storage, allocates if necessary and writes a terminator.
    // Its allocation and exception semantics remain a reference dependency,
    // not newly recovered scope. No writes follow if that call throws.
    original_wide_assign_substring(destination, source, 0, maximum);
    return destination;
}
