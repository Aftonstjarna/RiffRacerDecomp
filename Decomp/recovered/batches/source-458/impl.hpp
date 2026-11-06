#ifndef RIFF_TEXTURE_CACHE_HPP
#define RIFF_TEXTURE_CACHE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#endif
namespace riff {
struct TextureDevice;
typedef int32_t (RIFF_STDCALL *SetTexture)(TextureDevice*, uint32_t, void*);
struct TextureDeviceVtable {
    SetTexture slots[66]; // Only slot 65 (byte offset 0x104 on i386) is used.
};
struct TextureDevice { TextureDeviceVtable* vtable; };
struct Device {
    uint8_t unknown_000[0x78];
    TextureDevice* device;
    uint8_t unknown_07c[0x9ec - 0x7c];
    uint32_t texture_cache[16]; // Opaque 32-bit cached values; never dereferenced.
    // Original 0x4add20: ECX=this, one unused stack DWORD, callee pops 4.
    // The original return register is unspecified; no result is consumed here.
    void clear_texture_cache(uint32_t unused);
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(Device, device) == 0x78, "device offset");
static_assert(offsetof(Device, texture_cache) == 0x9ec, "cache offset");
#endif
}
#endif
