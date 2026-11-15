#ifndef RIFF_SCRIPT_ERROR_RESET_HPP
#define RIFF_SCRIPT_ERROR_RESET_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_REGISTER_CALL __fastcall
#else
#define RIFF_REGISTER_CALL __attribute__((fastcall))
#endif
namespace riff {
struct Value { uint32_t payload; int32_t tag; };
struct CallInfo { Value* base; uint32_t rest[5]; }; // original stride: 24 bytes
struct State {
    uint8_t header[8];
    Value* top;                       // +08
    Value* base;                      // +0c
    void* global;                     // +10
    CallInfo* currentCall;            // +14
    uint8_t unknown18[12];
    CallInfo* lastCall;               // +24
    CallInfo* baseCall;               // +28
    uint32_t unknown2c;
    int32_t callCapacity;             // +30 (signed comparison)
    uint16_t nestedCalls;             // +34
    uint16_t baseNestedCalls;         // +36
    uint8_t unknown38;
    uint8_t allowHook;                // +39
    uint8_t unknown3a[30];
    void* openUpvalues;               // +58
    uint32_t unknown5c;
    void* errorJump;                  // +60
    uint32_t errorFunction;           // +64 stack-relative error handler
    // Original 0x4f4d00: ECX=this, EDX=status, no stack arguments.
    void RIFF_REGISTER_CALL resetAfterError(int32_t status);
};
// Integration seams for accepted helpers, NOT recovered in this bounded task.
// Keep their private hybrid register/stack ABIs in platform adapters.
void closeUpvalues(State*, Value* level);
void setErrorObject(State*, int32_t status, Value* destination);
void resizeCallInfo(State*, int32_t capacity);
}
#endif
