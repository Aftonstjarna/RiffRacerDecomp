#ifndef AUDIO_INPUT_READ_DISPATCH_HPP
#define AUDIO_INPUT_READ_DISPATCH_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
// Original 0x58d830 is a free cdecl callback, not a thiscall member.
// Buffer/count names follow the accumulating reader at 0x58d880. The
// dispatcher treats both as opaque 32-bit arguments and performs no validation.
typedef int32_t (RIFF_CDECL *ReadCallback)(void*, void*, int32_t);
struct AudioInput {
    uint8_t unknown_0000[0x6d48];
    void* default_context;                 // +6d48
    void* alternate_context;               // +6d4c
    uint32_t flags;                        // +6d50: only low-byte bit 0x40 read
    uint8_t unknown_6d54[0x10];
    ReadCallback alternate_read;           // +6d64, nullable
    uint8_t unknown_6d68[8];
    ReadCallback default_read;             // +6d70, required on default path
};
static_assert(sizeof(void*) != 4 || offsetof(AudioInput, default_context) == 0x6d48, "layout");
static_assert(sizeof(void*) != 4 || offsetof(AudioInput, alternate_context) == 0x6d4c, "layout");
static_assert(sizeof(void*) != 4 || offsetof(AudioInput, flags) == 0x6d50, "layout");
static_assert(sizeof(void*) != 4 || offsetof(AudioInput, alternate_read) == 0x6d64, "layout");
static_assert(sizeof(void*) != 4 || offsetof(AudioInput, default_read) == 0x6d70, "layout");
// Native pointer-sized fields allow a Linux port to bind native callbacks;
// the documented byte offsets apply only to the original 32-bit ABI.
int32_t RIFF_CDECL audio_input_read_dispatch(AudioInput*, void*, int32_t);
}
#endif
