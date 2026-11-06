#include "impl.hpp"
extern "C" uint32_t __attribute__((cdecl)) original_utf16_terminated_length(const uint16_t*);

static uint16_t storage[4100];
static uint16_t saved[4100];
static int check(unsigned offset, unsigned length)
{
    for (unsigned i = 0; i < 4100; ++i) saved[i] = storage[i];
    const uint32_t expected = original_utf16_terminated_length(storage + offset);
    for (unsigned i = 0; i < 4100; ++i)
        if (storage[i] != saved[i]) return 1;
    const uint32_t actual = utf16_terminated_length(storage + offset);
    if (expected != length || actual != expected) return 2;
    for (unsigned i = 0; i < 4100; ++i)
        if (storage[i] != saved[i]) return 3;
    return 0;
}
extern "C" int test_main()
{
    // Every zero position from empty through 4096 units, with nonzero
    // guards and tails; odd code-unit offsets exercise 2 mod 4 alignment.
    for (unsigned length = 0; length <= 4096; ++length) {
        for (unsigned i = 0; i < 4100; ++i)
            storage[i] = static_cast<uint16_t>(1 + (i * 7919u) % 65535u);
        storage[1 + length] = 0;
        int result = check(1, length);
        if (result) return result;
    }
    // Embedded byte zeros, surrogate pairs, lone surrogates, noncharacters
    // and a second zero after nonzero tail data are all plain code units.
    const uint16_t units[] = {0x0100, 0x00ff, 0xd800, 0xdc00, 0xdfff,
                              0xffff, 0xfffe, 0x8000, 0, 0x1234, 0};
    for (unsigned i = 0; i < 11; ++i) storage[i] = units[i];
    if (check(0, 8)) return 4;
    if (check(8, 0)) return 5;
    if (check(9, 1)) return 6;
    return 0;
}
