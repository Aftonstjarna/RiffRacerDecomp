#ifndef RIFF_ENSURE_INTEGER_SLOT_HPP
#define RIFF_ENSURE_INTEGER_SLOT_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
union Payload { uint32_t bits; float number; };
struct Value { Payload payload; uint32_t tag; };
struct Node { Value value; Value key; Node* next; };
struct Table {
    uint8_t header[7]; uint8_t hashLog2;
    uint32_t metatable;
    Value* array;
    Node* nodes;
    Node* lastFree;
    uint32_t gcLink;
    uint32_t arraySize;
};
struct State;
// Dependency boundaries, not replacements for the VM's lookup/allocator/GC.
struct Services {
    Value* (*getInteger)(Table*,int32_t);
    Value* (*newKey)(State*,Table*,const Value*);
};
struct State {
    // Opaque state: this routine only forwards its address to newKey.
    Value* ensureIntegerSlot(Table*,int32_t,const Services&);
};
inline Value* nilSentinel() { return reinterpret_cast<Value*>(uintptr_t(0x99a41c)); }
static_assert(sizeof(Value)==8,"tagged value stride");
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Table)==32,"table layout");
static_assert(sizeof(Node)==20,"node layout");
static_assert(offsetof(Table,arraySize)==28,"array size offset");
#endif
}
#endif
