#ifndef SCRIPT_STACK_RESIZE_HPP
#define SCRIPT_STACK_RESIZE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FAST __fastcall
#else
#define RIFF_FAST __attribute__((fastcall))
#endif
namespace riff {
struct State;
// Port bindings for external helpers. Reallocate must preserve the original
// allocator/error/accounting contract; these helpers are outside this recovery.
struct StackServices {
    void* (*reallocate)(State*, void*, uint32_t, uint32_t);
    void* (*allocationTooLarge)(State*);
    void (*relocatePointers)(State*, void*);
};
struct State {
    uint32_t unknown00[2];
    void* top;                      // +08
    void* base;                     // +0c
    void* global;                   // +10
    void* currentFrame;             // +14
    uint32_t unknown18;
    void* stackLimit;               // +1c
    void* stack;                    // +20
    uint32_t unknown24;
    void* firstFrame;               // +28
    uint32_t stackCapacity;         // +2c, allocated slots including reserve
    uint32_t unknown30[10];
    void* openUpvalues;             // +58
    uint32_t unknown5c[3];
    // Original VA 0x4f4ef0 uses ECX=this, EDX=requestedSlots, ret 0.
    // Services are a port adapter, not a field in the original state.
    void RIFF_FAST resizeStack(uint32_t requestedSlots, const StackServices& services);
};
static_assert(sizeof(void*) == 4, "32-bit original layout");
static_assert(offsetof(State, stack)==0x20, "stack offset");
static_assert(offsetof(State, stackCapacity)==0x2c, "capacity offset");
static_assert(offsetof(State, openUpvalues)==0x58, "upvalue offset");
}
#endif
