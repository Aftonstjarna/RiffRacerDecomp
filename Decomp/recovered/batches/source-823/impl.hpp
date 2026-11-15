#ifndef RIFF_SCRIPT_FRAME_CURRENT_LINE_HPP
#define RIFF_SCRIPT_FRAME_CURRENT_LINE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif
namespace riff {
// Partial 32-bit interpreter layouts. Names describe observed roles, not
// recovered original declarations. Unused bytes must remain untouched.
struct ScriptPrototype {
    uint8_t unknown00[12];
    uint32_t code_address;                 // +0x0c
    uint8_t unknown10[4];
    const int32_t* line_table;             // +0x14
};
struct ScriptClosure {
    uint8_t unknown00[6];
    uint8_t native_flag;                   // +6: any nonzero rejects frame
    uint8_t unknown07[9];
    ScriptPrototype* prototype;            // +0x10
};
struct ScriptValue {
    ScriptClosure* closure;                // +0
    uint32_t tag;                          // +4: function tag is exactly 6
};
struct ScriptFrame {
    uint8_t unknown00[4];
    ScriptValue* function;                 // +4
    uint8_t unknown08[4];
    uint32_t saved_pc;                     // +0x0c: address, not dereferenced
    uint8_t unknown10[8];
};
struct ScriptState {
    uint8_t unknown00[20];
    ScriptFrame* active_frame;             // +0x14
    uint32_t current_pc;                   // +0x18
};
// Original VA 0x485cd0, 67 bytes. Two-register fastcall, no stack arguments.
// Requires valid object pointers; valid nonnegative indices require a suitably
// sized line table. The original does not check its length or PC alignment.
int32_t RIFF_FASTCALL script_frame_current_line(ScriptState* state, ScriptFrame* frame);
#if UINTPTR_MAX == UINT32_MAX
static_assert(offsetof(ScriptValue, tag) == 4, "value tag layout");
static_assert(offsetof(ScriptClosure, prototype) == 16, "closure layout");
static_assert(offsetof(ScriptPrototype, line_table) == 20, "prototype layout");
static_assert(offsetof(ScriptFrame, saved_pc) == 12, "frame layout");
static_assert(offsetof(ScriptState, current_pc) == 24, "state layout");
#endif
}
#endif
