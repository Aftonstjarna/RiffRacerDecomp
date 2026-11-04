#pragma once
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_STDCALL __stdcall
#define RR_THISCALL __thiscall
#else
#define RR_STDCALL __attribute__((stdcall))
#define RR_THISCALL __attribute__((thiscall))
#endif
struct Resource;
typedef uint32_t (RR_STDCALL *ReleaseMethod)(Resource*);
struct ResourceVtable { void* queryInterface; void* addRef; ReleaseMethod release; };
struct Resource { ResourceVtable* vtable; };
// Partial 32-bit graphics owner layout. Offset names avoid guessing resource types.
struct Device {
    unsigned char unknown000[0x70];
    Resource *resource070, *resource074, *resource078, *resource07c;
    unsigned char unknown080[0x204-0x80];
    Resource* resource204;
    unsigned char unknown208[0x214-0x208];
    Resource *resource214, *resource218, *resource21c;
    uint32_t state220[4];
    unsigned char unknown230[0x28c-0x230];
    Resource *resource28c, *resource290;
    unsigned char unknown294[4];
    Resource* resources298[33];
    unsigned char unknown31c[0x420-0x31c];
    Resource* resources420[4];
    Resource *resource430, *resource434, *resource438, *resource43c;
    Resource *resource440, *resource444, *resource448;
    unsigned char unknown44c[0x470-0x44c];
    Resource* queries470[2][3];
    void RR_THISCALL destroy();
private:
    void RR_THISCALL releaseQueries(); // dependency 0x4a4d20 only
};
static_assert(sizeof(void*)==4, "original i386 layout required");
static_assert(offsetof(Device, resource204)==0x204, "layout");
static_assert(offsetof(Device, resources298)==0x298, "layout");
static_assert(offsetof(Device, resources420)==0x420, "layout");
static_assert(offsetof(Device, queries470)==0x470, "layout");
static_assert(sizeof(Device)==0x488, "partial owner extent");
