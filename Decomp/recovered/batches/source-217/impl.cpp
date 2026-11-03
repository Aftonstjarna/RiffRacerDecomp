#include "impl.hpp"
namespace riff {
typedef int32_t (RR_STDCALL *GetRect)(uint32_t,Rect*);
static int32_t RR_STDCALL originalGetRect(uint32_t handle,Rect* rect) {
    return (*reinterpret_cast<GetRect*>(0x92d524u))(handle,rect);
}
RequestBoundaries boundaries = {
    reinterpret_cast<Window**>(0xbfcc28u), reinterpret_cast<void**>(0xbfcd0cu),
    reinterpret_cast<void (RR_THISCALL *)(Display*)>(0x4a6330u),
    originalGetRect,
    reinterpret_cast<void (RR_THISCALL *)(Window*,uint32_t,uint32_t,uint32_t)>(0x48cb30u),
    reinterpret_cast<void (RR_THISCALL *)(void*,uint32_t,uint32_t)>(0x53d2d0u),
    reinterpret_cast<bool (RR_THISCALL *)(Display*)>(0x4a6560u),
    reinterpret_cast<void (RR_THISCALL *)(Display*,uint32_t,uint32_t)>(0x4a22e0u),
    reinterpret_cast<void (RR_THISCALL *)(Display*)>(0x4a5b00u)
};
// Unsigned conversion in the original is signed int -> double, correction by
// 2^32, then float. Keep both rounding stages before the single precision divide.
static float unsignedFloat(uint32_t x) {
    double d=static_cast<double>(static_cast<int32_t>(x));
    d += (x >> 31) ? 4294967296.0 : 0.0;
    return static_cast<float>(d);
}
// VA 0x4a1cd0..0x4a2128 (including sample jump table), RET 4, result in AL.
// Dispatcher 0x4a1900 forwards the case-2 request with this in ECX.
// No exception recovery, additional resource cleanup, or retry is invented here.
bool RR_THISCALL Display::requestCase2(const Request* r) {
    if(r->width==width && r->height==height && r->backWidth==backWidth &&
       r->backHeight==backHeight && r->fullscreen==fullscreen && r->samples==samples) {
        flag=r->flag;
        return true;
    }
    boundaries.release(this);
    if(!fullscreen) {
        Window* w=*boundaries.window;
        Rect rect; // The API result is ignored in the original; valid output is required.
        boundaries.getWindowRect(w->handle,&rect);
        w->savedX=rect.left;
        w->savedY=rect.top;
    }
    Presentation oldPresentation=presentation;
    const uint32_t old274=source274;
    presentation.width=r->backWidth;
    presentation.height=r->backHeight;
    presentation.samples=(r->samples>=2 && r->samples<=16) ? r->samples : 0;
    presentation.quality=0;
    presentation.windowed=r->fullscreen==0 ? 1 : 0;
    presentation.refreshRate=presentation.windowed ? 0 : old274;
    if(device->vtable->reset(device,&presentation)<0) {
        const uint32_t mode=fullscreen; // loaded before restoring the parameters
        presentation=oldPresentation;
        // Uses requested dimensions and OLD mode, even though reset failed.
        boundaries.setWindowMode(*boundaries.window,r->backWidth,r->backHeight,mode);
        return false;
    }
    boundaries.resizeResources(*boundaries.resources,r->width,r->height);
    // Snapshot occurs after the resize callback, not before reset/release.
    const uint32_t oldWidth=width, oldHeight=height;
    const uint32_t oldBackWidth=backWidth, oldBackHeight=backHeight;
    const uint32_t oldSaved=saved274, oldSamples=samples;
    width=r->width; height=r->height;
    backWidth=r->backWidth; backHeight=r->backHeight;
    saved274=r->fullscreen ? old274 : source274;
    samples=r->samples; // raw setting, even when not a supported sample count
    if(!boundaries.restore(this)) {
        presentation=oldPresentation;
        device->vtable->reset(device,&presentation); // failure is ignored
        // The reset callback may modify the restored presentation parameters.
        boundaries.resizeResources(*boundaries.resources,presentation.width,presentation.height);
        width=oldWidth; height=oldHeight;
        backWidth=oldBackWidth; backHeight=oldBackHeight;
        saved274=oldSaved; samples=oldSamples;
        return false;
    }
    boundaries.setWindowMode(*boundaries.window,r->backWidth,r->backHeight,r->fullscreen);
    fullscreen=r->fullscreen;
    scaleX=unsignedFloat(width)/unsignedFloat(backWidth);
    scaleY=unsignedFloat(height)/unsignedFloat(backHeight);
    boundaries.viewport(this,backWidth,backHeight);
    flag=r->flag; // request is re-read after callbacks
    boundaries.finish(this);
    return true;
}
}
