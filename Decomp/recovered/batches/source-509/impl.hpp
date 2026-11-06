#ifndef RIFF_NARROW_COMPARE_RANGE_HPP
#define RIFF_NARROW_COMPARE_RANGE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_NORETURN __declspec(noreturn)
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_NORETURN __attribute__((noreturn))
#endif
namespace riff {
// Port integration boundary: original imports std::_Xout_of_range(const char*).
// Must throw the platform's out-of-range exception, and must never return.
RIFF_NORETURN void narrow_out_of_range(const char* message);
struct NarrowString {
    union Storage { unsigned char small[16]; const unsigned char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    int RIFF_THISCALL compare(uint32_t position, uint32_t count,
                              const unsigned char* right, uint32_t right_count) const;
};
#if defined(_MSC_VER) || defined(__i386__)
static_assert(sizeof(NarrowString)==24, "original i386 string layout");
#endif
}
#endif
