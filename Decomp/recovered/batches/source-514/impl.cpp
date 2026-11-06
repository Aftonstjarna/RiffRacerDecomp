#include "impl.hpp"

// Game.exe 0x426fd0..0x427002; ECX=this, stack source, RET 4, EAX=this.
// Four complete 16-byte reads interleaved with four complete writes. Do not
// replace with memcpy/memmove or snapshot all 64 bytes: overlap is observable.
// Call sites include 0x464944/0x464a2a (stack matrices used in float math),
// and 0x4d4dd9/0x4d4e17 (fields at object offsets 0x41c and 0x45c).
// No allocation, arithmetic on matrix values, other fields, globals or imports.
Matrix64* RIFF_THISCALL Matrix64::copy_from(const void* source) {
    const uint8_t* input = static_cast<const uint8_t*>(source);
    for (unsigned block = 0; block < 64; block += 16) {
        uint8_t snapshot[16];
        for (unsigned i = 0; i < 16; ++i)
            snapshot[i] = input[block + i];
        for (unsigned i = 0; i < 16; ++i)
            bytes[block + i] = snapshot[i];
    }
    return this;
}
