#ifndef RIFF_MINIMUM_CAPS_HPP
#define RIFF_MINIMUM_CAPS_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length, capacity;
    // Existing engine bindings; allocation and error handling are outside this slice.
    NarrowString* RIFF_THISCALL assign_range(const char*, uint32_t); // 0x416520
    NarrowString* RIFF_THISCALL append_range(const char*, uint32_t); // 0x442170
    NarrowString* RIFF_THISCALL assign_terminated(const char*); // 0x415b90
    NarrowString* RIFF_THISCALL append_terminated(const char*); // 0x441f70
};
// Original 32-bit object prefix only. Offsets are evidenced by 0x4a59e0.
struct GraphicsDevice {
    unsigned char unknown00[0x54];
    NarrowString diagnostic;                 // +0x54
    unsigned char unknown6c[0x50];
    uint32_t texture_caps;                    // +0xbc (D3DCAPS9.TextureCaps)
    unsigned char unknownc0[0x18];
    uint32_t max_texture_width;               // +0xd8
    uint32_t max_texture_height;              // +0xdc
    unsigned char unknowne0[0x64];
    uint32_t vertex_shader_version;           // +0x144
    uint32_t max_vertex_shader_constants;     // +0x148, untouched
    uint32_t pixel_shader_version;            // +0x14c
    unsigned char unknown150[0x20];
    uint32_t simultaneous_render_targets;     // +0x170
    bool RIFF_THISCALL minimum_caps(unsigned char* vertex_shader_warning);
};
#endif
