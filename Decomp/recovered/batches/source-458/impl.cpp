#include "impl.hpp"
namespace riff {
// Direct original disassembly: 0x4add20..0x4add59. The caller at
// 0x4a6363 (device release) supplies an unused DWORD before taking its lock.
// No Release calls, error checks, null-device guard, or cache-wide preclear.
void Device::clear_texture_cache(uint32_t /*unused*/) {
    for (uint32_t stage = 0; stage < 16; ++stage) {
        if (texture_cache[stage] != 0) {
            TextureDevice* current = device;
            current->vtable->slots[65](current, stage, 0);
        }
        texture_cache[stage] = 0;
    }
}
}
