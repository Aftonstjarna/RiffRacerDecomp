#include "impl.hpp"
namespace riff {
// Direct original disassembly 0x4a5530..0x4a56bd. Callers at 0x4a385d and
// 0x4a6623 test AL. The latter is the checked device-restoration sequence.
// D3D9 CreateTexture (slot 23): one level, RENDERTARGET usage, format from +0x1fc,
// DEFAULT pool, no shared handle. No preclear, Release, or failure rollback.
// Native SEH registration/cookie machinery is not a portable exception model;
// these routines model ordinary returns only. Helper exceptions remain external.
bool Graphics::createEffectTargetUsing(const ErrorServices& e) {
    if (!effectEnabled) return true;
    int32_t status = reinterpret_cast<CreateTexture>(device->vtable[0x5c/4])(
        device, width, height, 1, 1, effectFormat, 0, &effectTexture, 0);
    if (status < 0) {
        NarrowString description, formatted;
        NarrowString* text = e.describe(&description, status);
        NarrowString* result = e.prefix(&formatted, e.texturePrefix, text);
        FreeString release = *e.freeSlot;
        if (&lastError != result) {
            if (lastError.capacity >= 16) release(lastError.storage.heap);
            lastError.capacity = 15;
            lastError.length = 0;
            lastError.storage.small[0] = 0;
            e.move(&lastError, result);
        }
        if (formatted.capacity >= 16) release(formatted.storage.heap);
        formatted.capacity = 15;
        formatted.length = 0;
        formatted.storage.small[0] = 0;
        if (description.capacity >= 16) release(description.storage.heap);
        return false;
    }
    Interface* texture = effectTexture; // reload output even if call did not write
    status = reinterpret_cast<GetSurface>(texture->vtable[0x48/4])(
        texture, 0, &effectSurface);
    if (status >= 0) return true;
    NarrowString description, formatted;
    NarrowString* text = e.describe(&description, status);
    NarrowString* result = e.prefix(&formatted, e.surfacePrefix, text);
    e.moveAssign(&lastError, result);
    FreeString release = *e.freeSlot; // original loads this after move assignment
    if (formatted.capacity >= 16) release(formatted.storage.heap);
    formatted.capacity = 15;
    formatted.length = 0;
    formatted.storage.small[0] = 0;
    if (description.capacity >= 16) release(description.storage.heap);
    return false;
}
bool RR_THISCALL Graphics::createEffectTarget() {
    const ErrorServices e = {
        reinterpret_cast<DescribeError>(0x44f380u),
        reinterpret_cast<PrefixError>(0x4b2d20u),
        reinterpret_cast<MoveString>(0x416fa0u),
        reinterpret_cast<MoveAssignString>(0x440a20u),
        reinterpret_cast<FreeString volatile*>(0x92d4b0u),
        reinterpret_cast<const char*>(0x9fc5f4u),
        reinterpret_cast<const char*>(0x9fc740u)
    };
    return createEffectTargetUsing(e);
}
}
