#ifndef RIFF_SCRIPT_PROTOTYPE_HPP
#define RIFF_SCRIPT_PROTOTYPE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
// Only the fields read by VA 0x4f4c40 are identified. Other bytes stay opaque.
struct ScriptLocal {
    const void* name_object; // string data starts 16 bytes after this address
    int32_t start_position;
    int32_t end_position;
};
struct ScriptPrototype {
    unsigned char unknown00[0x18];
    const ScriptLocal* locals;
    unsigned char unknown1c[0x1c];
    int32_t local_count;
    const char* local_name(uint32_t ordinal, int32_t position) const;
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(sizeof(ScriptLocal) == 12, "original local stride");
static_assert(offsetof(ScriptPrototype, locals) == 0x18, "original locals field");
static_assert(offsetof(ScriptPrototype, local_count) == 0x38, "original count field");
#endif
}
#endif
