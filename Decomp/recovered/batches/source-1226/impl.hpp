#ifndef RECOVERED_SCRIPT_GC_HPP
#define RECOVERED_SCRIPT_GC_HPP
#include <stdint.h>
struct GCObject { uint8_t prefix[5]; uint8_t flags; };
struct GCValue { GCObject* object; int32_t tag; };
struct GCNode { GCValue value; GCValue key; uint32_t link; };
struct GCTable {
    uint8_t prefix[5]; uint8_t flags; uint8_t unused6; uint8_t hash_log2;
    uint32_t unused8; GCValue* array; GCNode* nodes; uint32_t unused14;
    GCTable* next; uint32_t array_size;
    void clear_weak_entries();
};
// Accepts a null head, unlike invoking a C++ member on null.
void clear_weak_entries(GCTable* head);
#endif
