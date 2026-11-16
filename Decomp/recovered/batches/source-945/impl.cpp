#include "impl.hpp"
// Game.exe VA 0x58a120, RVA 0x18a120, 56 bytes including skipped padding.
// Direct disassembly agrees with accepted audio_unity_arrays_initialize.S.
// Caller 0x589ec0 retains this in EBX and passes it unchanged at 0x589f6d.
// No arguments, allocation, imports, FS access, or floating-point arithmetic.
// Requires a valid writable object; the original does not check null pointers.
void RIFF_THISCALL AudioUnityArrays::initialize() {
    word2448 = 0;
    unsigned i = 0;
    do {
        // Preserve the observed second-array-before-first-array store order.
        second[i] = 1.0f;
        first[i] = 1.0f;
        ++i;
    } while (i != 32);
}
