#include "impl.hpp"
#include <stddef.h>
extern "C" void* memcpy(void*, const void*, size_t);
// Game.exe VA 0x58e0d0..0x58e17f. Original internal ABI: ECX=this,
// EDX=destination, stack=count, caller cleanup. A portable member expresses
// the operation; its ordinary compiler ABI is not that custom register ABI.
// Signed comparisons are intentional. Helpers retain x86 32-bit wraparound.
static int32_t add32(int32_t a, int32_t b) {
    return static_cast<int32_t>(static_cast<uint32_t>(a) + static_cast<uint32_t>(b));
}
static int32_t sub32(int32_t a, int32_t b) {
    return static_cast<int32_t>(static_cast<uint32_t>(a) - static_cast<uint32_t>(b));
}
int32_t AudioBuffer::read_range(void* destination, int32_t count) {
    AudioChunk* chunk = first;
    int32_t base = 0;
    const int32_t initial_cursor = cursor;
    if (sub32(length, initial_cursor) < count) {
        cursor = saved_cursor;
        return -10;
    }
    while (chunk) {
        int32_t end = add32(base, chunk->length);
        if (end > initial_cursor) break;
        base = end;
        chunk = chunk->next;
    }
    int32_t copied = 0;
    while (copied < count && chunk) {
        int32_t offset = sub32(cursor, base);
        int32_t amount = sub32(count, copied);
        int32_t available = sub32(chunk->length, offset);
        if (amount > available) amount = available;
        memcpy(static_cast<unsigned char*>(destination) + copied,
               chunk->data + offset, static_cast<size_t>(amount));
        copied = add32(copied, amount);
        cursor = add32(cursor, amount);
        base = add32(base, chunk->length);
        chunk = chunk->next;
    }
    return copied;
}
