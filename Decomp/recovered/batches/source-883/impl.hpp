#ifndef RIFF_CLOSE_UPVALUES_HPP
#define RIFF_CLOSE_UPVALUES_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
struct Upvalue;
struct Value { uint32_t payload; int32_t tag; };
struct Global {
    unsigned char reserved0[20];
    uint8_t currentWhite; // +14
    uint8_t gcPhase;      // +15
    unsigned char reserved1[6];
    Upvalue* root;        // +1c
};
struct Upvalue {
    Upvalue* next;        // +0: open-state chain, then root chain
    uint8_t type;
    uint8_t marked;
    uint8_t reserved[2];
    Value* value;         // +8
    // +c/+10 are doubly linked open-list pointers until closed.
    union Storage {
        Value closed;
        struct Links { Upvalue* next; Upvalue* previous; } open;
    } storage;
};
struct State {
    unsigned char reserved0[16];
    Global* global;       // +10
    unsigned char reserved1[68];
    Upvalue* openUpvalues;// +58, descending value addresses
    // Original 0x4f49b0: ECX=this, EDX=level; caller has no stack arguments.
    void RIFF_FASTCALL closeUpvalues(Value* level);
};
// Integration dependencies, not additional recovered routines. Original calls use
// ECX/EDX plus caller-popped stack arguments (GCC regparm is NOT this ABI).
// Portable C adapters deliberately keep those details outside the algorithm.
void* reallocate(State*, void*, uint32_t oldSize, uint32_t newSize);
void barrier(State*, Upvalue*, void* child);
}
#endif
