#include "impl.hpp"
namespace riff {
void NarrowRecord24::default_initialize() {
    capacity = 15;
    length = 0;
    storage[0] = 0;
}
// Original Game.exe VA 0x4268c0, 45 bytes. No calls, allocation, reads
// from records, FS registration, or return-value contract. Writes occur in
// capacity/length/terminator order. Existing heap pointers are not released.
void narrow_record24_default_initialize(NarrowRecord24* first, uint32_t count) {
    uintptr_t address = reinterpret_cast<uintptr_t>(first);
    while (count != 0) {
        if (address != 0)
            reinterpret_cast<NarrowRecord24*>(address)->default_initialize();
        address += 24;
        --count;
    }
}
}
