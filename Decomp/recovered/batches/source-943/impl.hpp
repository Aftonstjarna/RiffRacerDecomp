#ifndef RIFF_AUDIO_STREAM_QUERY_POSITION_HPP
#define RIFF_AUDIO_STREAM_QUERY_POSITION_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#elif defined(__i386__)
#define RIFF_CDECL __attribute__((cdecl))
#else
#define RIFF_CDECL
#endif

// Partial layout: only fields accessed by VA 0x58dc90 are identified.
// Names describe arithmetic roles; original type names/position units are unknown.
struct AudioStream {
    uint8_t unknown0000[0x6d44];
    uint32_t cachedPosition;
    uint8_t unknown6d48[8];
    uint8_t flags;
    uint8_t unknown6d51[0x37];
    uint32_t bufferOffset;
    uint8_t unknown6d8c[4];
    uint32_t bufferBasePosition;
};
static_assert(offsetof(AudioStream, cachedPosition) == 0x6d44, "cache offset");
static_assert(offsetof(AudioStream, flags) == 0x6d50, "flags offset");
static_assert(offsetof(AudioStream, bufferOffset) == 0x6d88, "offset offset");
static_assert(offsetof(AudioStream, bufferBasePosition) == 0x6d90, "base offset");
static_assert(sizeof(AudioStream) == 0x6d94, "partial layout extent");
extern "C" uint32_t RIFF_CDECL audio_stream_query_position(AudioStream* stream);
#endif
