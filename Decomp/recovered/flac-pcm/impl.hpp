#pragma once
namespace riff { namespace recovered {
// Algorithm slice of Game.exe's FLAC wrapper, not the complete decoder ABI.
// Input is the wrapper's interleaved signed-16-bit PCM scratch block (<=4096
// bytes in the original call). Keep channel zero; do not average the channels.
// Caller supplies valid, nonoverlapping input/output with sufficient capacity.
unsigned flac_channel_zero(const short* input, unsigned bytes, float* output);
} }
