#include "impl.hpp"
namespace riff {
// Game.exe 0x47c270..0x47c2ad, thiscall, callee pops one argument.
// Shared through many shape vtables (e.g. entries at 0x9fb0ec and 0x9fb15c).
// No direct callers found in the original disassembly. This recovers only the
// dispatch protocol, not the implementations of the four virtual dependencies.
void RIFF_THISCALL Shape::serializeSingle(Serializer* serializer) {
    const int32_t size = vtable->serializedSize(this);
    Chunk* chunk = serializer->vtable->allocate(serializer, size, 1);
    const char* type = vtable->serialize(this, chunk->data, serializer);
    serializer->vtable->finalize(serializer, chunk, type, 0x50414853u, this);
}
// No null/error checks are present in the original. The chunk must be valid;
// its data and the returned type pointer are forwarded without validation.
// The final call's EAX is incidental; no semantic return value is established.
}
