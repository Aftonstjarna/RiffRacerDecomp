#ifndef WORKER_REQUEST_HPP
#define WORKER_REQUEST_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RR_STDCALL __stdcall
#define RR_THISCALL __thiscall
#else
#define RR_STDCALL __attribute__((stdcall))
#define RR_THISCALL __attribute__((thiscall))
#endif
extern "C" {
uint32_t RR_STDCALL WaitForMultipleObjects(uint32_t, const uint32_t*, int32_t, uint32_t);
int32_t RR_STDCALL ResetEvent(uint32_t);
int32_t RR_STDCALL SetEvent(uint32_t);
uint32_t RR_STDCALL WaitForSingleObject(uint32_t, uint32_t);
}
// Original object prefix; unknown fields retain their offsets and contents.
struct Worker {
    uint8_t unknown000[0x50];
    uint8_t requestActive;
    uint8_t unknown051[0x458-0x51];
    uint32_t workEvents[2];
    uint32_t completionEvents[2];
    uint8_t unknown468[0x488-0x468];
    uint32_t selected;
    uint8_t unknown48c[0xba0-0x48c];
    uint8_t shuttingDown;
    uint8_t unknownba1[3];
    uint32_t pendingRequest;
    uint8_t requestResult;
    uint8_t unknownba9[3];
    uint8_t RR_THISCALL request(void* payload);
};
#endif
