#include "impl.hpp"
// VA 0x58e250, 73 bytes. Original optimized ABI: ECX=this, EDX=source,
// signed count on stack, caller cleanup. Call sites 0x4f88a3, 0x55c446,
// 0x55db28 confirm this convention. The portable member models its semantics;
// it does not promise that compiler-specific optimized calling convention.
int32_t AudioStream::append_buffer(const void* source, int32_t count) {
    if (buffer.append(source, count) == 0) return 0;
    if ((flags & 0x20) == 0) {
        audio_append_diagnostic(
            "\n[..\\SDK\\mpg123\\readers.c:%i] error: Failed to add buffer, return: %i\n",
            0x301, -1);
    }
    // No rollback: the helper can have already copied part of the input.
    return -1;
}
