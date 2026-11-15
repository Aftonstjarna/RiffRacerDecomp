#include "impl.hpp"
// Game.exe VA 0x4f6040, RVA 0xf6040, 91 bytes, thiscall, no stack args.
// Caller 0x4f5b3c passes the stream through ECX and retains EAX as an int.
int RIFF_THISCALL ScriptStream::peek() {
    if (remaining == 0) {
        uint32_t count;
        const uint8_t* buffer = reader(readerContext, readerArgument, &count);
        if (!buffer || count == 0)
            return -1;
        // Original temporarily consumes then restores the first byte. Its
        // movzx makes the intervening comparison with -1 unreachable.
        // Successful refill replaces count/cursor even if reader mutated them.
        cursor = buffer;
        remaining = count;
    }
    return static_cast<int>(*cursor);
}
