#ifndef RIFF_AUDIO_BACKEND_RESET_HPP
#define RIFF_AUDIO_BACKEND_RESET_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Partial original object layout, not a complete audio class declaration.
// Image addresses remain 32-bit identities; a Linux backend integration must
// relocate/replace the table identity explicitly before indirect invocation.
struct AudioBackendState {
    uint8_t unknown0000[0x6d3c];
    uint32_t backendTableAddress; // +6d3c
    int32_t state6d40;
    uint8_t unknown6d44[0x0c];
    uint32_t state6d50;
    uint8_t unknown6d54[0x28];
    uint32_t state6d7c;
    uint32_t state6d80;
    uint32_t state6d84;
    uint32_t state6d88;
    uint32_t state6d8c;
    uint32_t state6d90;
    void RIFF_THISCALL reset();
};
static_assert(offsetof(AudioBackendState, backendTableAddress)==0x6d3c,"layout");
static_assert(offsetof(AudioBackendState, state6d50)==0x6d50,"layout");
static_assert(offsetof(AudioBackendState, state6d7c)==0x6d7c,"layout");
static_assert(sizeof(AudioBackendState)==0x6d94,"layout");
#endif
