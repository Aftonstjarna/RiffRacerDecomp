#include "impl.hpp"
// Game.exe VA 0x5908d0, RVA 0x1908d0, 63 bytes. ECX=this, EDX=count,
// EAX=result; no stack arguments. A fastcall member models these registers.
// Callers at 0x55c0d7, 0x55c345, 0x55c620, 0x58b009 and 0x590879
// store the returned phase at +0x4b98/+0x4b9c; this method does not.
int32_t RIFF_FASTCALL AudioResampleState::phaseAtCount(int32_t count) const {
    int32_t phase = 0x4000;
    if (count > 0) {
        const uint32_t increment = phaseFactor * phaseScale;
        do {
            // x86 wraps the addition before signed, truncation-toward-zero
            // remainder. Unsigned magnitude avoids signed overflow and avoids
            // implementation-defined conversion of out-of-range uint32_t.
            const uint32_t sum = static_cast<uint32_t>(phase) + increment;
            if (sum & 0x80000000u)
                phase = -static_cast<int32_t>((0u - sum) % 0x8000u);
            else
                phase = static_cast<int32_t>(sum % 0x8000u);
        } while (--count != 0);
    }
    return phase;
}
