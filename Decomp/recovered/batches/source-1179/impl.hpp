#ifndef RIFF_RETURN_HOOK_HPP
#define RIFF_RETURN_HOOK_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
struct Record { uint32_t event; uint8_t opaque04[16]; uint32_t argument; uint8_t opaque18[72]; int32_t frameIndex; };
typedef void (*Hook)(State*,Record*);
struct Frame { void* base; void* function; void* limit; uint32_t pc, results, tailCalls; };
struct State {
 uint8_t opaque00[8]; void* top; void* base; void* global; Frame* frame; uint32_t pc; void* stackLimit; void* stack; uint32_t opaque24; Frame* firstFrame; uint32_t capacity; uint8_t opaque30[8]; uint8_t hookMask, hookEnabled; uint8_t opaque3a[10]; Hook hook; uint8_t opaque48[16]; void* openUpvalues; uint32_t opaque5c[3];
 // Dependencies implement original dispatch (0x4f5020) and resize (0x4f4ef0).
 void* returnHook(void* result, void (*dispatch)(State*,uint32_t,uint32_t), void (*resize)(State*,uint32_t));
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(State,hook)==0x44,"state layout");
static_assert(offsetof(Frame,tailCalls)==0x14,"frame layout");
static_assert(offsetof(Record,frameIndex)==0x60,"record layout");
#endif
}
#endif
