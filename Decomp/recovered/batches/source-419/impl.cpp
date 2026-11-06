#include "impl.hpp"

// Byte access permits unaligned records and avoids C++ aliasing assumptions.
// Each complete word is read before its corresponding store, as in Game.exe.
static uint32_t read_word(uintptr_t address) {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(address);
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) |
           (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
static void write_word(uintptr_t address, uint32_t value) {
    unsigned char* p = reinterpret_cast<unsigned char*>(address);
    p[0] = static_cast<unsigned char>(value);
    p[1] = static_cast<unsigned char>(value >> 8);
    p[2] = static_cast<unsigned char>(value >> 16);
    p[3] = static_cast<unsigned char>(value >> 24);
}
void* record16_range_copy(const void* begin, const void* end, void* destination) {
    uintptr_t source = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t finish = reinterpret_cast<uintptr_t>(end);
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    // Integer advances preserve the original null-output single-record case.
    // A null output on multiple records is NOT a general discard operation:
    // the next iteration attempts to write at address 16.
    while (source != finish) {
        if (output != 0) {
            write_word(output, read_word(source));
            write_word(output + 4, read_word(source + 4));
            write_word(output + 8, read_word(source + 8));
            write_word(output + 12, read_word(source + 12));
        }
        source += 16;
        output += 16;
    }
    return reinterpret_cast<void*>(output);
}
// Caller at 0x4b27c0 allocates count*16 bytes, passes container begin/end
// (+0/+4), frees the old allocation, then updates begin/end/capacity (+0/+4/+8).
// This helper itself touches only destination bytes and has no calls or FS use.
