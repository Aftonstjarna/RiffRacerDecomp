#ifndef RIFF_REALLOCATE_HPP
#define RIFF_REALLOCATE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
typedef void* (*Allocator)(void*, void*, uint32_t, uint32_t);
typedef int (*Panic)(State*);
struct Global {
    uint8_t unknown00[12];
    Allocator allocator;                 // +0x0c, cdecl
    void* allocator_user;                // +0x10
    uint8_t unknown14[48];
    uint32_t allocated_bytes;            // +0x44, modulo 2^32
    uint8_t unknown48[16];
    Panic panic;                        // +0x58, cdecl; return value ignored
};
struct ErrorFrame {
    uint32_t unknown00;
    uint8_t jump_buffer[64];             // +4, CRT-specific contents opaque
    uint32_t status;                     // +0x44
};
// Integration dependencies, not substitute implementations of the VM or CRT.
struct ErrorServices {
    void (*jump)(void* jump_buffer, int value); // actual CRT longjmp does not return
    void (*prepare)(State*, uint32_t error);  // original 0x4f4d00
};
struct State {
    uint8_t unknown00[6];
    uint8_t status;                      // +6
    uint8_t unknown07[9];
    Global* global;                      // +0x10
    uint8_t unknown14[76];
    ErrorFrame* error_frame;             // +0x60
    void* reallocate(void* memory, uint32_t old_bytes, uint32_t new_bytes,
                     const ErrorServices& errors);
};
static_assert(offsetof(State,global)==16,"32-bit VM layout");
static_assert(offsetof(State,error_frame)==96,"32-bit VM layout");
static_assert(offsetof(Global,allocated_bytes)==68,"32-bit VM layout");
static_assert(offsetof(Global,panic)==88,"32-bit VM layout");
}
#endif
