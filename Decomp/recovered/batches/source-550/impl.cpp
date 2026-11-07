#include "impl.hpp"
// Game.exe 0x426960..0x4269e9. The caller at 0x426795 passes the
// vector's begin/end and newly allocated storage, then destroys/deletes the
// old range. Three additional template/tag arguments are unused here;
// caller removes all six arguments. This helper itself is cdecl, not thiscall.
static void move_bytes(unsigned char* d,const unsigned char* s,uint32_t n) {
    if (reinterpret_cast<uintptr_t>(d)>reinterpret_cast<uintptr_t>(s)) {
        while(n) { --n; d[n]=s[n]; }
    } else {
        for(uint32_t i=0;i<n;++i) d[i]=s[i];
    }
}
NarrowString* RIFF_CDECL narrow_range_move_construct(
    NarrowString* first,NarrowString* last,NarrowString* destination) {
    while(first!=last) {
        if(destination) {
            // Ordered writes intentionally preserve original alias behavior.
            // There is no cleanup of a previous destination allocation.
            destination->capacity=15;
            destination->length=0;
            destination->storage.local[0]=0;
            if(first->capacity<16) {
                const uint32_t count=first->length+uint32_t(1);
                // INC/JE skips memmove for corrupt UINT_MAX length.
                if(count) move_bytes(destination->storage.local,first->storage.local,count);
            } else {
                destination->storage.heap=first->storage.heap;
                first->storage.heap=0;
            }
            destination->length=first->length;
            destination->capacity=first->capacity;
            first->capacity=15;
            first->length=0;
            first->storage.local[0]=0;
        }
        ++first;
        // The original adds 24 even to NULL. Avoid C++ null arithmetic;
        // a multi-element NULL destination soon becomes invalid address 24.
        destination=reinterpret_cast<NarrowString*>(
            reinterpret_cast<uintptr_t>(destination)+sizeof(NarrowString));
    }
    return destination;
}
