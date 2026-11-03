#ifndef RIFF_SECONDARY_HPP
#define RIFF_SECONDARY_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define SW_STDCALL __stdcall
#define SW_THISCALL __thiscall
#else
#define SW_STDCALL __attribute__((stdcall))
#define SW_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Rect { uint32_t left,top,right,bottom; };
struct Window;
struct WindowApi {
 int32_t (SW_STDCALL *destroy)(uint32_t);
 int32_t (SW_STDCALL *adjust)(Rect*,uint32_t,int32_t);
 int32_t (SW_STDCALL *rect)(uint32_t,Rect*);
 uint32_t (SW_STDCALL *create)(uint32_t,const uint16_t*,const uint16_t*,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,void*);
 int32_t (SW_STDCALL *position)(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
 int32_t (SW_STDCALL *show)(uint32_t,int32_t);
 int32_t (SW_STDCALL *style)(uint32_t,int32_t,uint32_t);
 void (SW_THISCALL *frame)(Window*);
};
struct Window {
 uint32_t instance,primary,secondary;
 uint32_t unknown[4];
 uint32_t horizontalOffset,verticalOffset;
 void SW_THISCALL secondaryWindow(uint32_t width,uint32_t height,uint8_t popup);
 void secondaryWithApi(uint32_t width,uint32_t height,uint8_t popup,const WindowApi& api);
};
static_assert(offsetof(Window,horizontalOffset)==0x1c,"layout");
static_assert(sizeof(Window)==0x24,"bounded prefix");
}
#endif
