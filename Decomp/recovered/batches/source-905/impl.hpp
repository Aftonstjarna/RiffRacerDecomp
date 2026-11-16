#ifndef RIFF_LUA_CLOSURE_ALLOCATE_HPP
#define RIFF_LUA_CLOSURE_ALLOCATE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
struct Table;
struct Prototype;
struct Upvalue;
struct Closure {
    void* next;                       // +00: GC root link
    uint8_t type;                     // +04: LUA_TFUNCTION (6)
    uint8_t marked;                   // +05: current white & 3
    uint8_t is_c;                     // +06: zero for Lua closure
    uint8_t upvalue_count;            // +07: low byte of requested count
    void* gc_list;                    // +08: deliberately uninitialized here
    Table* environment;              // +0c
    Prototype* prototype;             // +10: deliberately uninitialized here
    // count Upvalue* slots follow at +14, not part of this fixed header.
};
struct Global {
    uint8_t unknown00[12];
    void* (*allocator)(void*, void*, uint32_t, uint32_t); // cdecl, +0c
    void* allocator_user;             // +10
    uint8_t current_white;            // +14
    uint8_t unknown15[7];
    void* root;                       // +1c
    uint8_t unknown20[36];
    uint32_t allocated_bytes;         // +44: owned by reallocate dependency
    uint8_t unknown48[16];
    void* panic;                      // +58: opaque here, not called by target
};
struct State {
    uint8_t unknown00[16];
    Global* global;                   // +10
    uint8_t unknown14[76];
    void* error_frame;                // +60, used only by reallocate dependency
    Closure* allocate_lua_closure(uint32_t count, Table* environment);
};
// Integration boundary: accepted script-reallocate (0x4f7d10), NOT recovered
// in this task. The host port must supply its allocation/error semantics.
// Original ABI is private ECX/EDX + caller-cleaned stack sizes; test.cpp
// supplies the only compiler-specific oracle adapter.
void* reallocate(State*, void* memory, uint32_t old_bytes, uint32_t new_bytes);
static_assert(sizeof(void*) == 4, "original VM uses 32-bit pointers");
static_assert(sizeof(Closure) == 20, "closure header");
static_assert(offsetof(Closure, environment) == 12, "environment field");
static_assert(offsetof(State, global) == 16, "state global field");
static_assert(offsetof(State, error_frame) == 96, "error frame field");
static_assert(offsetof(Global, root) == 28, "root field");
static_assert(offsetof(Global, allocated_bytes) == 68, "accounting field");
}
#endif
