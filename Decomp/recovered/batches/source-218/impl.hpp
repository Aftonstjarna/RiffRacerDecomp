#ifndef RIFF_DEVICE_DEFAULTS_HPP
#define RIFF_DEVICE_DEFAULTS_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
// Partial, DWORD-addressed view of the device owner, not its complete class.
// Field semantics are unresolved. Offset names intentionally avoid assigning
// unproven Direct3D render-state names. No pointers or virtual calls are used.
struct DeviceState {
    uint32_t words[0xa74 / 4];
    void RIFF_THISCALL resetDefaults();
private:
    uint32_t& at(unsigned byteOffset) { return words[byteOffset / 4]; }
};
static_assert(sizeof(DeviceState) == 0xa74, "partial device layout");
}
#endif
