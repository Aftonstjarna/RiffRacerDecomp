#include "impl.hpp"
namespace recovered {
static void clear_string(WideStringStorage& s, DeleteStorage release) {
    if (s.capacity >= 8u) {
        uintptr_t address = 0;
        for (unsigned i=0;i<4;++i) address |= uintptr_t(s.storage[i]) << (8*i);
        release(reinterpret_cast<void*>(address));
    }
    s.capacity = 7;
    s.length = 0;
    // Only the first WCHAR is cleared, including when storage held a pointer.
    s.storage[0] = 0;
    s.storage[1] = 0;
}
// VA 0x5357a0, RVA 0x1357a0, 100 bytes. Direct original disassembly
// agrees with accepted save_device_destruct.S. The only direct caller found
// is scalar-deleting wrapper 0x535770 (thiscall, stack flag, ret 4).
// No file close, null-this check, or object deallocation occurs here.
void __attribute__((thiscall)) save_device_destruct(SaveDevice* self, DeleteStorage release) {
    self->primary_vtable = 0x009ffe2c;
    self->secondary_vtable = 0x009ffe6c;
    clear_string(self->second, release);
    clear_string(self->first, release);
    self->primary_vtable = 0x009f99d8;
}
}
