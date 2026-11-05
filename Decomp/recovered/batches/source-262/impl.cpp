#include "impl.hpp"
// Game.exe VA 0x44f790, RVA 0x4f790, 65 bytes; thiscall, callee pops 4.
// Caller 0x44ef1a passes a stack UTF-16 buffer and destination in ECX.
// The wrapper reads no destination fields: all mutation, allocation and alias
// handling belong to assign_range. It forwards that method's return value.
// Null or unterminated source is invalid; no validation or Unicode decoding.
WideString* RIFF_THISCALL WideString::assign_pointer(const uint16_t* source) {
    const uint16_t* end = source;
    while (*end != 0) {
        ++end;
    }
    return assign_range(source, static_cast<uint32_t>(end - source));
}
