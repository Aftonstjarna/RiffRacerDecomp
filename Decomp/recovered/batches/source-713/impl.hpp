#ifndef RIFF_STREAM_APPEND_HPP
#define RIFF_STREAM_APPEND_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif

// Partial stream layout for VA 0x5cc7a0 (RVA 0x1cc7a0), 36 bytes.
// Names describe only this routine's observed use; surrounding words are opaque.
struct Stream {
    uint32_t unknown00;
    uint32_t unknown04;
    uint8_t* buffer;
    uint32_t unknown0c;
    uint32_t unknown10;
    uint32_t cursor;
    uint32_t unknown18;
    void RIFF_FASTCALL append_u16_be(uint32_t value);
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(Stream, buffer) == 0x08, "original buffer offset");
static_assert(offsetof(Stream, cursor) == 0x14, "original cursor offset");
#endif
#endif
