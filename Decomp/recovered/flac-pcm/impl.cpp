#include "impl.hpp"
namespace riff { namespace recovered {
unsigned flac_channel_zero(const short* input, unsigned bytes, float* output) {
    static_assert(sizeof(short) == 2 && sizeof(float) == 4, "original PCM widths");
    // Original VA 0x4f91cd shifts returned byte count right once. Loop at
    // 0x4f91f0..0x4f9212 sign-extends every second short, converts to binary32,
    // and multiplies by the binary32 constant at 0xa06428 (0x38000000).
    const unsigned words = bytes >> 1;
    unsigned produced = 0;
    for (unsigned i = 0; i < words; i += 2)
        output[produced++] = static_cast<float>(input[i]) * (1.0f / 32768.0f);
    return produced;
}
} }
