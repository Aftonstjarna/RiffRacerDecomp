#ifndef RIFF_GROW_HPP
#define RIFF_GROW_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_METHOD __thiscall
#elif defined(__i386__)
#define RIFF_METHOD __attribute__((thiscall))
#else
#define RIFF_METHOD
#endif
namespace riff {
struct State {
    uint8_t unknown00[0x14];
    uint32_t current; // +14: current 24-byte CallInfo address
    uint8_t unknown18[12];
    uint32_t last; // +24
    uint32_t records; // +28
    uint8_t unknown2c[4];
    uint32_t capacity; // +30: compared as signed, doubled modulo 2^32
    uint8_t unknown34[0x70-0x34];
    uint32_t RIFF_METHOD grow();
};
static_assert(offsetof(State,current)==0x14,"current layout");
static_assert(offsetof(State,capacity)==0x30,"capacity layout");
// Integration dependencies; implementations are outside this recovered scope.
// Original resize/status use ECX=state and EDX=count/status (custom fastcall).
void resize_callinfo(State*, uint32_t);
void throw_status(State*, uint32_t);
// Original cdecl variadic runtime error at 0x486ab0, literal at 0x9fd828.
void runtime_error(State*, const char*);
}
#endif
