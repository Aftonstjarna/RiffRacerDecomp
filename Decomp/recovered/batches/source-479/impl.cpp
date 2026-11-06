#include "impl.hpp"
// VA 0x416af0, 100 bytes. ECX=this, one stack source argument, EAX=this,
// ret 4. Callers include vector insertion at 0x49aad8 (24-byte stride)
// and prefix/result construction at 0x4b2d59. No allocation or deletion.
static void move_bytes(void* destination, const void* source, uint32_t count) {
    unsigned char* d = static_cast<unsigned char*>(destination);
    const unsigned char* s = static_cast<const unsigned char*>(source);
    if (reinterpret_cast<uintptr_t>(d) > reinterpret_cast<uintptr_t>(s)) {
        while (count) { --count; d[count] = s[count]; }
    } else {
        for (uint32_t i=0; i<count; ++i) d[i] = s[i];
    }
}
NarrowString* RIFF_THISCALL NarrowString::move_construct(NarrowString* source) {
    // Ordered initialization matters for self-move: it becomes empty. This is
    // construction into raw storage; any previous destination pointer is lost.
    capacity = 15;
    length = 0;
    storage.local[0] = 0;
    if (source->capacity < 16) {
        const uint32_t count = source->length + uint32_t(1);
        // Original INC/JE skips the import when UINT_MAX wraps to zero.
        if (count) move_bytes(&storage, &source->storage, count);
    } else {
        storage.heap = source->storage.heap;
        source->storage.heap = 0;
    }
    length = source->length;
    capacity = source->capacity;
    source->capacity = 15;
    source->length = 0;
    source->storage.local[0] = 0;
    return this;
}
