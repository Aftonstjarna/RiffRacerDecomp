#ifndef RIFF_SCRIPT_TABLE_HPP
#define RIFF_SCRIPT_TABLE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// Names reflect observed script VM layout; full VM types are not recovered.
struct StringHeader { uint32_t opaque[2]; uint32_t hash; };
union Payload { uint32_t bits; float number; const StringHeader* string; };
struct Value { Payload payload; uint32_t tag; };
struct Node { Value value; Value key; Node* next; };
struct Table {
    uint8_t opaque0[7];
    uint8_t hashLog2;
    uint32_t opaque8;
    Value* array;
    Node* nodes;
    // Original entry 0x4f0110 uses ECX=this, EDX=key, no stack arguments.
    Node* RIFF_FASTCALL mainBucket(const Value* key) const;
};
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(Value)==8, "VM value layout");
static_assert(sizeof(Node)==20, "VM hash node stride");
static_assert(offsetof(Table,hashLog2)==7, "hash exponent offset");
static_assert(offsetof(Table,nodes)==16, "node base offset");
static_assert(offsetof(StringHeader,hash)==8, "string hash offset");
#endif
}
#endif
