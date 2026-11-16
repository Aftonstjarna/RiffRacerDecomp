#ifndef RIFF_AUDIO_INPUT_READ_LOOP_HPP
#define RIFF_AUDIO_INPUT_READ_LOOP_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
struct AudioInput;
typedef int32_t (RIFF_CDECL *InputRead)(AudioInput*, void*, int32_t);
struct AudioInput {
    uint8_t unknown_0000[0x6d44];
    uint32_t position;                     // +6d44, modulo-2^32 accounting
    uint8_t unknown_6d48[8];
    uint32_t flags;                        // +6d50, bit 0x08 suppresses accounting
    uint8_t unknown_6d54[4];
    InputRead read;                        // +6d58, required for positive counts
    uint8_t unknown_6d5c[0x90];             // opaque surrounding storage for tests
};
static_assert(offsetof(AudioInput, position) == 0x6d44, "position offset");
static_assert(offsetof(AudioInput, flags) == 0x6d50, "flags offset");
static_assert(offsetof(AudioInput, read) == 0x6d58, "read offset");
// Free cdecl function, not a thiscall method. Nonpositive count needs no state.
int32_t RIFF_CDECL audio_input_read_loop(AudioInput*, void*, int32_t);
}
#endif
