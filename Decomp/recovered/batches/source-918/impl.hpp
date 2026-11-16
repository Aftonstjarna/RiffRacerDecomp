#ifndef RIFF_BLOCK64_IMPL_HPP
#define RIFF_BLOCK64_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Unnamed 64-byte subobject. Direct callers at 0x41e443 and 0x41e8c1
// supply enclosing-object + 0x28. No evidence identifies individual words.
struct Block64 {
    uint32_t words[16];
    Block64* RIFF_THISCALL zero_initialize();
};
static_assert(sizeof(Block64) == 64, "Original storage extent");
}
#endif
