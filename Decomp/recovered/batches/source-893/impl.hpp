#ifndef RIFF_GC_SEPARATE_HPP
#define RIFF_GC_SEPARATE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct String { uint32_t opaque[2]; uint32_t hash; };
struct Node { uint32_t value, value_tag; String* key; uint32_t key_tag; Node* next; };
struct Table { uint8_t opaque[6]; uint8_t absent_events, hash_exponent; uint32_t opaque8, opaque12; Node* nodes; };
struct Object { Object* next; uint8_t type, marks; uint8_t opaque6[2]; Table* metatable; uint32_t opaque12; uint32_t payload_size; uint32_t opaque20; };
struct Global {
    uint8_t opaque0[0x30]; Object* finalizer_tail;
    uint8_t opaque34[0x30]; Object** root_link;
    uint8_t opaque68[0x40]; String* finalizer_name;
};
struct State {
    uint8_t opaque[0x10]; Global* global;
    // VA 0x4f1090: original fastcall ECX=state, EDX=force, EAX=bytes.
    // A normal portable member keeps the recovered behavior separate from ABI glue.
    uint32_t separate_finalizable(uint32_t force);
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(sizeof(Node)==20,"hash node stride");
static_assert(sizeof(Object)==24,"userdata header");
static_assert(offsetof(Global,root_link)==0x64,"root link");
static_assert(offsetof(Global,finalizer_name)==0xa8,"finalizer event name");
#endif
}
#endif
