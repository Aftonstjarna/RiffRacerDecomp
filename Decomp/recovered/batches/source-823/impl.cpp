#include "impl.hpp"
namespace riff {
// Evidence: Game.exe [0x485cd0,0x485d13), accepted
// Decomp/native/script_frame_current_line.S, and direct original disassembly.
// Call at 0x485fdb passes state in ECX/frame in EDX and stores EAX at
// debug-output +0x14; call at 0x4869cb uses the active frame from state +0x14.
// These establish register arguments rather than a stack thiscall parameter.
// No calls, allocation, FS registration, or other global writes occur here.
// The layout resembles a script VM; original type/member names are unresolved.

int32_t RIFF_FASTCALL script_frame_current_line(ScriptState* state, ScriptFrame* frame) {
    ScriptValue* function = frame->function;
    if (function->tag != 6 || function->closure->native_flag != 0)
        return -1;
    if (frame == state->active_frame)
        frame->saved_pc = state->current_pc;
    ScriptPrototype* prototype = function->closure->prototype;
    // The x86 subtraction wraps before SAR 2. Express the sign extension in
    // unsigned arithmetic so even wrapped or unaligned PCs have defined behavior.
    uint32_t distance = frame->saved_pc - prototype->code_address;
    uint32_t instruction = distance >> 2;
    if ((distance & 0x80000000u) != 0)
        instruction |= 0xc0000000u;
    uint32_t index = instruction - 1u;
    if ((index & 0x80000000u) != 0)
        return -1;
    if (prototype->line_table == 0)
        return 0;
    return prototype->line_table[index];
}
}
