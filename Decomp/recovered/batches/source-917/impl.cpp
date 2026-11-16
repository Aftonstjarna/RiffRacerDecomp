#include "impl.hpp"
// VA 0x541f40, 94 bytes. The caller at 0x541bc3 grows a vector-like
// [begin,end,capacity] container, passing old end and new element count.
// No allocation, container pointer update, imports, or FS access occurs here.
// This is partial default initialization, not a whole-record memset.
extern "C" void RECORD48_FASTCALL record48_default_construct_range(Record48* first, uint32_t count) {
    uintptr_t address = reinterpret_cast<uintptr_t>(first);
    while (count != 0) {
        if (address != 0) {
            Record48* record = reinterpret_cast<Record48*>(address);
            record->zeroedWords[0] = 0;
            record->zeroedWords[1] = 0;
            record->zeroedWords[2] = 0;
            record->zeroedWords[3] = 0;
            record->zeroedWords[4] = 0;
            record->zeroedWords[5] = 0;
            record->zeroedWords[6] = 0;
            record->zeroedWords[7] = 0;
            record->zeroedWords[8] = 0;
            record->zeroedWord40 = 0;
            record->zeroedByte44 = 0;
        }
        // Integer addressing retains the original null-element skip without
        // C++ null pointer arithmetic. Native ports use native pointer width.
        address += sizeof(Record48);
        --count;
    }
}
