#include "impl.hpp"

// Interpret a wrapped x86 word without out-of-range unsigned-to-signed casts.
static int32_t signed_word(uint32_t bits) {
    if (bits <= 0x7fffffffu) return static_cast<int32_t>(bits);
    return -1 - static_cast<int32_t>(~bits);
}

// Original Game.exe [0x5909e0,0x590a51), accepted reference
// audio-resample-output-count. No calls, globals, floating point or state stores.
// Callers 0x58ace1, 0x58ad32, 0x58ad8a select this for mode 3;
// modes 0..2 instead arithmetic-shift their counts by the mode value.
// Adjacent setup stores 0x8000 at +0x4ba0; +0x4cec has observed
// setup values 0x480 and 0x180. Names describe usage, not recovered type names.
int32_t RIFF_FASTCALL AudioResampleState::output_count(int32_t input_count) const {
    const int32_t limit = chunk_input_limit; // Read even on nonpositive input.
    if (input_count <= 0) return 0;
    const uint32_t step = static_cast<uint32_t>(step_q15);
    uint32_t phase = 0x4000u; // Half of one Q15 output unit, local to each call.
    uint32_t total = 0;
    do {
        const int32_t chunk = input_count > limit ? limit : input_count;
        input_count = signed_word(static_cast<uint32_t>(input_count) -
                                  static_cast<uint32_t>(chunk));
        // IMUL and ADD retain low 32 bits, including on unusual field values.
        phase += step * static_cast<uint32_t>(chunk);
        const int32_t emitted = signed_word(phase) / 32768; // Truncate toward zero.
        total += static_cast<uint32_t>(emitted);
        phase -= static_cast<uint32_t>(emitted) * 32768u;
    } while (input_count > 0);
    // Do not replace with one multiply: per-chunk wrapping changes the result.
    // limit==0 with positive input never terminates, as in the original.
    return signed_word(total);
}
