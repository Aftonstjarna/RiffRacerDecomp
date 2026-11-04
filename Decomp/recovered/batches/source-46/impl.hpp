#ifndef RIFF_WINDOW_FRAME_HPP
#define RIFF_WINDOW_FRAME_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define WF_STDCALL __stdcall
#define WF_THISCALL __thiscall
#else
#define WF_STDCALL __attribute__((stdcall))
#define WF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Rect { int32_t left, top, right, bottom; };
typedef int32_t (WF_STDCALL *FrameQuery)(uint32_t, uint32_t, void*, uint32_t);
struct FrameApi {
 uint32_t (WF_STDCALL *load)(const char*);
 FrameQuery (WF_STDCALL *lookup)(uint32_t, const char*);
 int32_t (WF_STDCALL *release)(uint32_t);
 int32_t (WF_STDCALL *windowRect)(uint32_t, Rect*);
};
struct Window {
 uint32_t unknown0[2];
 uint32_t secondaryWindow; // HWND at +8; used after creation at 0x48cd64.
 uint32_t unknownC[5];
 uint32_t verticalOffset; // +0x20, consumed by caller 0x48cd76.
 void WF_THISCALL frame();
 void frameWithApi(const FrameApi& api); // Native-port dependency adapter.
};
static_assert(offsetof(Window, secondaryWindow)==8, "HWND offset");
static_assert(offsetof(Window, verticalOffset)==0x20, "placement offset");
static_assert(sizeof(Window)==0x24, "bounded object prefix");
}
#endif
