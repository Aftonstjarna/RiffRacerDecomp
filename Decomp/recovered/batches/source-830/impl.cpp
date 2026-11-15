#include "impl.hpp"
namespace riff {
namespace {
uint32_t relocate(uint32_t address, uint32_t oldStack, uint32_t newStack) {
    // Original SUB / SAR 3 / scaled LEA. Dropping the low three bits gives
    // exactly the same modulo-2^32 result, without signed overflow or a
    // compiler-dependent signed right shift. Even unaligned inputs round down.
    return newStack + ((address - oldStack) & ~uint32_t(7));
}
template<class T> T* at(uint32_t address) {
    return reinterpret_cast<T*>(static_cast<uintptr_t>(address));
}
}
// Game.exe VA 004f4e60..004f4eee, accepted script-stack-relocate-pointers.
// ECX=this, EDX=oldStack, no stack arguments, no result. A fastcall member
// models this internal register ABI (ordinary thiscall would put oldStack on
// the stack). No allocation, copying of stack values, imports or FS access.
// Observed call sites: 004efc28, 004efe54, 004f16df, 004f4f43, 004f5480,
// 004f5c27. Each installs stack at +20 and updates +1c/+2c beforehand.
void RIFF_FASTCALL ScriptState::relocatePointers(uint32_t oldStack) {
    top = relocate(top, oldStack, stack);
    uint32_t node = openUpvalues;
    while (node != 0) {
        OpenUpvalue* upvalue = at<OpenUpvalue>(node);
        upvalue->value = relocate(upvalue->value, oldStack, stack);
        node = upvalue->next;
    }
    uint32_t frameAddress = firstFrame;
    while (frameAddress <= currentFrame) {
        ScriptFrame* frame = at<ScriptFrame>(frameAddress);
        frame->top = relocate(frame->top, oldStack, stack);
        frame->base = relocate(frame->base, oldStack, stack);
        frame->function = relocate(frame->function, oldStack, stack);
        frameAddress += 24;
    }
    base = relocate(base, oldStack, stack);
}
}
