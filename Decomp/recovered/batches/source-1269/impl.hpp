#ifndef RIFF_FINALIZE_ONE_HPP
#define RIFF_FINALIZE_ONE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct Value { uint32_t payload, tag; };
struct String { uint32_t unused[2], hash; };
struct Node { Value value; String* key; uint32_t key_tag; Node* next; };
struct Table { uint8_t pad0[6], absent, exponent; uint32_t pad8[2]; Node* nodes; };
struct Object { Object* next; uint8_t type, marked; uint8_t pad6[2]; Table* metatable; };
struct Global {
 uint8_t pad0[0x14]; uint8_t current_white; uint8_t pad15[0x1b]; Object* pending;
 uint8_t pad34[0xc]; uint32_t threshold, total; uint8_t pad48[0x1c]; Object** root_link;
 uint8_t pad68[0x40]; String* finalizer_name;
};
struct State {
 uint8_t pad0[8]; Value* top; uint8_t padc[4]; Global* global;
 uint8_t pad14[0x25]; uint8_t allow_hook;
 void finalize_one();
};
// Integration boundary: implement the VM call at 0x4f5830, using its
// ECX=state, EDX=function slot, caller-cleaned result count custom ABI.
// It may mutate state and stack and may not return on a script error.
void invoke_finalizer(State*, Value* function, int results);
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(State, global)==0x10 && offsetof(State, allow_hook)==0x39, "state layout");
static_assert(offsetof(Global, pending)==0x30 && offsetof(Global, root_link)==0x64 && offsetof(Global, finalizer_name)==0xa8, "global layout");
static_assert(offsetof(Object, metatable)==8 && sizeof(Node)==20, "object layout");
#endif
}
#endif
