#include "impl.hpp"
namespace riff {
// Game.exe VA 0x535C20, RVA 0x135C20, 38 bytes. Original ABI: thiscall,
// no stack arguments; only AL is a defined result. Import 0x92D470 is fclose.
// Direct disassembly agrees with accepted save_device_close.S. The primary
// elSaveDevicePC vtable at 0x9FFE2C names this routine in slot +0xC.
// No direct call sites were found; virtual dispatch determines callers.
// Constructor initializes +0xC/+0x10 to zero; read/write use +0x10 as FILE*.
bool save_device_close(SaveDevicePrefix* device, CloseStream close_stream) {
    void* stream = device->stream;
    if (stream) {
        device->state = 0;
        close_stream(stream); // Return value intentionally ignored, including EOF.
        device->stream = nullptr;
    }
    return true;
}
}
