#include "impl.hpp"

// Game.exe VA 0x546100, RVA 0x146100, 42 bytes. ECX=this, no stack
// arguments, plain ret. EAX happens to contain 0xfff0; no semantic return
// value is consumed by the observed caller at 0x546374.
// That caller sets weights[0] to 1.0f after reset; an inlined reset at
// 0x5462c2 performs the same stores. No calls, allocation, or FS access.
void RIFF_THISCALL SimplexResult::reset() {
    status = 0;
    weights[0] = 0.0f;
    weights[1] = 0.0f;
    weights[2] = 0.0f;
    weights[3] = 0.0f;
    flags &= static_cast<uint16_t>(0xfff0u);
}
