#include "impl.hpp"
#include <stddef.h>
static_assert(sizeof(NarrowString) == 24, "original i386 string layout");
static_assert(offsetof(GraphicsDevice, texture_caps) == 0xbc, "caps layout");
static_assert(offsetof(GraphicsDevice, vertex_shader_version) == 0x144, "version layout");
static_assert(offsetof(GraphicsDevice, simultaneous_render_targets) == 0x170, "MRT layout");
// VA 0x4a59e0..0x4a5af9. ECX=this; one callee-cleaned pointer argument;
// AL is the boolean result. Caller 0x4a3126 supplies a local byte and tests AL.
// Comparisons are unsigned encoded D3D shader versions, not signed integers.
// A weak vertex shader is only reported to the caller; it does not reject here.
// The output store precedes every subsequent capability read (aliasing matters).
bool RIFF_THISCALL GraphicsDevice::minimum_caps(unsigned char* warning) {
    *warning = vertex_shader_version < 0xfffe0300u ? 1 : 0;
    const char* reason;
    uint32_t count;
    if (pixel_shader_version < 0xffff0300u) {
        reason = "Pixel Shader v3.0 is required.";
        count = 30;
    } else if ((texture_caps & 2u) != 0 && (texture_caps & 0x100u) == 0) {
        reason = "NP2 texture support is required.";
        count = 32;
    } else if ((texture_caps & 0x20u) != 0) {
        reason = "Non-square texture support is required.";
        count = 39;
    } else if (max_texture_width < 4096u || max_texture_height < 4096u) {
        reason = "4096x4096 textures required";
        count = 27;
    } else if (simultaneous_render_targets < 3u) {
        // This branch uses the NUL-scanning wrappers in the original.
        diagnostic.assign_terminated("Graphics card does not meet minimum system requirements.\n\n");
        diagnostic.append_terminated("At least 3 simultaneous render targers are required.");
        return false;
    } else {
        return true; // Existing diagnostic is deliberately retained.
    }
    diagnostic.assign_range("Graphics card does not meet minimum system requirements.\n\n", 58);
    diagnostic.append_range(reason, count);
    return false;
}
