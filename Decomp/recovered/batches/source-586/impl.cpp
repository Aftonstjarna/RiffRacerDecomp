#include "impl.hpp"
namespace riff {
// Game.exe VA 0x4a4ea0, size 138. thiscall, no stack arguments.
// The source roles follow the creation calls at 0x4a4d80. Cleanup is also
// called on bind failure (0x4a4fa1) and after readback (0x4a5221).
// Release is COM stdcall vtable slot 2; its reference count return is ignored.
// Clear AFTER Release, preserving callback visibility and fresh later loads.
void RIFF_THISCALL DevicePendingTargets::cleanup() {
    if (readback_surface) {
        readback_surface->vtable->release(readback_surface);
        readback_surface = 0;
    }
    if (depth_surface) {
        depth_surface->vtable->release(depth_surface);
        depth_surface = 0;
    }
    if (color_surface[1]) {
        color_surface[1]->vtable->release(color_surface[1]);
        color_surface[1] = 0;
    }
    if (color_surface[0]) {
        color_surface[0]->vtable->release(color_surface[0]);
        color_surface[0] = 0;
    }
    if (color_texture[1]) {
        color_texture[1]->vtable->release(color_texture[1]);
        color_texture[1] = 0;
    }
    if (color_texture[0]) {
        color_texture[0]->vtable->release(color_texture[0]);
        color_texture[0] = 0;
    }
    viewport.x = viewport.y = viewport.width = viewport.height = 0;
    viewport.min_depth = viewport.max_depth = 0.0f;
}
}
