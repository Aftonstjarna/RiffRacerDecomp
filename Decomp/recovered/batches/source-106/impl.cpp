#include "impl.hpp"
namespace riff {
FitDimensions fitDimensions = 0;
WindowOffsets* window = 0;
// Original 0x4A22E0..0x4A23B4, thiscall, two stack arguments, ret 8.
// Callers include graphics startup/device reset and application-frame fit
// toggling (0x4A0BAE), which reuses +48C/+490 after changing +4B8.
// Signed division applies to the height's *bit pattern*, even though dimensions
// are otherwise unsigned. Avoid implementation-defined unsigned-to-signed cast.
static int32_t signedHeight(uint32_t h) {
    return h <= 0x7fffffffu ? static_cast<int32_t>(h)
                          : -1-static_cast<int32_t>(~h);
}
void Viewport::setSize(uint32_t requestedW, uint32_t requestedH) {
    const bool fitting = fitEnabled != 0;
    requestedWidth = requestedW;
    requestedHeight = requestedH;
    if (!fitting) {
        offsetX = offsetY = 0;
        width = requestedW;
        height = requestedH;
        heightTenthMinusTwo = signedHeight(requestedH)/10 - 2;
        return;
    }
    uint32_t fittedW = requestedW, fittedH = requestedH;
    fitDimensions(&fittedW, &fittedH);
    width = fittedW;
    height = fittedH;
    // Read singleton after the dependency call, as in the original.
    WindowOffsets* const destination = window;
    offsetY = (requestedH-fittedH) >> 1;
    heightTenthMinusTwo = signedHeight(fittedH)/10 - 2;
    offsetX = (requestedW-fittedW) >> 1;
    destination->x = offsetX;
    destination->y = offsetY;
    // No null checks or clamping in the original. Subtraction wraps modulo
    // 2^32; offsets use logical shifts, including when fitted size grows.
}
}
