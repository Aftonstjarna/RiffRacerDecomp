#include "impl.hpp"
namespace recovered {
SaveDevice* active_save_device = 0;
// VA 0x535710, RVA 0x135710, 81 bytes. ECX=this, EAX=this, no stack args.
// Startup VA 0x5CFC60 allocates 0x44 bytes and calls only for nonnull storage.
// RTTI evidence identifies wsSaveDevice / elSaveDevicePC. These numeric vtable
// identities need relocation to recovered dispatch tables in a complete port;
// this bounded routine neither dereferences them nor recovers virtual methods.
SaveDevice* SAVE_THISCALL SaveDevice::initialize() {
    enabled = 1;
    secondary_vtable = 0x009ffe24; // base construction stage
    primary_vtable = 0x009ffe2c;
    secondary_vtable = 0x009ffe6c;
    unknown0c = 0;
    file_handle = 0;
    first.capacity = 7;
    first.length = 0;
    first.inline_storage[0] = 0;
    second.length = 0;
    second.capacity = 7;
    second.inline_storage[0] = 0;
    active_save_device = this;
    return this;
}
}
