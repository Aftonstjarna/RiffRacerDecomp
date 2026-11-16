#ifndef RIFF_STRING_SLOT_HPP
#define RIFF_STRING_SLOT_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct String { uint8_t header[8]; uint32_t hash; };
union Payload { uint32_t bits; String* string; };
struct Value { Payload payload; uint32_t tag; };
struct Node { Value value; Value key; Node* next; };
struct Table {
 uint8_t header[7]; uint8_t hashLog2;
 uint32_t metatable; Value* array; Node* nodes; Node* lastFree;
 uint32_t gcLink; uint32_t arraySize;
};
struct State;
// Allocation, rehash and GC policy belong to the existing VM, not this lookup.
struct Services { Value* (*newKey)(State*,Table*,const Value*); };
struct State { Value* ensureStringSlot(Table*,String*,const Services&); };
inline Value* nilSentinel() { return reinterpret_cast<Value*>(uintptr_t(0x99a41c)); }
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Value)==8,"tagged value layout");
static_assert(sizeof(Node)==20,"node layout");
static_assert(offsetof(Node,key)==8 && offsetof(Node,next)==16,"node fields");
static_assert(offsetof(Table,nodes)==16 && sizeof(Table)==32,"table layout");
#endif
static_assert(offsetof(String,hash)==8,"interned string hash");
}
#endif
