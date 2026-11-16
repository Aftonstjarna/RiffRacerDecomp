#ifndef RIFF_AUDIO_MEMORY_SEEK_HPP
#define RIFF_AUDIO_MEMORY_SEEK_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#elif defined(__i386__)
#define RIFF_CDECL __attribute__((cdecl))
#else
#define RIFF_CDECL
#endif
// Partial view of the callback context, not a reconstruction of its whole class.
// The neighboring read callback uses a buffer address at +0x2c.
struct AudioMemoryState {
    uint8_t opaque[0x30];
    uint32_t length;
    uint32_t position;
};
static_assert(offsetof(AudioMemoryState, length) == 0x30, "length layout");
static_assert(offsetof(AudioMemoryState, position) == 0x34, "cursor layout");
// Return the EAX bit pattern. Some decoder callers interpret it as signed.
extern "C" uint32_t RIFF_CDECL audio_memory_seek_callback(
    AudioMemoryState* state, int32_t displacement, int32_t origin);
#endif
