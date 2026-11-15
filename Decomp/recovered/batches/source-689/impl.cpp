#include "impl.hpp"
// VA 0x47d840, length 102: ECX=this, one stack pointer, ret 4.
// Callers at 0x47ea12/1e serialize two adjacent embedded transforms;
// 0x47e64f also copies a transform from a strided record. No return value
// is consumed. Field meanings beyond this 64-byte representation are unknown.
// Each original dword load precedes its store; this is a forward copy,
// including for overlap, not a snapshot or memmove.
void RIFF_THISCALL Transform64::serialize_copy(void* destination) const {
    unsigned char* out = static_cast<unsigned char*>(destination);
    for (unsigned i = 0; i != 64; i += 4) {
        // Capture the whole word before writing any bytes. Byte access avoids
        // alignment and aliasing assumptions and retains arbitrary float bits.
        const unsigned char a = bytes[i];
        const unsigned char b = bytes[i+1];
        const unsigned char c = bytes[i+2];
        const unsigned char d = bytes[i+3];
        out[i] = a;
        out[i+1] = b;
        out[i+2] = c;
        out[i+3] = d;
    }
}
