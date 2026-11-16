#ifndef AUDIO_FRAME_REUSE_HPP
#define AUDIO_FRAME_REUSE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(__GNUC__) && defined(__i386__)
#define AUDIO_THISCALL __attribute__((thiscall))
#else
#define AUDIO_THISCALL
#endif
namespace recovered {
// Partial decoder layout. Names describe observed use, not a recovered class identity.
struct AudioFrame {
    uint8_t opaque0[0x254c];
    uint8_t saved_bytes[0x24];
    uint32_t repeats;
    uint8_t opaque1[0x4ce8-0x2574];
    uint32_t mode;
    uint8_t opaque2[8];
    uint32_t read_prefix;
    uint8_t opaque3[0x54];
    uint32_t bit_offset;
    uint8_t* cursor;
    uint8_t opaque4[0x4da0-0x4d50-sizeof(uint8_t*)];
    uint32_t copy_size;
    uint8_t opaque5[0x6ca8-0x4da4];
    uint8_t* buffered;
    uint8_t opaque6[0x6d04-0x6ca8-sizeof(uint8_t*)];
    uint32_t flag_a;
    uint32_t flag_b;
    uint8_t opaque7[0x2c];
    uint32_t prefix;
    uint8_t opaque8[0x80];
    uint32_t frame_count;
    int AUDIO_THISCALL reuse_buffered();
    // Integration dependency: accepted audio-bitstream-read16, VA 0x58eab0.
    uint32_t AUDIO_THISCALL read16();
};
static_assert(offsetof(AudioFrame, frame_count)==0x6dbc,"decoder layout");
static_assert(offsetof(AudioFrame, cursor)==0x4d50,"cursor layout");
}
#endif
