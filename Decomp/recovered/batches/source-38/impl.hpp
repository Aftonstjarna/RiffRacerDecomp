#pragma once
#include <stdint.h>
#include <stddef.h>
namespace recovered {
using DeleteStorage = void (*)(void*); // Original imported operator delete is cdecl.
struct WideStringStorage {
    unsigned char storage[16]; // Inline UTF-16[8], or a 32-bit heap pointer.
    uint32_t length;
    uint32_t capacity;
};
struct SaveDevice {
    uint32_t primary_vtable;
    uint32_t unknown04;
    uint32_t secondary_vtable;
    unsigned char unknown0c[8];
    WideStringStorage first;
    WideStringStorage second;
};
static_assert(sizeof(WideStringStorage)==24, "original string layout");
static_assert(offsetof(SaveDevice,first)==0x14 && offsetof(SaveDevice,second)==0x2c, "original offsets");
static_assert(sizeof(SaveDevice)==0x44, "observed object prefix");
// Ordinary destructor, not the scalar-deleting wrapper: object itself is not freed.
// Dependency is explicit for native ports; original import slot is 0x92d4b0.
void __attribute__((thiscall)) save_device_destruct(SaveDevice*, DeleteStorage);
}
