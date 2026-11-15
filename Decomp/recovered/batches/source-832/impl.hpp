#ifndef RIFF_ERROR_DISPATCH_HPP
#define RIFF_ERROR_DISPATCH_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THIS __thiscall
#define RIFF_FAST __fastcall
#else
#define RIFF_THIS __attribute__((thiscall))
#define RIFF_FAST __attribute__((fastcall))
#endif
namespace riff {
struct Value { uint32_t payload; int32_t tag; };
struct ScriptState {
    uint8_t unknown00[6];
    uint8_t status;
    uint8_t unknown07;
    Value* top;                         // +08, first free stack slot
    uint32_t unknown0c;
    void* global;                       // +10
    uint8_t unknown14[8];
    Value* stackLimit;                  // +1c
    uint8_t* stackBase;                 // +20
    uint8_t unknown24[8];
    int32_t stackCapacity;              // +2c
    uint8_t unknown30[0x30];
    void* errorJump;                    // +60
    int32_t errorHandlerOffset;         // +64, byte offset; zero disables
    void RIFF_THIS dispatchError();
};
static_assert(sizeof(void*)==4,"Original layout requires 32-bit pointers");
static_assert(offsetof(ScriptState,top)==8,"top");
static_assert(offsetof(ScriptState,stackLimit)==0x1c,"limit");
static_assert(offsetof(ScriptState,stackBase)==0x20,"base");
static_assert(offsetof(ScriptState,stackCapacity)==0x2c,"capacity");
static_assert(offsetof(ScriptState,errorJump)==0x60,"jump");
static_assert(offsetof(ScriptState,errorHandlerOffset)==0x64,"handler");
// External dependencies, not recovered here. Throw/grow use ECX/EDX.
void RIFF_FAST throwStatus(ScriptState*,int32_t); // VA 0x4f4d80
void RIFF_FAST growStack(ScriptState*,int32_t);   // VA 0x4f4ef0
// Portable adapter required for VA 0x4f5830: original takes state in ECX,
// function slot in EDX, result count on the caller-cleaned stack. Neither
// standard thiscall nor standard fastcall describes that three-argument ABI.
void callHandler(ScriptState*,Value* function,int32_t results);
}
#endif
