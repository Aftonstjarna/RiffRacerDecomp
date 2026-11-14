#ifndef RIFF_RANDOM_RANGE_HPP
#define RIFF_RANDOM_RANGE_HPP
#include <stdint.h>
struct RiffRandom {
    uint32_t state;
    // Original 0x478850: this in ECX, lower and upper on stack, callee pops 8.
    // Arguments/results are raw 32-bit words; signed callers use the same bits.
    uint32_t inclusive(uint32_t lower, uint32_t upper);
};
#endif
