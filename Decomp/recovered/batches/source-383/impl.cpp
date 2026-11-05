#include "impl.hpp"
namespace riff {
// Game.exe 0x52f560..0x52f5a3. Original x86 thiscall, no arguments,
// no defined return value. Request-dispatch case 0 calls this on [0xbfcd04].
// Six rows have 0x460-byte stride. Slot meaning and original type names
// remain unresolved; notification does not imply ownership or destruction.
void RIFF_THISCALL ShaderGrid::notifySlot12() {
    for (unsigned column = 0; column != 280; ++column) {
        for (unsigned row = 0; row != 6; ++row) {
            ShaderEntry* entry = entries[row][column];
            if (entry) entry->vtable->notifySlot12(entry);
        }
    }
}
}
