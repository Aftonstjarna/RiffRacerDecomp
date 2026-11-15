#ifndef RIFF_SCRIPT_THROW_STATUS_HPP
#define RIFF_SCRIPT_THROW_STATUS_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#define RIFF_CDECL __cdecl
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
struct ScriptState;
// The return value of the panic callback is ignored by this routine.
typedef int (RIFF_CDECL *PanicHandler)(ScriptState*);
struct ScriptGlobal {
    uint8_t unknown00[0x58];
    PanicHandler panic;
};
struct ScriptJump {
    ScriptJump* previous;
    uint8_t crtJumpBuffer[0x40];
    int32_t status;
};
struct ScriptState {
    uint8_t unknown00[6];
    uint8_t status;
    uint8_t unknown07[9];
    ScriptGlobal* global;
    uint8_t unknown14[0x4c];
    ScriptJump* errorJump;
};
static_assert(sizeof(void*) == 4, "Original script layout requires 32-bit pointers");
static_assert(offsetof(ScriptState, status) == 6, "status layout");
static_assert(offsetof(ScriptState, global) == 0x10, "global layout");
static_assert(offsetof(ScriptState, errorJump) == 0x60, "jump layout");
static_assert(offsetof(ScriptGlobal, panic) == 0x58, "panic layout");
static_assert(offsetof(ScriptJump, status) == 0x44, "jump status layout");
// Original VA 0x4f4d80, size 69. This is a free fastcall function, not
// thiscall: callers supply both ECX=state and EDX=status, with no stack args.
void RIFF_FASTCALL scriptThrowStatus(ScriptState* state, int32_t status);
}
#endif
