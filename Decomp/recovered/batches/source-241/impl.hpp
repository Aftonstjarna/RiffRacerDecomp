#ifndef RIFF_SAVE_DEVICE_SIZE_HPP
#define RIFF_SAVE_DEVICE_SIZE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#define RIFF_THISCALL __thiscall
#else
#define RIFF_CDECL __attribute__((cdecl))
#define RIFF_THISCALL __attribute__((thiscall))
#endif

// Win32 CRT long and int are both 32 bits. The opaque handle is FILE*,
// deliberately not interpreted here. A port supplies compatible CRT adapters.
typedef int32_t (RIFF_CDECL *SaveSeek)(void*, int32_t, int32_t);
typedef int32_t (RIFF_CDECL *SaveTell)(void*);
struct SaveDeviceImports { SaveSeek seek; SaveTell tell; };
extern SaveDeviceImports save_device_imports;

struct SaveDevice {
    uint32_t opaque_prefix[4];
    void* file;                         // original this+0x10 (i386)
    unsigned char opaque_tail[0x30];    // observed object through +0x43
    int32_t RIFF_THISCALL size();
};
#if defined(_M_IX86) || defined(__i386__)
static_assert(offsetof(SaveDevice, file) == 0x10, "original file offset");
static_assert(sizeof(SaveDevice) == 0x44, "observed object extent");
#endif
#endif
