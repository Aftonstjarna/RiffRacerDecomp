#include "impl.hpp"
namespace riff {
// Evidence: Game.exe 0x4f4ef0..0x4f4f4f and accepted script_stack_resize.S.
// Callers at 0x485f44 and 0x4f50ac grow by doubling or adding needed slots.
// Unsigned arithmetic deliberately preserves the machine's wraparound guard,
// including unusual requests near UINT32_MAX; do not replace with size_t math.
void RIFF_FAST State::resizeStack(uint32_t requestedSlots, const StackServices& services) {
    const uint32_t allocatedSlots = requestedSlots + 6u;
    void* const oldStack = stack;
    void* replacement;
    if (allocatedSlots + 1u > 0x1fffffffu)
        replacement = services.allocationTooLarge(this);
    else
        replacement = services.reallocate(this, oldStack, stackCapacity * 8u,
                                          allocatedSlots * 8u);
    // Even a returning error helper flows through these stores in the original.
    stack = replacement;
    stackCapacity = allocatedSlots;
    stackLimit = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(replacement)
                                         + requestedSlots * 8u);
    services.relocatePointers(this, oldStack);
}
}
