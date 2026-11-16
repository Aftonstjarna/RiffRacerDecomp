#ifndef RIFF_AUDIO_STREAM_COMMIT_POSITION_HPP
#define RIFF_AUDIO_STREAM_COMMIT_POSITION_HPP
#include <stdint.h>
#include <stddef.h>

#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#define RIFF_THISCALL __thiscall
#else
#define RIFF_CDECL __attribute__((cdecl))
#define RIFF_THISCALL __attribute__((thiscall))
#endif

namespace riff {
// Partial 32-bit original layouts, not complete recovered game classes.
struct AudioBlock {
    void* data;
    uint32_t size;
    uint32_t unknown08;
    AudioBlock* next;
};
struct AudioBuffer {
    AudioBlock* head;          // +00
    AudioBlock* tail;          // +04
    uint32_t bufferedBytes;    // +08
    uint32_t position;         // +0c (signed comparisons in dependency)
    uint32_t checkpoint;       // +10
    uint32_t committedBase;    // +14
    uint32_t unknown18;
    uint32_t recycleLimit;     // +1c
    uint32_t recycledCount;    // +20
    AudioBlock* recycled;      // +24

    // Dependency at VA 0x58e180, accepted audio-buffer-commit-consumed.
    // Supply the independently recovered helper when integrating the port.
    // This bounded recovery does not provide a replacement for that routine.
    void RIFF_THISCALL commitConsumed();
};
struct AudioStream {
    unsigned char unknown0000[0x6d44];
    uint32_t committedPosition;
    unsigned char unknown6d48[0x34];
    AudioBuffer buffer;        // +6d7c
};
static_assert(sizeof(void*) == 4, "Original layout requires a 32-bit target");
static_assert(sizeof(AudioBlock) == 16, "block layout");
static_assert(sizeof(AudioBuffer) == 0x28, "buffer layout");
static_assert(offsetof(AudioStream, committedPosition) == 0x6d44, "position layout");
static_assert(offsetof(AudioStream, buffer) == 0x6d7c, "buffer layout");
static_assert(offsetof(AudioBuffer, position) == 0xc, "offset layout");
static_assert(offsetof(AudioBuffer, committedBase) == 0x14, "base layout");
}

// Original VA 0x58e3d0, RVA 0x18e3d0, length 39. Stack argument, caller cleanup.
extern "C" uint32_t RIFF_CDECL audio_stream_commit_position(riff::AudioStream* stream);
#endif
