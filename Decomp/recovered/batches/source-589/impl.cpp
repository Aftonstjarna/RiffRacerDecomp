#include "impl.hpp"
namespace riff {
// Original 004a4d80..004a4e9d. Caller 004a4f30 consumes AL and binds
// the surfaces only on success. D3D9-style COM entries use stdcall.
// Inputs/COM pointers are assumed valid. Existing resources are overwritten,
// not released first; failed calls may have written output pointers.
bool RIFF_THISCALL Device::prepare_pending() {
    const uint32_t width = requested_width < 8192u ? requested_width : 8192u;
    const uint32_t height = (width * 9u) >> 4;
    typedef int32_t (RIFF_STDCALL *Texture)(Object*,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,Object**,void*);
    typedef int32_t (RIFF_STDCALL *Surface)(Object*,uint32_t,Object**);
    typedef int32_t (RIFF_STDCALL *Depth)(Object*,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,Object**,void*);
    typedef int32_t (RIFF_STDCALL *Readback)(Object*,uint32_t,uint32_t,uint32_t,uint32_t,Object**,void*);
    if (reinterpret_cast<Texture>(graphics->vtable[0x5c/4])(graphics,width,height,1,1,color_format,0,&resources[0],0)<0) goto failed;
    // Read mode again at each original branch: callbacks may change it.
    if (mode && reinterpret_cast<Texture>(graphics->vtable[0x5c/4])(graphics,width,height,1,1,color_format,0,&resources[1],0)<0) goto failed;
    if (reinterpret_cast<Surface>(resources[0]->vtable[0x48/4])(resources[0],0,&resources[2])<0) goto failed;
    if (mode && reinterpret_cast<Surface>(resources[1]->vtable[0x48/4])(resources[1],0,&resources[3])<0) goto failed;
    if (reinterpret_cast<Depth>(graphics->vtable[0x74/4])(graphics,width,height,depth_format,0,0,1,&resources[4],0)<0) goto failed;
    if (reinterpret_cast<Readback>(graphics->vtable[0x90/4])(graphics,width,height,color_format,2,&resources[5],0)<0) goto failed;
    viewport.x=0; viewport.y=0; viewport.width=width; viewport.height=height;
    viewport.minimum=0.0f; viewport.maximum=1.0f;
    return true;
failed:
    cleanup_pending();
    return false;
}
}
