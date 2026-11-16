#ifndef RIFF_METADATA_CLEAR_HPP
#define RIFF_METADATA_CLEAR_HPP
#include <stddef.h>
#include <stdint.h>
namespace riff {
// Partial decoder layout: names/types of the metadata payload remain unresolved.
// Original thiscall method: VA 0x58b220, RVA 0x18b220, length 148.
struct AudioDecoder {
    unsigned char unknown_prefix[0x6f70];
    unsigned char metadata_flag;
    unsigned char preserved_gap[3];
    uint32_t metadata_words[14];
    void clear_metadata();
};
static_assert(offsetof(AudioDecoder, metadata_flag) == 0x6f70, "flag offset");
static_assert(offsetof(AudioDecoder, metadata_words) == 0x6f74, "words offset");
static_assert(sizeof(AudioDecoder) == 0x6fac, "known extent only");
}
#endif
