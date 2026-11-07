#ifndef RIFF_RECORD32_REFERENCE_HPP
#define RIFF_RECORD32_REFERENCE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Original 32-bit address-space layouts; unknown fields retain neutral names.
struct RecordReference32 {
    uint32_t table_address;
    uint32_t record_address;
    uint32_t owner_address;
};
struct RecordIndex32 {
    uint32_t unknown0;
    uint32_t metadata_address; // metadata +8: first record index
    uint32_t owner_address;    // owner +12: record array address
    RecordReference32* RIFF_THISCALL index_reference(RecordReference32* output,
                                                   uint32_t index) const;
};
}
#endif
