#include "impl.hpp"
namespace recovered {
CloseHandleImport close_handle = 0;
DeleteImport delete_storage = 0;
// Game.exe VA 0x48DB80, 44 bytes; base vtable 0x9FBE20 slot 0.
// Slot 1 is start, slot 2 is the worker entry. No join or handle reset.
// This explicit method models the deleting-destructor ABI without imposing a
// host compiler's vtable layout. Only the observed 16-byte base is named.
Worker* WORKER_THISCALL Worker::scalar_delete(uint32_t flags) {
    const uint32_t saved_handle = handle;
    vtable_address = 0x009fbe20u;
    close_handle(saved_handle);
    if (flags & 1u)
        delete_storage(this);
    return this; // Pointer value only; storage may have been released.
}
}
