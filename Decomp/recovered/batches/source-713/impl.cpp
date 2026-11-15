#include "impl.hpp"

// Caller evidence: 0x5ccada computes EDX arithmetically; 0x5ccaeb,
// 0x5ccaf6, 0x5ccf36 and 0x5ccf41 load unsigned words into EDX.
// ECX is the stream in every observed direct caller. No stack arguments,
// allocation, capacity check or defined return value occur in this routine.
void RIFF_FASTCALL Stream::append_u16_be(uint32_t value) {
    buffer[cursor] = static_cast<uint8_t>(value >> 8);
    ++cursor;
    // Reload both fields: the preceding byte may alias the object itself.
    buffer[cursor] = static_cast<uint8_t>(value);
    ++cursor;
}
