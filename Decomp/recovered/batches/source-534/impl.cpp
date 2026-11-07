#include "impl.hpp"

// Direct original disassembly: Game.exe [0x41db10,0x41db33).
// Call sites: 0x41d755, 0x43c8c5, 0x49c1c5, 0x49c345, 0x49c5c5,
// 0x573885. They pass the old end and number of added 12-byte elements.
// No allocation, imports, FS registration, or return value is involved.
void RIFF_FASTCALL record12_default_initialize(Record12* destination, uint32_t count)
{
    // Integer address advancement preserves the original null skip without
    // undefined C++ arithmetic on a null pointer. On i386 it also wraps at 32 bits.
    uintptr_t address = reinterpret_cast<uintptr_t>(destination);
    while (count != 0) {
        if (address != 0) {
            Record12* record = reinterpret_cast<Record12*>(address);
            record->field0 = 0;
            record->field4 = UINT32_C(0xffffffff);
            record->field8 = 0;
        }
        address += sizeof(Record12);
        --count;
    }
}
