#include "impl.hpp"
namespace riff {
// Game.exe 0x486650..0x486675. Callers at 0x486770 and 0x4867c8
// extract a nine-bit RK operand from an instruction (shift 14, mask 0x1ff).
// This helper itself does not mask to nine bits, check bounds, or validate
// string addresses. Tag 4 denotes a Lua string; its bytes start at +16.
// The original fallback lives at 0x9f99d0 and contains "?\0". Relocating
// that immutable literal is necessary for a native port; identity is local.
const char* RIFF_FASTCALL constant_string_name(const LuaPrototype* prototype,
                                             uint32_t operand) {
    static const char unknown[] = "?";
    if ((operand & 0x100u) == 0) return unknown;
    const uint32_t index = operand & ~uint32_t(0x100u);
    // Preserve the original 32-bit scaled-address arithmetic, including wrap.
    const uint32_t address = prototype->constants_address + index * 8u;
    const LuaConstant* constant = reinterpret_cast<const LuaConstant*>(
        static_cast<uintptr_t>(address));
    if (constant->tag != 4u) return unknown;
    return reinterpret_cast<const char*>(static_cast<uintptr_t>(
        constant->value_address + 16u));
}
}
