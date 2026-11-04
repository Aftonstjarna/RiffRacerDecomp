#ifndef RECOVERED_PRESENTATION_HPP
#define RECOVERED_PRESENTATION_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RR_THISCALL __thiscall
#else
#define RR_THISCALL __attribute__((thiscall))
#endif
// Original object offsets are retained; unknown fields remain opaque.
struct DisplayMode { uint32_t width, height, other[4]; };
struct PresentationState {
    union { unsigned char storage[0x4c0]; uint32_t words[0x130]; };
    uint32_t& word(unsigned offset) { return words[offset / 4]; }
    uint32_t word(unsigned offset) const { return words[offset / 4]; }
    void RR_THISCALL updatePresentationParameters(); // VA 004a33f0, no stack arguments
    // Integration dependency: original viewport-size at 004a22e0, callee pops 8.
    // Port supplies this method; tests bind it to the accepted original helper.
    void RR_THISCALL setViewportSize(uint32_t width, uint32_t height);
};
#endif
