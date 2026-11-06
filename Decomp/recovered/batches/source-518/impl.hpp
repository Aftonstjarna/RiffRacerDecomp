#ifndef RIFF_UNSIGNED64_LOGICAL_SHIFT_RIGHT_HPP
#define RIFF_UNSIGNED64_LOGICAL_SHIFT_RIGHT_HPP
#include <stdint.h>
namespace riff {
// Recovered from Game.exe VA 0x8fc380, RVA 0x4fc380 (31 bytes).
// Portable value API for the original EDX:EAX / CL register helper.
uint64_t unsigned64_logical_shift_right(uint64_t value, uint8_t count);
}
#endif
