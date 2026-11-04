#ifndef RIFF_AUX_TARGET_A_HPP
#define RIFF_AUX_TARGET_A_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_THISCALL __thiscall
#define RR_STDCALL __stdcall
#define RR_FASTCALL __fastcall
#else
#define RR_THISCALL __attribute__((thiscall))
#define RR_STDCALL __attribute__((stdcall))
#define RR_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
struct Interface { void** vtable; };
// Original MSVC narrow-string layout, not the host standard library's string.
struct NarrowString {
    union { char small[16]; char* heap; } storage;
    uint32_t length, capacity;
};
typedef int32_t (RR_STDCALL *CreateTexture)(Interface*, uint32_t, uint32_t,
    uint32_t, uint32_t, uint32_t, uint32_t, Interface**, void*);
typedef int32_t (RR_STDCALL *GetSurface)(Interface*, uint32_t, Interface**);
typedef NarrowString* (RR_FASTCALL *DescribeError)(NarrowString*, int32_t);
typedef NarrowString* (*PrefixError)(NarrowString*, const char*, NarrowString*);
typedef void (RR_THISCALL *MoveString)(NarrowString*, NarrowString*);
typedef NarrowString* (RR_THISCALL *MoveAssignString)(NarrowString*, NarrowString*);
typedef void (*FreeString)(void*);
// External game helpers remain dependencies, not newly recovered functions.
struct ErrorServices {
    DescribeError describe;          // 0x44f380, ECX=output, EDX=HRESULT
    PrefixError prefix;              // 0x4b2d20, cdecl; consumes/mutates description
    MoveString move;                 // 0x416fa0, thiscall, transfers storage
    MoveAssignString moveAssign;     // 0x440a20, thiscall
    FreeString volatile* freeSlot;   // import 0x92d4b0; reload timing matters
    const char* texturePrefix;
    const char* surfacePrefix;
};
struct Graphics {
    uint8_t unknown000[0x54];
    NarrowString lastError;                  // +0x54
    uint8_t unknown06c[0xc];
    Interface* device;                      // +0x78
    uint8_t unknown07c[0x23c-0x7c];
    uint32_t width, height;                  // +0x23c/+0x240
    uint8_t unknown244[0x43c-0x244];
    Interface* auxiliaryTexture;            // +0x43c
    Interface* auxiliarySurface;            // +0x440
    uint8_t unknown444[0xa5e - 0x444];
    uint8_t auxiliaryEnabled;               // +0xa5e (any nonzero)
    bool RR_THISCALL createAuxiliaryA();     // VA 0x4a56c0, bool in AL, no stack args
    bool createAuxiliaryAUsing(const ErrorServices& errors);
};
static_assert(sizeof(void*) != 4 || offsetof(Graphics, device)==0x78, "device layout");
static_assert(sizeof(void*) != 4 || offsetof(Graphics, auxiliaryTexture)==0x43c, "texture layout");
static_assert(sizeof(void*) != 4 || offsetof(Graphics, auxiliaryEnabled)==0xa5e, "enable layout");
}
#endif
