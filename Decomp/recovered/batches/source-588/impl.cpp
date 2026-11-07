#include "impl.hpp"
namespace riff {
// Direct caller at 004a1100 tests AL; on false it binds fallback targets
// from +428/+430. This method does not restore those bindings itself.
// All helpers and COM objects must be valid; no original null checks exist.
bool RIFF_THISCALL Device::bind_pending() {
    if (!pending) return false;
    pending = 0;
    if (!prepare_pending()) return false;
    typedef int32_t (RIFF_STDCALL *SetColor)(Object*,uint32_t,Object*);
    typedef int32_t (RIFF_STDCALL *SetDepth)(Object*,Object*);
    typedef int32_t (RIFF_STDCALL *SetViewport)(Object*,Viewport*);
    // No index validation in the original; valid modes normally select 0 or 1.
    Object* color = resources[2 + (mode ? color_index : 0)];
    if (reinterpret_cast<SetColor>(graphics->vtable[0x94/4])(graphics,0,color) < 0)
        goto failed;
    if (reinterpret_cast<SetDepth>(graphics->vtable[0x9c/4])(graphics,resources[4]) < 0)
        goto failed;
    if (reinterpret_cast<SetViewport>(graphics->vtable[0xbc/4])(graphics,&viewport) < 0)
        goto failed;
    bound_mode = mode;
    bound = 1;
    return true;
failed:
    cleanup_pending();
    return false;
}
}
