#ifndef RIFF_NEW_KEY_HPP
#define RIFF_NEW_KEY_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct Value { uint32_t payload; int32_t tag; };
struct Node { Value value; Value key; Node* next; };
struct Table {
 uint8_t header[7]; uint8_t hashLog2;
 uint32_t metatable; Value* array; Node* nodes; Node* lastFree;
 Table* gcLink; uint32_t arraySize;
};
struct Global { uint8_t opaque[40]; Table* grayAgain; };
struct State;
// VM dependency boundaries: mainBucket=0x4f0110, rehash=0x4f0800,
// ensureValue=0x4f0c50. The last two remain unrecovered here.
struct Services {
 Node* (*mainBucket)(Table*,const Value*);
 void (*rehash)(State*,Table*,const Value*);
 Value* (*ensureValue)(State*,Table*,const Value*);
};
struct State {
 uint8_t opaque[16]; Global* global;
 Value* newKey(Table*,const Value*,const Services&);
};
static_assert(sizeof(Value)==8,"value stride");
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Node)==20,"node stride");
static_assert(offsetof(Table,lastFree)==20,"free cursor");
static_assert(offsetof(Table,gcLink)==24,"GC link");
static_assert(offsetof(State,global)==16,"global state");
#endif
}
#endif
