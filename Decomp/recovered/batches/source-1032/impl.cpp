#include "impl.hpp"
namespace riff {
// Game.exe VA 0x58e7a0, RVA 0x18e7a0, 51 bytes; cdecl, three stack words.
// The two indirect callees are cdecl too (caller removes all eight words).
// Original .rdata 0x9eea50..0x9eea8f contains sixteen pointers here. No
// direct call site was found in original disassembly; indirect users and
// concrete input/result types remain unresolved. No object writes occur here.
uint32_t RIFF_CDECL audio_stereo_callback_bridge(uint32_t first_input,
                                                uint32_t second_input,
                                                Decoder* decoder) {
    const uint32_t first = decoder->selected_callback(first_input, 0, decoder, 0);
    // Intentionally reload: the first callback may change the selected callback.
    const uint32_t second = decoder->selected_callback(second_input, 1, decoder, 1);
    return first + second;
}
}
