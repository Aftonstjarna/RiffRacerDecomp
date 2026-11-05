#include "impl.hpp"

// Game.exe 0x441f70..0x441fa6; ECX=this, one stack argument,
// callee removes four bytes; EAX passes through append_range's result.
// Callers include minimum_caps at 0x4a5ac0 (this = owner + 0x54),
// and string-building calls at 0x523400 and 0x59e14a.
// This wrapper accesses no object fields and performs no writes before delegation.
// text must point to a readable NUL-terminated byte string: NULL is not accepted.
// Bytes with the high bit set are ordinary nonzero bytes. Embedded NUL ends the
// scan. Scan precedes delegation, including when text aliases this string.
NarrowString* RIFF_THISCALL NarrowString::append_terminated(const char* text) {
    uint32_t count = 0;
    if (*text != '\0') {
        const char* end = text;
        do { ++end; } while (*end != '\0');
        count = static_cast<uint32_t>(end - text);
    }
    return append_range(text, count);
}
