#ifndef RIFF_SHADER_SLOT_SELECT_HPP
#define RIFF_SHADER_SLOT_SELECT_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Shader; // Callers invoke virtual methods; concrete type is unresolved.
// Partial 32-bit manager layout, not a recovered complete class.
struct ShaderManager {
    unsigned char unknown_0000[0xe18];
    Shader** slots;
    unsigned char unknown_0e1c[0x2862 - 0xe1c];
    unsigned char first_override;
    unsigned char second_override;
    Shader* RIFF_THISCALL select(uint32_t index) const;
};
static_assert(sizeof(void*) == 4, "Original manager ABI requires 32-bit pointers");
static_assert(offsetof(ShaderManager, slots) == 0xe18, "table offset");
static_assert(offsetof(ShaderManager, first_override) == 0x2862, "first flag offset");
static_assert(offsetof(ShaderManager, second_override) == 0x2863, "second flag offset");
}
#endif
