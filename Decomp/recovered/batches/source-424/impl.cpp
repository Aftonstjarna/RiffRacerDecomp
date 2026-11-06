#include "impl.hpp"

// Game.exe 0x5434f0..0x5435f6 (RVA 0x1434f0).
// Internal free iterator helper, not a member: ECX=first, EDX=middle,
// stack=last, caller cleanup. Portable entry below deliberately uses the
// platform C++ ABI; the original custom register ABI is adapted only in tests.
// The caller at 0x5434d9 rotates newly appended records into an insertion
// position, then advances its container end at +4. This routine itself changes
// only record bytes; it neither changes container pointers nor allocates.
void record24_rotate(unsigned char* first, unsigned char* middle, unsigned char* last)
{
    const int32_t shift = static_cast<int32_t>(middle - first) / 24;
    const int32_t count = static_cast<int32_t>(last - first) / 24;
    int32_t cycles = count;
    int32_t remainder = shift;
    while (remainder != 0) {
        const int32_t next = cycles % remainder;
        cycles = remainder;
        remainder = next;
    }
    if (cycles >= count || cycles <= 0)
        return;

    // The original chooses representatives gcd,...,1 rather than gcd-1,...,0.
    // Successive swaps pull the record one 'shift' ahead into the preceding
    // slot. Stop before swapping the last slot back into the representative.
    const int32_t stride = shift * 24;
    for (int32_t cycle = cycles; cycle > 0; --cycle) {
        unsigned char* const start = first + cycle * 24;
        unsigned char* next = start + stride;
        if (next == last)
            next = first;
        unsigned char* current = start;
        do {
            unsigned char saved[24];
            for (int i = 0; i < 24; ++i) saved[i] = current[i];
            for (int i = 0; i < 24; ++i) current[i] = next[i];
            for (int i = 0; i < 24; ++i) next[i] = saved[i];
            current = next;
            const int32_t remaining = static_cast<int32_t>(last - next) / 24;
            if (shift < remaining)
                next += stride;
            else
                next = first + (shift - remaining) * 24;
        } while (next != start);
    }
}
