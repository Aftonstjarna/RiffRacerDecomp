#ifndef RIFF_RESIZE_HPP
#define RIFF_RESIZE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
union Payload { uint32_t bits; float number; };
struct Value { Payload payload; uint32_t tag; };
struct Node { Value value, key; Node* next; };
struct Table {
 uint8_t header[7], hashLog2;
 uint32_t metatable;
 Value* array;
 Node* nodes;
 Node* lastFree;
 uint32_t gcLink;
 int32_t arraySize;
};
struct State;
// Original 0x486ab0 receives state and these literal messages respectively:
// 0x9fdb34 "memory allocation error: block too big"
// 0x9fd750 "table index is nil"; 0x9fd714 "table index is NaN".
enum Error { ArrayTooLarge, NilKey, NaNKey };
// These are dependency boundaries, not recovered VM implementations. Allocation
// errors normally do not return. A port must supply the VM's actual services.
struct Services {
 void (*resizeArray)(State*,Table*,int32_t);
 void (*initializeHash)(State*,Table*,int32_t);
 Value* (*ensureInteger)(State*,Table*,int32_t);
 Value* (*lookup)(Table*,const Value*);
 Value* (*newKey)(State*,Table*,const Value*);
 void* (*reallocate)(State*,void*,uint32_t,uint32_t);
 void (*error)(State*,Error);
};
struct State { void resize(Table*,int32_t arraySize,int32_t hashRequest,const Services&); };
inline Value* nilValue() { return reinterpret_cast<Value*>(uintptr_t(0x99a41c)); }
inline Node* emptyHash() { return reinterpret_cast<Node*>(uintptr_t(0x99a424)); }
static_assert(sizeof(Value)==8,"value stride");
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Table)==32 && sizeof(Node)==20,"original i386 layouts");
static_assert(offsetof(Table,arraySize)==28,"array count offset");
#endif
}
#endif
