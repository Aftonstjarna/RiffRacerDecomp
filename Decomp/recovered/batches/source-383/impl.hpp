#ifndef RIFF_GRID_NOTIFY_HPP
#define RIFF_GRID_NOTIFY_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct ShaderEntry;
typedef void (RIFF_THISCALL *NotifySlot12)(ShaderEntry*);
struct ShaderEntryVtable {
    NotifySlot12 unknownSlots[3];
    NotifySlot12 notifySlot12;
};
struct ShaderEntry { const ShaderEntryVtable* vtable; };
struct ShaderGrid {
    uint8_t unknownPrefix[0xe1c];
    ShaderEntry* entries[6][280];
    void RIFF_THISCALL notifySlot12();
};
}
#endif
