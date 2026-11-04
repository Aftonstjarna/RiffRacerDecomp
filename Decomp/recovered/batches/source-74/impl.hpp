#ifndef RIFF_WIDE_ERASE_HPP
#define RIFF_WIDE_ERASE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#define RIFF_NORETURN __declspec(noreturn)
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_NORETURN __attribute__((noreturn))
#endif
struct WideString {
    union Storage { uint16_t local[8]; uint16_t* heap; } storage;
    uint32_t size;
    uint32_t capacity;
    WideString* RIFF_THISCALL erase(uint32_t position, uint32_t count);
};
static_assert(offsetof(WideString, size) == 16, "original length offset");
static_assert(offsetof(WideString, capacity) == 20, "original capacity offset");
// Integration supplies the nonreturning std::_Xout_of_range equivalent.
extern "C" RIFF_NORETURN void wide_out_of_range(const char* message);
#endif
