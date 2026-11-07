#include "impl.hpp"

// Evidence: original Game.exe [0x437ed0,0x437ef3), corroborated by accepted
// record12_zero_initialize.S. Direct calls at 0x4378ef, 0x50d18c, 0x5193d3
// pass the old array end and added element count in ECX/EDX. At 0x437880
// the caller computes element counts by dividing byte differences by 12,
// ensures capacity, initializes the added records, then advances its end.
// No calls, allocation, imports, global writes, or FS registration occur here.
void RIFF_FASTCALL record12_zero_initialize(Record12* destination, uint32_t count)
{
    // Use integer advancement: null skips this iteration only, and must not
    // invoke undefined C++ null-pointer arithmetic. On i386 addresses wrap
    // modulo 2^32 as in the original; native ports use their pointer width.
    uintptr_t address = reinterpret_cast<uintptr_t>(destination);
    while (count != 0) {
        if (address != 0) {
            Record12* record = reinterpret_cast<Record12*>(address);
            record->field0 = 0;
            record->field4 = 0;
            record->field8 = 0;
        }
        address += sizeof(Record12);
        --count;
    }
}
