#include "impl.hpp"

SaveDeviceImports save_device_imports = { 0, 0 };

// Game.exe 0x535c50..0x535cb3, no explicit arguments, ECX=this, EAX=result.
// Vtable 0x9ffe2c slot +0x10 names this routine. No direct call sites were
// found in the original disassembly; indirect caller identities are unresolved.
// Adjacent open/close methods store/clear file at +0x10 and mode at +0x0c.
// This method itself writes no object fields. The rest of the object remains
// opaque: the layout above does not claim recovered class or base-class names.
int32_t RIFF_THISCALL SaveDevice::size()
{
    if (!file)
        return 0;

    // Original caches the ftell IAT entry once, but reloads the handle and
    // fseek IAT entry for each call. Keep those distinctions for adapters.
    SaveTell tell = save_device_imports.tell;
    const int32_t position = tell(file);
    if (save_device_imports.seek(file, 0, 2) != 0)
        return 0;
    const int32_t end = tell(file);
    if (save_device_imports.seek(file, position, 0) != 0)
        return 0;
    return end;
}
