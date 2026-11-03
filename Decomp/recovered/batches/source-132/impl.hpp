#ifndef RIFF_REQUEST_CASE3_HPP
#define RIFF_REQUEST_CASE3_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Request3 {
    uint32_t kind;                 // dispatcher selects this method for kind 3
    uint32_t logicalWidth, logicalHeight;
    uint32_t windowWidth, windowHeight;
    uint32_t unused14, setting18;
    uint8_t mode, flag, unused1e[2];
};
struct Display {
    uint8_t unknown000[0x254];
    uint32_t logicalWidth, logicalHeight; // +254, +258
    uint32_t windowWidth, windowHeight;   // +25c, +260
    uint32_t saved274, setting18;         // +264, +268
    uint8_t unknown26c[8];
    uint32_t source274;
    uint8_t unknown278[0x4ac-0x278];
    float scaleX, scaleY;
    uint8_t unknown4b4[7];
    uint8_t flag;                         // +4bb, always copied
    uint8_t unknown4bc[3];
    uint8_t comparedMode;                 // +4bf, never written here
    bool RIFF_THISCALL requestCase3(const Request3* request);
};
// Port boundary for original singleton [0xbfcc28] and method 0x48cc70.
// The callback must preserve thiscall stack cleanup on i386. No window helper
// implementation is claimed here. Its return value (if any) is ignored.
typedef void (RIFF_THISCALL *SecondaryWindowUpdate)(void*,uint32_t,uint32_t,uint32_t);
extern void* windowSystem;
extern SecondaryWindowUpdate updateSecondaryWindow;
static_assert(offsetof(Display,logicalWidth)==0x254,"layout");
static_assert(offsetof(Display,source274)==0x274,"layout");
static_assert(offsetof(Display,scaleX)==0x4ac,"layout");
static_assert(offsetof(Display,flag)==0x4bb,"layout");
static_assert(offsetof(Display,comparedMode)==0x4bf,"layout");
static_assert(sizeof(Request3)==0x20,"request layout");
}
#endif
