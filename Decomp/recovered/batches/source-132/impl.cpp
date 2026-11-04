#include "impl.hpp"
namespace riff {
void* windowSystem = 0;
SecondaryWindowUpdate updateSecondaryWindow = 0;
// Original 0x4a2130..0x4a226e, thiscall, ret 4, boolean result in AL.
// Original unsigned conversion uses signed int -> double, adds 0 or 2^32,
// then rounds to float BEFORE division. Keep the intermediate rounding,
// including zero denominators and the caller's current FP rounding mode.
static float unsignedSingle(uint32_t value) {
    int32_t signedValue = value < 0x80000000u ? (int32_t)value : -1-(int32_t)~value;
    volatile double corrected = (double)signedValue + (value >> 31 ? 4294967296.0 : 0.0);
    volatile float rounded = (float)corrected;
    return rounded;
}
bool RIFF_THISCALL Display::requestCase3(const Request3* r) {
    if (r->logicalWidth != logicalWidth || r->logicalHeight != logicalHeight ||
        r->windowWidth != windowWidth || r->windowHeight != windowHeight ||
        r->mode != comparedMode || r->setting18 != setting18) {
        logicalWidth = r->logicalWidth;
        logicalHeight = r->logicalHeight;
        void* system = windowSystem;
        windowWidth = r->windowWidth;
        windowHeight = r->windowHeight;
        saved274 = source274;
        setting18 = r->setting18;
        updateSecondaryWindow(system,r->windowWidth,r->windowHeight,r->mode);
        // Reload state: a window callback can have changed the dimensions.
        float numerator = unsignedSingle(logicalWidth);
        float denominator = unsignedSingle(windowWidth);
        scaleX = numerator / denominator;
        numerator = unsignedSingle(logicalHeight);
        denominator = unsignedSingle(windowHeight);
        scaleY = numerator / denominator;
    }
    flag = r->flag;
    return true;
}
}
