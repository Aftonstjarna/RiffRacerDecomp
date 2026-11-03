#include "impl.hpp"
// VA 004a33f0..004a362e. Only the first two words of each 24-byte
// mode record participate; the remaining record fields are unresolved.
// Called by graphics-startup (004a072a) and device-create (004a3778),
// after viewport initialization. 4bf is the fullscreen flag; 4b8 belongs
// to the viewport helper. 1b8/1bc are D3D presentation backbuffer dimensions.
void RR_THISCALL PresentationState::updatePresentationParameters() {
    const DisplayMode* modes = reinterpret_cast<const DisplayMode*>(static_cast<uintptr_t>(word(0x27c)));
    // Original subtracts 32-bit addresses, then performs signed /24, truncating
    // toward zero. Valid vector storage and nonnegative length are required.
    uint32_t count = static_cast<uint32_t>(static_cast<int32_t>(word(0x280)-word(0x27c))/24);
    if (storage[0x4bf]) {
        uint32_t upperW=0xffffffffu, upperH=0xffffffffu;
        uint32_t lowerW=0, lowerH=0;
        bool exact=false;
        for (uint32_t i=0; i<count; ++i) {
            uint32_t w=modes[i].width, h=modes[i].height;
            if (w==word(0x48c) && h==word(0x490)) { exact=true; break; }
            if (w>=word(0x48c) && h>=word(0x490)) {
                if (w<=upperW && h<=upperH) { upperW=w; upperH=h; }
            } else if (w>=lowerW && h>=lowerH) { lowerW=w; lowerH=h; }
        }
        if (!exact) {
            word(0x48c)=upperW!=0xffffffffu ? upperW : lowerW;
            word(0x490)=upperW!=0xffffffffu ? upperH : lowerH;
        }
        setViewportSize(word(0x48c),word(0x490));
    } else {
        uint32_t maxW=0,maxH=0;
        for (uint32_t i=0; i<count; ++i) {
            if (modes[i].width>=maxW) {
                maxW=modes[i].width;
                if (modes[i].height>=maxH) maxH=modes[i].height;
            }
        }
        if (word(0x48c)>maxW || word(0x490)>maxH) setViewportSize(maxW,maxH);
    }
    word(0x24c)=word(0x274);
    word(0x1c8)=word(0x200);
    const uint32_t w=word(0x48c), h=word(0x490);
    word(0x23c)=w; word(0x240)=h;
    word(0x244)=w; word(0x248)=h;
    word(0x1b8)=w; word(0x1bc)=h;
    word(0x1d8)=storage[0x4bf]==0;
    word(0x1e8)=0;
}
