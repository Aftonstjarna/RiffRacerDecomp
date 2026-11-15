#include "impl.hpp"
#include <stddef.h>
extern "C" void* RIFF_CDECL memcpy(void*, const void*, size_t);

// Game.exe 0x4f60a0..0x4f6139. Original internal ABI: ECX=stream,
// EDX=destination, stack=requested, caller cleans stack (NOT MS fastcall).
// Callers at 0x556001/0x55603f check nonzero as short-read failure.
// This member exposes the same semantics through a portable member ABI.
uint32_t ScriptStream::readBlock(void* destination, uint32_t requested) {
    unsigned char* output = static_cast<unsigned char*>(destination);
    uint32_t left = requested;
    // The original passes the address of its stack argument, not 'left'.
    uint32_t refillSize = requested;
    while (left != 0) {
        if (available == 0) {
            const unsigned char* block = reader(sourceContext, readerContext, &refillSize);
            if (block == 0 || refillSize == 0)
                return left;
            cursor = block;
            available = refillSize - 1;
            // The original probes a byte, temporarily advances, then ungets it.
            // movzx makes its comparison with -1 impossible, including for FF.
            (void)*static_cast<const volatile unsigned char*>(cursor);
            ++cursor;
            ++available;
            --cursor;
        }
        (void)*static_cast<const volatile unsigned char*>(cursor);
        uint32_t count = left <= available ? left : available;
        memcpy(output, cursor, count);
        available -= count;
        output += count;
        cursor += count;
        left -= count;
    }
    return 0;
}
