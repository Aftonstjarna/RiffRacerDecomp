#include "impl.hpp"
// Game.exe 0x4f1b50: thiscall, no arguments. Services represent the
// original external helpers and are not fields in the original object.
void ScriptState::shrinkBuffers(const ScriptServices& services) {
    ScriptGlobal* g = global;
    int32_t count = g->bucketCount;
    // Signed division truncates toward zero, then the comparison is unsigned.
    if (g->used < static_cast<uint32_t>(count / 4) && count > 64)
        services.resizeBuckets(this, count / 2);
    uint32_t size = g->bufferSize;
    if (size > 64) {
        uint32_t newSize = size / 2;
        // The original tests newSize + 1 > 0xfffffffd, but this cannot
        // hold for a 32-bit size shifted right by one.
        void* result = services.reallocate(this, g->buffer, size, newSize);
        g->bufferSize = newSize;
        g->buffer = result;
    }
}
