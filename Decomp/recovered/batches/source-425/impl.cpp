#include "impl.hpp"
// Game.exe 0x44f490..0x44f4e1 (RVA 0x4f490), 82 bytes.
// ECX=this, EDX=source, no stack arguments, EAX=this. A fastcall member
// models this register pair. Callers 0x5cfe43 application_entry and 0x535fa8
// save_device_refresh construct a fresh stack object from a virtual-call result.
// No destruction of previous storage, null check, Unicode decoding, or SEH.
// Scan precedes ALL destination writes; source must be readable and terminated.
// Objects with existing heap ownership must not be reconstructed this way.
WideString* RIFF_FASTCALL WideString::construct_terminated(const uint16_t* source) {
    const uint16_t* end = source;
    while (*end != 0) ++end;
    const uint32_t count = static_cast<uint32_t>(end - source);
    capacity = 7;
    length = 0;
    storage.local[0] = 0;
    if (count != 0) assign_range(source, count);
    // Original ignores helper EAX and explicitly returns this.
    return this;
}
