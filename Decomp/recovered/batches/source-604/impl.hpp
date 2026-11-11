#ifndef RIFF_FOUR_RECORD20_HPP
#define RIFF_FOUR_RECORD20_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Observed layout, not recovered original type/field names. The first word
// and final three bytes are deliberately preserved by initialization.
struct Record20 {
    uint32_t preserved;
    uint32_t field04;
    uint32_t field08;
    uint32_t field0c;
    uint8_t flag10;
    uint8_t preserved11[3];
};
struct FourRecord20 {
    Record20 records[4];
    FourRecord20* RIFF_THISCALL initialize();
};
static_assert(sizeof(Record20) == 20, "record stride");
static_assert(offsetof(Record20, flag10) == 16, "flag offset");
static_assert(sizeof(FourRecord20) == 80, "embedded block size");
}
#endif
