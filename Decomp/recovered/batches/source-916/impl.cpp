#include "impl.hpp"
namespace riff {
// Game.exe VA 0x55d1c0, 66 bytes; ECX=this, no stack arguments.
// Caller 0x55d210 passes its subobject at +0x6cd8 for format 0x5080,
// or after signed-word rebiasing for 0x6000. Format names remain unknown.
// Requires a valid writable, non-object-overlapping buffer. There are no
// bounds, null, allocation or capacity checks. A size below four only sets
// size to zero (even if data is null). No return value is consumed by callers.
void ByteBuffer::packHighThreeBytes() {
    uint32_t readOffset = 0;
    uint32_t writeOffset = 0;
    // Preserve unsigned 32-bit addition/comparison, including wraparound.
    // Unrealistically large sizes near UINT32_MAX do not have a safe general
    // buffer interpretation: the original's next-group check can wrap.
    while (uint32_t(readOffset + 4u) <= size) {
        data[writeOffset] = data[readOffset + 1u];
        data[writeOffset + 1u] = data[readOffset + 2u];
        data[writeOffset + 2u] = data[readOffset + 3u];
        readOffset += 4u;
        writeOffset += 3u;
    }
    size = writeOffset;
}
}
