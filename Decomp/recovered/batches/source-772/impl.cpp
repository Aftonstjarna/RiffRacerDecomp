#include "impl.hpp"
namespace riff {
// Game.exe 0x416a60..0x416a94. ECX=first, EDX=last, stack=destination,
// caller cleanup, EAX=result. This is a free range helper, not a member.
// Callers 0x415ea4 and 0x4163a1 pass vector-like begin/end and allocated
// storage; the former stores the returned end at destination-container +4.
// REP MOVSD copies 130 opaque words. Stage each word before writing so
// partial overlaps retain forward word-copy behavior (not memmove).
unsigned char* construct_record520_range(const unsigned char* first,
    const unsigned char* last, unsigned char* destination) {
    uintptr_t src = reinterpret_cast<uintptr_t>(first);
    const uintptr_t end = reinterpret_cast<uintptr_t>(last);
    uintptr_t dst = reinterpret_cast<uintptr_t>(destination);
    while (src != end) {
        if (dst != 0) {
            const unsigned char* s = reinterpret_cast<const unsigned char*>(src);
            unsigned char* d = reinterpret_cast<unsigned char*>(dst);
            for (unsigned i = 0; i < 520; i += 4) {
                const unsigned char a = s[i], b = s[i+1];
                const unsigned char c = s[i+2], e = s[i+3];
                d[i] = a; d[i+1] = b; d[i+2] = c; d[i+3] = e;
            }
        }
        src += 520;
        dst += 520;
    }
    return reinterpret_cast<unsigned char*>(dst);
}
}
