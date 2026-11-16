#ifndef RIFF_AUDIO_EXACT_HPP
#define RIFF_AUDIO_EXACT_HPP
#include <stdint.h>
struct AudioChunk {
    unsigned char* data;
    int32_t length;
    int32_t capacity;
    AudioChunk* next;
};
struct AudioBuffer {
    AudioChunk* first;
    AudioChunk* last;
    int32_t length;
    int32_t cursor;
    int32_t saved_cursor;
    uint32_t unknown[5];
    // Reference dependency at 0x58e0d0. Portable member interface;
    // original optimized ABI is ECX=this, EDX=destination, stack=count,
    // caller cleanup. A port must supply this dependency.
    int32_t read_range(void* destination, int32_t count);
};
struct BufferedAudioStream {
    unsigned char unknown_prefix[0x6d7c];
    AudioBuffer buffer;
};
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
extern "C" int32_t RIFF_CDECL audio_buffered_read_exact_callback(
    BufferedAudioStream* stream, void* destination, int32_t count);
#endif
