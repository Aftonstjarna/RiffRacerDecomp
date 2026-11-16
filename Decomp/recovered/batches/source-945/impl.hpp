#ifndef RIFF_AUDIO_UNITY_ARRAYS_HPP
#define RIFF_AUDIO_UNITY_ARRAYS_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Partial layout of the enclosing audio object, not its complete size.
// Field meanings are unresolved; offsets and float representations are observed.
struct AudioUnityArrays {
    unsigned char preceding[0x2448];
    uint32_t word2448;
    float first[32];
    float second[32];
    void RIFF_THISCALL initialize();
};
static_assert(offsetof(AudioUnityArrays, word2448) == 0x2448, "word offset");
static_assert(offsetof(AudioUnityArrays, first) == 0x244c, "first offset");
static_assert(offsetof(AudioUnityArrays, second) == 0x24cc, "second offset");
static_assert(sizeof(AudioUnityArrays) == 0x254c, "partial layout size");
#endif
