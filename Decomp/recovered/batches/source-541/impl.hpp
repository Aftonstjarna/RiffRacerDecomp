#ifndef RIFF_NARROW_RECORD24_HPP
#define RIFF_NARROW_RECORD24_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
// Layout inferred from VA 0x4268c0 and array callers at 0x4264c8,
// 0x76ac34. Storage can hold a narrow string's small-buffer representation;
// this initializer does not establish the meaning of preexisting contents.
struct NarrowRecord24 {
    unsigned char storage[16];
    uint32_t length;
    uint32_t capacity;
    void default_initialize();
};
static_assert(sizeof(NarrowRecord24) == 24, "original record stride");
static_assert(offsetof(NarrowRecord24, length) == 16, "original length");
static_assert(offsetof(NarrowRecord24, capacity) == 20, "original capacity");
// Original is cdecl, not thiscall: stack arguments are address and count.
// Observed template callers also pass three unused trailing arguments.
void narrow_record24_default_initialize(NarrowRecord24* first, uint32_t count);
}
#endif
