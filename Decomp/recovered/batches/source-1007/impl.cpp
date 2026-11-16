#include "impl.hpp"
namespace riff {
// Evidence: original Game.exe and accepted audio_decoder_metadata_clear.S.
// Call sites 0x589f74 and 0x58a757 pass the decoder in ECX. At the latter,
// collection cleanup at 0x58b3c0 precedes this reset; this method itself does
// not release memory, follow pointers, call callbacks, or return a value.
// Valid writable object storage is required; null/short storage is not handled.
void AudioDecoder::clear_metadata() {
    metadata_flag = 0;
    metadata_words[0] = 0;
    metadata_words[1] = 0;
    metadata_words[2] = 0;
    metadata_words[3] = 0;
    metadata_words[4] = 0;
    metadata_words[5] = 0;
    // Retain the observed order of the paired stores without inferring types.
    metadata_words[7] = 0;
    metadata_words[6] = 0;
    metadata_words[9] = 0;
    metadata_words[8] = 0;
    metadata_words[11] = 0;
    metadata_words[10] = 0;
    metadata_words[13] = 0;
    metadata_words[12] = 0;
}
}
