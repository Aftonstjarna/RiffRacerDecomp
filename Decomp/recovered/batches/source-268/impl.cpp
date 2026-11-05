#include "impl.hpp"
// Original 0x44f6f0..0x44f75a: ECX destination, stack source, EAX destination,
// callee pops four bytes. Caller 0x53623e consumes a temporary after prepend.
// Storage is UTF-16, independent of the platform's wchar_t width.
static void move_bytes(void* destination, const void* source, uint32_t count) {
    unsigned char* d = static_cast<unsigned char*>(destination);
    const unsigned char* s = static_cast<const unsigned char*>(source);
    if (reinterpret_cast<uintptr_t>(d) > reinterpret_cast<uintptr_t>(s)) {
        while (count) { --count; d[count] = s[count]; }
    } else {
        for (uint32_t i = 0; i < count; ++i) d[i] = s[i];
    }
}
WideString* RIFF_THISCALL WideString::move_construct(WideString* source) {
    // Initialization precedes reading source: self-move consequently empties it.
    // This is construction into raw storage; an old heap allocation is not freed.
    capacity = 7;
    length = 0;
    storage.local[0] = 0;
    if (source->capacity < 8) {
        uint32_t units = source->length + uint32_t(1);
        if (units != 0) {
            // Both additions in the original wrap at 32 bits, even for corrupt
            // metadata. Only valid memory ranges may actually be copied.
            move_bytes(&storage, &source->storage, units * uint32_t(2));
        }
    } else {
        storage.heap = source->storage.heap;
        source->storage.heap = 0;
    }
    length = source->length;
    capacity = source->capacity;
    source->capacity = 7;
    source->length = 0;
    source->storage.local[0] = 0;
    return this;
}
