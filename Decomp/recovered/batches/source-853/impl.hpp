#ifndef RIFF_STACK_PUSH_HPP
#define RIFF_STACK_PUSH_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
struct PushServices {
    void* (*intern)(State*,const char*,uint32_t);
    void (*resize)(State*,uint32_t);
};
struct Slot { uint32_t payload; uint32_t tag; };
struct State {
    uint32_t unknown00[2];
    Slot* top;                     // +08
    void* base;                    // +0c
    void* global;                  // +10
    void* currentFrame;            // +14
    uint32_t unknown18;
    void* stackLimit;              // +1c, usable end before reserve
    void* stack;                   // +20
    uint32_t unknown24;
    void* firstFrame;              // +28
    uint32_t stackCapacity;        // +2c, includes reserve after resize
    uint32_t unknown30[10];
    void* openUpvalues;            // +58
    uint32_t unknown5c[3];
    // Original 0x4efab0: ECX=this, EDX=text, plain ret (95 bytes).
    // Services are explicit port bindings, never original object fields.
    void pushTerminated(const char* text,const PushServices& services);
};
static_assert(sizeof(void*)==4,"original VM requires 32-bit pointers");
static_assert(offsetof(State,top)==8,"top offset");
static_assert(offsetof(State,stackCapacity)==0x2c,"capacity offset");
}
#endif
