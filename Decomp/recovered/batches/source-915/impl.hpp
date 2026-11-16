#ifndef RIFF_SCRIPT_LOCALS_HPP
#define RIFF_SCRIPT_LOCALS_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// Names describe observed use; original source type names are unavailable.
struct Local { uint32_t name; uint32_t flags; uint32_t end_position; };
struct Symbols { uint8_t unknown00[0x18]; Local* locals; };
struct Function {
    Symbols* symbols;
    uint8_t unknown04[0x14];
    uint32_t position;
    uint8_t unknown1c[0x16];
    uint8_t active_count;
    uint8_t unknown33[0x79];
    uint16_t active_indices[256];
};
struct Compiler {
    uint8_t unknown00[0x1c];
    Function* function;
    void RIFF_FASTCALL remove_active_locals(int32_t target);
};
}
#endif
