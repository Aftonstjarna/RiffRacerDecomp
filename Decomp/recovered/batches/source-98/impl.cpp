#include "impl.hpp"
// Game.exe 0x536250..0x53631d. ECX=this; RET 16; EAX=this.
// path_compose (0x536220) supplies prefix as stack slot two and then
// move-constructs its result from the modified suffix. Other slots are ignored.
WideString* RIFF_THIS WideString::prepend(uint32_t, const WideString* prefix,
                                        uint32_t, uint32_t) {
    const uint32_t count = prefix->length; // min(length, UINT32_MAX) is identity
    // This check precedes even the empty-prefix return. Strict unsigned >
    // is required: a total of UINT32_MAX is rejected, not just wraparound.
    if (UINT32_MAX - length <= count)
        wide_length_error("string too long");
    if (count != 0) {
        const uint32_t total = length + count;
        if (reserve(total, false)) {
            // Re-read storage and length after reserve: it may reallocate.
            wide_move(data() + count, data(), length);
            if (this == prefix)
                wide_move(data(), data(), count);
            else
                wide_copy(data(), prefix->data(), count);
            set_length(total);
        }
    }
    return this;
}
