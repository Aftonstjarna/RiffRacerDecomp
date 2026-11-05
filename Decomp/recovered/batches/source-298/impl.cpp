#include "impl.hpp"
namespace riff {
// Game.exe 0x542a40, 91 bytes. ECX=this, no arguments, no defined
// return value. Callers pass enclosing-object offsets +0x214 (0x4a0a1f)
// and +0x28 (0x540beb). The virtual calls are COM-style stdcall slot +8,
// not C++ thiscall virtual calls. Their return values are ignored.
void RIFF_THISCALL Buffer::release() {
    if (third) third->vtable->release(third);
    // Retain the original load-before-clear order, including callback
    // visibility: each pointer is still present during its own Release.
    ReleaseInterface* next = second;
    third = 0;
    if (next) next->vtable->release(next);
    next = first;
    second = 0;
    if (next) next->vtable->release(next);
    first = 0;
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    state[3] = 0;
}
}
