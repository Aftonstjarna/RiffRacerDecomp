#include "impl.hpp"
namespace riff {
// Interpret wrapped x86 arithmetic without C++ signed-overflow undefined behavior.
static int32_t signed_bits(uint32_t x) {
    return x <= 0x7fffffffu ? static_cast<int32_t>(x)
                          : -1 - static_cast<int32_t>(~x);
}
// Original VA 0x58d880, 83 bytes. Setup at 0x58e668 installs this
// function in +6d78 and sets flag 8. Setup at 0x58e5d9 installs the
// separate dispatcher (0x58d830) in +6d58. No direct calls were found;
// consumers of the installed callback are outside this bounded recovery.
int32_t RIFF_CDECL audio_input_read_loop(AudioInput* input, void* buffer, int32_t count) {
    uint32_t total = 0;
    while (signed_bits(total) < count && count > 0) {
        // Integer address addition also models the original's unchecked offset;
        // an oversized callback result is neither clamped nor rejected.
        void* destination = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(buffer) + total);
        int32_t got = input->read(input, destination,
                                 signed_bits(static_cast<uint32_t>(count) - total));
        if (got < 0) return -1;
        if (got == 0) break;
        // Read flags after the callback, and reload read on the next iteration.
        if (!(input->flags & 8u)) input->position += static_cast<uint32_t>(got);
        total += static_cast<uint32_t>(got);
    }
    return signed_bits(total);
}
}
