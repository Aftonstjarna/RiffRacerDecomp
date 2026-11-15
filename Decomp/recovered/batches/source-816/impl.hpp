#ifndef RIFF_SCRIPT_VALUE_SLOT_HPP
#define RIFF_SCRIPT_VALUE_SLOT_HPP
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
// Dependencies retain VM lookup, allocation/rehashing, GC and error policy.
struct Services {
    Value* (*getValue)(Table*,const Value*);
    Value* (*newKey)(State*,Table*,const Value*);
    void (*runtimeError)(State*,const char*);
};
struct State {
    Value* ensureValueSlot(Table*,const Value*,const Services&);
};
inline Value* nilSentinel() { return reinterpret_cast<Value*>(uintptr_t(0x99a41c)); }
static_assert(sizeof(Value)==8,"value stride");
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Table)==32,"table stride");
static_assert(sizeof(Node)==20,"node stride");
static_assert(offsetof(Table,array)==12,"array offset");
static_assert(offsetof(Table,arraySize)==28,"array size offset");
#endif
}
#endif
