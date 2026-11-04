#ifndef RIFF_REQUEST_CASE2_HPP
#define RIFF_REQUEST_CASE2_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_THISCALL __thiscall
#define RR_STDCALL __stdcall
#else
#define RR_THISCALL __attribute__((thiscall))
#define RR_STDCALL __attribute__((stdcall))
#endif
namespace riff {
struct Request {
    uint32_t kind, width, height, backWidth, backHeight, unused14, samples;
    uint8_t fullscreen, flag, unused1e[2];
};
// D3DPRESENT_PARAMETERS occupies 56 bytes in the original 32-bit ABI.
struct Presentation {
    uint32_t width, height, format, backBufferCount, samples, quality;
    uint32_t swapEffect, window, windowed, autoDepth, depthFormat, flags;
    uint32_t refreshRate, interval;
};
struct Device;
typedef int32_t (RR_STDCALL *Reset)(Device*,Presentation*);
struct DeviceVtable { void* unknown[16]; Reset reset; };
struct Device { DeviceVtable* vtable; };
struct Rect { int32_t left, top, right, bottom; };
struct Window { uint32_t unknown0, handle, unknown8; int32_t savedX, savedY; };
struct Display {
    uint8_t unknown000[0x78];
    Device* device;
    uint8_t unknown07c[0x1b8-0x7c];
    Presentation presentation;
    uint8_t unknown1f0[0x23c-0x1f0];
    uint32_t width, height, backWidth, backHeight, saved274, samples;
    uint8_t unknown254[0x274-0x254];
    uint32_t source274;
    uint8_t unknown278[0x4a4-0x278];
    float scaleX, scaleY;
    uint8_t unknown4ac[0x4ba-0x4ac];
    uint8_t flag, unknown4bb[4], fullscreen;
    uint8_t unknown4c0[0xbac-0x4c0]; // caller-visible object extent; untouched here
    bool RR_THISCALL requestCase2(const Request*);
};
// Explicit unrecovered boundaries, bound to the original addresses by default.
// The singleton slots are reloaded at each call, as in Game.exe.
struct RequestBoundaries {
    Window** window;
    void** resources;
    void (RR_THISCALL *release)(Display*);
    int32_t (RR_STDCALL *getWindowRect)(uint32_t,Rect*);
    void (RR_THISCALL *setWindowMode)(Window*,uint32_t,uint32_t,uint32_t);
    void (RR_THISCALL *resizeResources)(void*,uint32_t,uint32_t);
    bool (RR_THISCALL *restore)(Display*);
    void (RR_THISCALL *viewport)(Display*,uint32_t,uint32_t);
    void (RR_THISCALL *finish)(Display*);
};
extern RequestBoundaries boundaries;
static_assert(sizeof(Request)==0x20,"request layout");
static_assert(sizeof(Presentation)==56,"presentation layout");
static_assert(offsetof(Display,presentation)==0x1b8,"presentation offset");
static_assert(offsetof(Display,width)==0x23c,"settings offset");
static_assert(offsetof(Display,source274)==0x274,"source offset");
static_assert(offsetof(Display,scaleX)==0x4a4,"ratio offset");
static_assert(offsetof(Display,flag)==0x4ba,"flag offset");
static_assert(offsetof(Display,fullscreen)==0x4bf,"mode offset");
}
#endif
