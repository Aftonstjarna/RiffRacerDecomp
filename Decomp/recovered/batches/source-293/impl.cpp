#include "impl.hpp"
namespace riff {
static uint32_t entryCount(const GraphicsEntries& table) {
    // Original subtracts 32-bit addresses, interprets the wrapped result as
    // signed, divides by 12 toward zero, then compares it as unsigned.
    const uint32_t bytes = uint32_t(uintptr_t(table.end)) - uint32_t(uintptr_t(table.begin));
    const int32_t signedBytes = bytes <= 0x7fffffffU
        ? int32_t(bytes) : -1 - int32_t(0xffffffffU - bytes);
    return uint32_t(signedBytes / 12);
}
void RIFF_THISCALL GraphicsEntries::releaseAll(uint32_t /*unused*/) {
    const uint32_t count = entryCount(*this);
    for (uint32_t index = 0; index < count; ++index) {
        if (entryCount(*this) <= index)
            graphicsEntryRangeError();
        // Re-read begin: releasing a resource can call user-controlled virtual
        // destruction and change this table. The iteration limit stays fixed.
        GraphicsEntry* entry = reinterpret_cast<GraphicsEntry*>(
            uintptr_t(begin) + uint32_t(index * 12U));
        entry->release(true);
    }
}
// No result is promised: the original leaves volatile EAX incidental.
// Callers at 0x4a09c0/0x4a0a00 pass an uninitialized stack slot and ignore EAX.
}
