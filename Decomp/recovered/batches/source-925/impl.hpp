#ifndef RECOVERED_AUDIO_BITSTREAM_HPP
#define RECOVERED_AUDIO_BITSTREAM_HPP
#include <stdint.h>
#include <stddef.h>
namespace recovered {
// Only this bounded routine's fields are identified; the prefix is opaque.
struct AudioBitstream {
    uint8_t opaque[0x4d4c];
    uint32_t bit_offset;
    const uint8_t* cursor;
    uint32_t read16();
};
static_assert(offsetof(AudioBitstream, bit_offset) == 0x4d4c, "bit offset layout");
static_assert(offsetof(AudioBitstream, cursor) == 0x4d50, "cursor layout");
}
#endif
