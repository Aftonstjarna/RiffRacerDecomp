#ifndef RIFF_AUDIO_RESAMPLE_OUTPUT_COUNT_HPP
#define RIFF_AUDIO_RESAMPLE_OUTPUT_COUNT_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif

// Partial state layout only: unknown bytes belong to the enclosing audio object.
// VA 0x5909e0: ECX=this, EDX=signed input count, EAX=signed output count.
struct AudioResampleState {
    unsigned char unknown_0000[0x4ba0];
    int32_t step_q15;
    unsigned char unknown_4ba4[0x4cec - 0x4ba4];
    int32_t chunk_input_limit;

    int32_t RIFF_FASTCALL output_count(int32_t input_count) const;
};
static_assert(offsetof(AudioResampleState, step_q15) == 0x4ba0, "step offset");
static_assert(offsetof(AudioResampleState, chunk_input_limit) == 0x4cec, "chunk offset");
static_assert(sizeof(AudioResampleState) == 0x4cf0, "partial layout size");
#endif
