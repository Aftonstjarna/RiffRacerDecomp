#include "impl.hpp"
namespace riff {
// Original: this in ECX, same pointer returned in EAX, no stack arguments.
// Genuine member method preserves the MSVC x86 thiscall convention.
// Requires a live writable record. Null/invalid pointers are not accepted.
// Direct original disassembly: thirteen immediate dword stores, no reads.
// Float interpretation of 0 and +0x24..+0x30 follows their IEEE encodings;
// only +0 is additionally confirmed by caller MOVSS use (e.g. 0x568b59).
// The six zeroed words and +0x1c/+0x20 retain unknown field types.
Record52* Record52::initialize() {
    value00 = -1.0f;
    words04[0] = 0;
    words04[1] = 0;
    words04[2] = 0;
    words04[3] = 0;
    words04[4] = 0;
    words04[5] = 0;
    word1c = UINT32_MAX;
    word20 = 0;
    values24[0] = 1.0f;
    values24[1] = 1.0f;
    values24[2] = 1.0f;
    values24[3] = 1.0f;
    return this;
}
// Direct call sites include 0x568b26/32, 0x5691c1, 0x574f8d,
// 0x575266, 0x5a8e86/91, 0x5a9283, 0x5ad051/5d and 0x5ad49d.
// They use stack records. At 0x5a928d and 0x5ad4a5 EAX is pushed as
// a subsequent call argument. No external dependency or SEH is present.
}
