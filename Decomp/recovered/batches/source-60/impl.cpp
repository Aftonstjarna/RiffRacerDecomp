#include "impl.hpp"
namespace riff {
// Original 0x52F4C0..0x52F55A: thiscall, no arguments, no defined return value.
// Callers: manager teardown at 0x52DA16 and setup failure at 0x52F4B0.
// Names are descriptive; the callback class and its slot-zero method name
// are unresolved (argument 1 suggests a scalar deleting destructor).
void ShaderManager::release() {
    // External accepted helper 0x52F5B0; not recovered in this bounded unit.
    // A native port must bind its equivalent here. It visits six binding
    // tables column-first and invokes slot +0x10 without clearing them.
    typedef void (RIFF_THISCALL *BindingCleanup)(ShaderManager*);
    reinterpret_cast<BindingCleanup>(static_cast<uintptr_t>(0x52f5b0))(this);
    for (unsigned i = 0; i != 280; ++i) {
        Callback* object = callbacks[i];
        if (object) object->vtable->destroy(object, 1);
        // The original reloads callbacks after the virtual call.
        callbacks[i] = 0;
    }
    for (unsigned i = 0; i != 225; ++i) {
        ShaderRecord& r = shaders[i];
        Resource* p = r.vertexConstants;
        if (p) p->vtable->release(p);
        p = r.vertexShader; // Loaded BEFORE clearing vertexConstants.
        r.vertexConstants = 0;
        if (p) p->vtable->release(p);
        r.vertexShader = 0;
        p = r.pixelConstants;
        if (p) p->vtable->release(p);
        p = r.pixelShader; // Loaded BEFORE clearing pixelConstants.
        r.pixelConstants = 0;
        if (p) p->vtable->release(p);
        r.pixelShader = 0;
    }
}
}
