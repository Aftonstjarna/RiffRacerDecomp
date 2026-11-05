#include "impl.hpp"
// Original VA 0x442170..0x442254: ECX=this, source/count on stack,
// EAX=result, RET 8. The 32-bit object has length at +16, capacity at +20.
// The terminated wrapper calls at 0x441f80 (empty) and 0x441f9c
// (scanned count). No FS registration or allocation occurs locally.
NarrowString* RIFF_THISCALL NarrowString::append_range(const char* source, uint32_t count) {
    if (source) {
        char* base = capacity >= 16 ? storage.heap : storage.local;
        const uintptr_t p = reinterpret_cast<uintptr_t>(source);
        const uintptr_t begin = reinterpret_cast<uintptr_t>(base);
        // Exclusive logical end; the terminator and unused capacity are external.
        if (p >= begin && p < begin + length)
            return append_substring(this, static_cast<uint32_t>(p - begin), count);
    }
    const uint32_t old_length = length;
    // Reject a sum of UINT_MAX as well as unsigned overflow. Alias delegation
    // precedes this check, allowing its dependency to clamp large counts.
    if (0xffffffffu - old_length <= count)
        narrow_length_error("string too long");
    if (count != 0 && prepare_append(old_length + count, false)) {
        char* base = capacity >= 16 ? storage.heap : storage.local;
        // Read length again after preparation, as the original does.
        narrow_copy(base + length, source, count);
        length = old_length + count;
        base = capacity >= 16 ? storage.heap : storage.local;
        base[length] = 0;
    }
    return this;
}
