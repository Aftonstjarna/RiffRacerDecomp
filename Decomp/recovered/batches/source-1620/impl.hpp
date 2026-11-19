#ifndef UI_ITEM_FOCUS_HPP
#define UI_ITEM_FOCUS_HPP
#include <stdint.h>

struct UiItem;
#ifdef _MSC_VER
#define UI_THISCALL __thiscall
#else
#define UI_THISCALL __attribute__((thiscall))
#endif
// Only the observed vtable entry and object offsets are identified.
typedef void (UI_THISCALL *UiFocusCallback)(UiItem*, int32_t, int32_t);
struct UiItemVtable { void* unknown[21]; UiFocusCallback set_focus; };
struct UiItem {
    UiItemVtable* vtable;             // 0x000
    uint32_t unknown04;
    uint32_t id;                     // 0x008
    uint32_t unknown0c;
    uint32_t state;                  // 0x010
    uint8_t unknown14[0x160];
    uint8_t flags;                   // 0x174
    uint8_t unknown175[3];
    UiItem** children_begin;          // 0x178
    UiItem** children_end;            // 0x17c
    uint8_t unknown180[0x10];
    uint8_t alternate_eligible;      // 0x190
    bool set_focus_id(uint32_t target);
};
#endif
