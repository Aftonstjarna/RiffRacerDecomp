#ifndef RIFF_SCRIPT_STACK_RELOCATION_HPP
#define RIFF_SCRIPT_STACK_RELOCATION_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// Original 32-bit address space. Stack values occupy eight bytes. These are
// addresses, not host-size pointers, so the recovered data layout is explicit.
struct OpenUpvalue {
    uint32_t next;
    uint32_t unknown04;
    uint32_t value;
};
struct ScriptFrame {
    uint32_t base;
    uint32_t function;
    uint32_t top;
    uint32_t unknown0c[3];
};
struct ScriptState {
    uint32_t unknown00[2];
    uint32_t top;                 // +08
    uint32_t base;                // +0c
    uint32_t unknown10;
    uint32_t currentFrame;        // +14, inclusive last frame
    uint32_t unknown18;
    uint32_t stackLimit;          // +1c, maintained by callers
    uint32_t stack;               // +20, already replaced by callers
    uint32_t unknown24;
    uint32_t firstFrame;          // +28
    uint32_t stackCapacity;       // +2c, maintained by callers
    uint32_t unknown30[10];
    uint32_t openUpvalues;        // +58, singly linked list
    void RIFF_FASTCALL relocatePointers(uint32_t oldStack);
};
static_assert(sizeof(ScriptFrame) == 24, "frame stride");
static_assert(offsetof(ScriptState, openUpvalues) == 0x58, "state layout");
}
#endif
