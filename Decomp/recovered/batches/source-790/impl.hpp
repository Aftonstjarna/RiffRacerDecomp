#ifndef RIFF_TABLE_GET_VALUE_HPP
#define RIFF_TABLE_GET_VALUE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
struct StringHeader { uint32_t opaque[2]; uint32_t hash; };
union Payload { uint32_t bits; float number; const StringHeader* string; };
struct Value { Payload payload; uint32_t tag; };
struct Node { Value value; Value key; Node* next; };
struct Table {
    uint8_t opaque[7];
    uint8_t hashLog2;
    uint32_t opaque8;
    Value* array;
    Node* nodes;
    uint32_t opaque20[2];
    uint32_t arraySize;
    // Original 0x4f0bb0: ECX=this, EDX=key, EAX=result, no stack args.
    const Value* RIFF_FASTCALL getValue(const Value* key) const;
    // Accepted reference dependencies, deliberately not recovered in this task.
    const Value* RIFF_FASTCALL getString(const StringHeader*) const;
    const Value* RIFF_FASTCALL getInteger(int32_t) const;
    Node* RIFF_FASTCALL mainBucket(const Value*) const;
};
static_assert(sizeof(Value)==8,"value layout");
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Node)==20,"node stride");
static_assert(offsetof(Table,nodes)==16,"nodes offset");
static_assert(offsetof(Table,arraySize)==28,"array size offset");
#endif
}
#endif
