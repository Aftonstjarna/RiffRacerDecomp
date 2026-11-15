#ifndef RIFF_CACHED_EVENT_LOOKUP_HPP
#define RIFF_CACHED_EVENT_LOOKUP_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct ScriptString {
    uint32_t opaque[2];
    uint32_t hash;
};
struct Value { uint32_t payload; uint32_t tag; };
struct Node {
    Value value;
    ScriptString* key;
    uint32_t key_tag;
    Node* next;
};
struct ScriptTable {
    uint8_t opaque[6];
    uint8_t absent_events;
    uint8_t hash_exponent;
    uint32_t opaque8;
    uint32_t opaque12;
    Node* nodes;
    // Original 0x4f5ca0: custom register ABI (ECX=this, EDX=event,
    // caller-cleaned stack string). This portable member models its semantics;
    // the original custom ABI is represented only by the GCC test declaration.
    Value* cached_event_lookup(uint32_t event, const ScriptString* name);
};
static_assert(sizeof(Value)==8, "value layout");
#if UINTPTR_MAX == 0xffffffffu
static_assert(sizeof(Node)==20, "node stride");
static_assert(offsetof(ScriptTable,nodes)==16, "table node offset");
#endif
}
#endif
