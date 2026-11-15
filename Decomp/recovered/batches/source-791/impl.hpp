#ifndef RIFF_TABLE_H
#define RIFF_TABLE_H
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
struct ScriptArraySlot {
    uint32_t payload;
    uint32_t tag;
};
// Partial table layout, inferred from this routine only. Unknown words are opaque.
struct ScriptTable {
    uint32_t unknown00[3];
    ScriptArraySlot* array; // original +0x0c
    uint32_t unknown10[3];
    int32_t arraySize;      // original +0x1c, compared as signed
    uint32_t RIFF_FASTCALL countArrayHistogram(uint32_t* histogram) const;
};
}
#endif
