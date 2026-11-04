#ifndef RECOVERED_SAVE_DEVICE_HPP
#define RECOVERED_SAVE_DEVICE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define SAVE_THISCALL __thiscall
#else
#define SAVE_THISCALL __attribute__((thiscall))
#endif
namespace recovered {
struct WideStringStorage {
    uint16_t inline_storage[8];
    uint32_t length;
    uint32_t capacity;
};
struct SaveDevice {
    uint32_t primary_vtable;
    uint8_t enabled;
    uint8_t untouched05[3];
    uint32_t secondary_vtable;
    uint32_t unknown0c;
    uint32_t file_handle;
    WideStringStorage first;
    WideStringStorage second;
    SaveDevice* SAVE_THISCALL initialize();
};
// Portable storage for the original active-context slot at VA 0xBFCB4C.
extern SaveDevice* active_save_device;
static_assert(sizeof(WideStringStorage) == 24, "UTF-16 small-string storage");
static_assert(offsetof(SaveDevice, first) == 0x14, "first string");
static_assert(offsetof(SaveDevice, second) == 0x2c, "second string");
static_assert(sizeof(SaveDevice) == 0x44, "startup allocation size");
}
#endif
