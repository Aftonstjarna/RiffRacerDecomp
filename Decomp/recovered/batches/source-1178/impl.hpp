#ifndef SCRIPT_HOOK_DISPATCH_HPP
#define SCRIPT_HOOK_DISPATCH_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
struct HookRecord { uint32_t event; unsigned char unknown04[16]; uint32_t argument; unsigned char unknown18[72]; int32_t frameIndex; };
typedef void (*Hook)(State*, HookRecord*);
struct Frame { uint32_t unknown00[2]; void* limit; uint32_t unknown0c[3]; };
struct State {
 uint32_t unknown00[2]; void* top; void* base; void* global; Frame* currentFrame;
 uint32_t unknown18; void* stackLimit; void* stack; uint32_t unknown24;
 Frame* firstFrame; uint32_t stackCapacity; unsigned char unknown30[9]; uint8_t hookEnabled;
 unsigned char unknown3a[10]; Hook hook; unsigned char unknown48[16]; void* openUpvalues; uint32_t unknown5c[3];
 // Original ECX state, EDX event, caller-cleaned stack argument. Resize is a port binding.
 void dispatchHook(uint32_t event, uint32_t argument, void (*resize)(State*,uint32_t));
};
static_assert(sizeof(void*)==4,"requires original 32-bit layout");
static_assert(offsetof(State,hook)==0x44,"hook offset");
static_assert(offsetof(HookRecord,frameIndex)==0x60,"record offset");
}
#endif
