#include "impl.hpp"
namespace riff {
static const uint16_t windowClass[]={'O','c','t','a','n','e','5','W','i','n','d','o','w','C','l','a','s','s',0};
static const uint16_t title[]={'S','e','c','o','n','d',' ','s','c','r','e','e','n',' ','l','o','l',0};
// 0x48CC70, thiscall, callee pops 12 bytes. Caller 0x4A21C8 supplies
// dimensions and a zero-extended settings byte. No meaningful return value.
void Window::secondaryWithApi(uint32_t width,uint32_t height,uint8_t popup,const WindowApi& api) {
 if ((!width || !height) && secondary) {
  api.destroy(secondary); // Failure is ignored, including on destruction.
  secondary=0;
  return;
 }
 const uint32_t style=popup?0x80000000u:0x00c00000u;
 Rect adjusted={0,0,width,height};
 api.adjust(&adjusted,style,0);
 const uint32_t outerWidth=adjusted.right-adjusted.left;
 const uint32_t outerHeight=adjusted.bottom-adjusted.top;
 if (!secondary) {
  Rect parent; // Original ignores failure; unwritten RECT fields are unresolved.
  api.rect(primary,&parent);
  // All arithmetic wraps at 32 bits. Signed division truncates toward zero,
  // matching CDQ/SUB/SAR even when the subtraction overflows signed range.
  const uint32_t gap=parent.right-parent.left-outerWidth;
  const int64_t signedGap=gap<0x80000000u?int64_t(gap):int64_t(gap)-4294967296LL;
  horizontalOffset=uint32_t(signedGap/2);
  verticalOffset=parent.bottom-parent.top;
  secondary=api.create(0,windowClass,title,style,
      horizontalOffset+parent.left,verticalOffset+parent.top,
      outerWidth,outerHeight,0,0,instance,this);
  if (!secondary) return;
  api.frame(this); // 0x48CAB0; may change offsets/handle before they are reloaded.
  api.position(secondary,0xfffffffeu,horizontalOffset+parent.left,
      verticalOffset+parent.top,0,0,5);
  api.show(secondary,5);
 } else {
  api.style(secondary,-16,style);
  api.position(secondary,0xfffffffeu,popup?0:0x80000000u,
      popup?0:0x80000000u,adjusted.right-adjusted.left,
      adjusted.bottom-adjusted.top,popup?0x62:0x60);
 }
}
void SW_THISCALL Window::secondaryWindow(uint32_t w,uint32_t h,uint8_t popup) {
 WindowApi api;
 api.destroy=*reinterpret_cast<decltype(api.destroy)*>(0x92d530);
 api.adjust=*reinterpret_cast<decltype(api.adjust)*>(0x92d580);
 api.rect=*reinterpret_cast<decltype(api.rect)*>(0x92d524);
 api.create=*reinterpret_cast<decltype(api.create)*>(0x92d578);
 api.position=*reinterpret_cast<decltype(api.position)*>(0x92d56c);
 api.show=*reinterpret_cast<decltype(api.show)*>(0x92d574);
 api.style=*reinterpret_cast<decltype(api.style)*>(0x92d5ac);
 api.frame=reinterpret_cast<decltype(api.frame)>(0x48cab0);
 secondaryWithApi(w,h,popup,api);
}
}
