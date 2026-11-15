#ifndef RIFF_POINTER_RANGE_HPP
#define RIFF_POINTER_RANGE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
namespace riff {
// Original 32-bit address layout; capacity is not read by this routine.
struct PointerRange32 { uint32_t begin; uint32_t end; uint32_t capacity; };
// VA 0x53c7c0, 75 bytes. Free stdcall function: ECX is overwritten,
// three stack slots are removed, and only AL is a defined result.
bool RIFF_STDCALL pointer_range_has_state_six_or_seven(
    uint32_t unused, int32_t index, const PointerRange32* range);
}
#endif
