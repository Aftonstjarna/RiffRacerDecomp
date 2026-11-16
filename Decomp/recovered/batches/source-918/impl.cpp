#include "impl.hpp"
namespace riff {
// Game.exe 0x41e770..0x41e7e2: ECX points at writable storage;
// sixteen ascending DWORD stores, EAX returns ECX, no stack arguments.
// Explicit stores preserve the observed extent and order without assigning
// speculative matrix/physics meanings to the fields. No allocation or imports.
Block64* RIFF_THISCALL Block64::zero_initialize() {
    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    words[7] = 0;
    words[8] = 0;
    words[9] = 0;
    words[10] = 0;
    words[11] = 0;
    words[12] = 0;
    words[13] = 0;
    words[14] = 0;
    words[15] = 0;
    return this;
}
}
