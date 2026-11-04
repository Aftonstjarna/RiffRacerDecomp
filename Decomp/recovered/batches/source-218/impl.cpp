#include "impl.hpp"
namespace riff {
// Original: Game.exe 0x004a5e80..0x004a632a, ECX=this, no arguments.
// Both direct callers (0x4a3a10, 0x4a6673) ignore the incidental EAX value.
// No failure path, allocation, external call, or floating-point operation.
// Only the listed fields change; in particular this is not a whole-object clear.
void RIFF_THISCALL DeviceState::resetDefaults() {
    const uint32_t allBits = 0xffffffffu;
    const uint32_t floatOne = 0x3f800000u; // IEEE-754 1.0f, stored as bits
    const uint32_t float64 = 0x42800000u;  // IEEE-754 64.0f
    at(0x4f8) = 0u;
    at(0x4fc) = 3u;
    at(0x500) = 2u;
    at(0x514) = 1u;
    at(0x518) = 0u;
    at(0x51c) = 1u;
    at(0x528) = 2u;
    at(0x52c) = 1u;
    at(0x534) = 3u;
    at(0x538) = 4u;
    at(0x53c) = 0u;
    at(0x540) = 8u;
    at(0x544) = 0u;
    at(0x548) = 0u;
    at(0x54c) = 0u;
    at(0x550) = 0u;
    at(0x564) = 0u;
    at(0x568) = 0u;
    at(0x56c) = 0u;
    at(0x59c) = 0u;
    at(0x5ac) = 0u;
    at(0x5b0) = 1u;
    at(0x5b4) = 1u;
    at(0x5b8) = 1u;
    at(0x5bc) = 8u;
    at(0x5c0) = 0u;
    at(0x5c4) = allBits;
    at(0x5c8) = allBits;
    at(0x5cc) = allBits;
    at(0x570) = floatOne;
    at(0x574) = floatOne;
    at(0x6dc) = 0u;
    at(0x6e0) = 0u;
    at(0x6e4) = 0u;
    at(0x6e8) = 0u;
    at(0x6ec) = 0u;
    at(0x6f0) = 0u;
    at(0x6f4) = 0u;
    at(0x6f8) = 0u;
    at(0x744) = float64;
    at(0x748) = floatOne;
    at(0x754) = floatOne;
    at(0x758) = 0u;
    at(0x75c) = 0u;
    at(0x774) = float64;
    at(0x6fc) = 1u;
    at(0x700) = 1u;
    at(0x708) = 0u;
    at(0x70c) = 0u;
    at(0x710) = 1u;
    at(0x714) = 1u;
    at(0x718) = 0u;
    at(0x720) = 1u;
    at(0x724) = 2u;
    at(0x728) = 0u;
    at(0x72c) = 0u;
    at(0x738) = 0u;
    at(0x73c) = 0u;
    at(0x74c) = 0u;
    at(0x750) = 0u;
    at(0x760) = 1u;
    at(0x764) = allBits;
    at(0x768) = 0u;
    at(0x770) = 0u;
    at(0x778) = 0u;
    at(0x77c) = 15u;
    at(0x784) = 0u;
    at(0x7a4) = floatOne;
    at(0x7a8) = floatOne;
    at(0x7ac) = 0u;
    at(0x7b0) = 0u;
    at(0x7b4) = floatOne;
    at(0x788) = 1u;
    at(0x78c) = 3u;
    at(0x790) = 1u;
    at(0x794) = 0u;
    at(0x798) = 0u;
    at(0x79c) = 0u;
    at(0x7bc) = 0u;
    at(0x7c0) = 0u;
    at(0x7c4) = 1u;
    at(0x7c8) = 1u;
    at(0x7cc) = 1u;
    at(0x7d0) = 8u;
    at(0x7d4) = 15u;
    at(0x7d8) = 15u;
    at(0x7dc) = 15u;
    at(0x7e0) = allBits;
    at(0x7e4) = 0u;
    at(0x7f4) = 0u;
    at(0x7f8) = 0u;
    at(0x7fc) = 0u;
    at(0x800) = 0u;
    at(0x804) = 0u;
    at(0x7b8) = 0u;
    at(0x7e8) = 0u;
    at(0x808) = 0u;
    at(0x80c) = 0u;
    at(0x810) = 0u;
    at(0x814) = 0u;
    at(0x818) = 2u;
    at(0x81c) = 1u;
    at(0x820) = 1u;

    // Eight parallel state arrays; the two gaps at 0x9a4 and 0xa2c
    // (and the surrounding unlisted fields) are intentionally untouched.
    for (unsigned i = 0; i != 16; ++i) {
        const unsigned offset = 4 * i;
        at(0x824 + offset) = 1;
        at(0x864 + offset) = 1;
        at(0x8a4 + offset) = 0;
        at(0x8e4 + offset) = 1;
        at(0x924 + offset) = 1;
        at(0x964 + offset) = 1;
        at(0x9ac + offset) = 0;
        at(0x9ec + offset) = 0;
    }
    at(0xa68) = 0;
    at(0xa64) = allBits;
    at(0xa6c) = 0;
    at(0xa70) = 0;
}
}
