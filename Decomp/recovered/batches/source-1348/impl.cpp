#include "impl.hpp"

// Game.exe 0x422650: thiscall, returns this in EAX. The original first
// clears all twelve words, then writes the final identity and zero values.
Matrix3Identity* Matrix3Identity::initialize_identity() {
    for (int i = 0; i < 12; ++i)
        values[i] = 0.0f;
    values[0] = 1.0f;
    values[4] = 1.0f;
    values[8] = 1.0f;
    return this;
}
