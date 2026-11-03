#include "impl.hpp"
namespace riff {
// VA 0x48cab0, 123 bytes. Only +0x20 is written by the routine itself.
void Window::frameWithApi(const FrameApi& api) {
 const uint32_t module = api.load("dwmapi.dll");
 if (!module) return;
 FrameQuery query = api.lookup(module, "DwmGetWindowAttribute");
 if (query) {
  Rect window, frameBounds;
  // The original does not initialize either RECT or check GetWindowRect's
  // BOOL. If an API fails without writing a subsequently read top, behavior
  // depends on uninitialized stack contents; no substitute is invented here.
  api.windowRect(secondaryWindow, &window);
  const int32_t status = query(secondaryWindow, 9, &frameBounds, 16);
  if (status >= 0) {
   const uint32_t delta = uint32_t(window.top) - uint32_t(frameBounds.top);
   // TEST/JLE interprets the wrapped subtraction as signed, avoiding C++ UB.
   if (delta != 0 && delta < 0x80000000u) verticalOffset += delta;
  }
 }
 api.release(module);
}
void WF_THISCALL Window::frame() {
 FrameApi api;
 api.load = *reinterpret_cast<uint32_t (WF_STDCALL **)(const char*)>(0x92d0dc);
 api.lookup = *reinterpret_cast<FrameQuery (WF_STDCALL **)(uint32_t,const char*)>(0x92d0e0);
 api.release = *reinterpret_cast<int32_t (WF_STDCALL **)(uint32_t)>(0x92d0e4);
 api.windowRect = *reinterpret_cast<int32_t (WF_STDCALL **)(uint32_t,Rect*)>(0x92d524);
 frameWithApi(api);
}
}
