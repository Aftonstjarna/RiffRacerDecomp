#include "impl.hpp"
namespace riff {
// Game.exe VA 0x5301b0, RVA 0x1301b0, 69 bytes. ECX=this,
// one stack argument, callee pops 4 bytes, pointer result in EAX.
// Direct callers include 0x5418f3 (slot 0x65 then virtual call +0x28),
// 0x518943..0x518983 (slots 0x59,0x5b,0x5c,0x5d,0x5a), and
// 0x518df1 (zero-extended byte index). No calls, writes, or checks here.
Shader* RIFF_THISCALL ShaderManager::select(uint32_t index) const {
    if (first_override != 0)
        return slots[228];
    if (second_override != 0)
        return slots[229];
    // x86 scales modulo 2^32. Integer address calculation also preserves
    // wrapped indices without imposing C++ array-index overflow semantics.
    const uint32_t offset = index * uint32_t(4);
    const uintptr_t address = reinterpret_cast<uintptr_t>(slots) + offset;
    return *reinterpret_cast<Shader* const*>(address);
}
}
