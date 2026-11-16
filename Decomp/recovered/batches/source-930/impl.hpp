#ifndef RIFF_AUDIO_ADVANCE_HPP
#define RIFF_AUDIO_ADVANCE_HPP
#include <stdint.h>
#include <stddef.h>
struct AudioBufferPosition {
    uint8_t unknown[0x6d84];
    uint32_t bufferedEnd;
    uint32_t position;
    uint32_t checkpoint;
    uint32_t basePosition;
};
static_assert(offsetof(AudioBufferPosition, bufferedEnd)==0x6d84, "end offset");
static_assert(offsetof(AudioBufferPosition, position)==0x6d88, "position offset");
static_assert(offsetof(AudioBufferPosition, checkpoint)==0x6d8c, "checkpoint offset");
static_assert(offsetof(AudioBufferPosition, basePosition)==0x6d90, "base offset");
static_assert(sizeof(AudioBufferPosition)==0x6d94, "partial layout size");
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
extern "C" int32_t RIFF_CDECL audio_buffer_advance_position(AudioBufferPosition*, int32_t amount);
#endif
