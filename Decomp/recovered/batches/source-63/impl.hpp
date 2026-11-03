#ifndef RIFF_BUFFER_HPP
#define RIFF_BUFFER_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#define RIFF_THISCALL __thiscall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Device;
struct Resource;
struct ResourceVTable {
    void* queryInterface;
    void* addRef;
    uint32_t (RIFF_STDCALL *release)(Resource*);
};
struct Resource { ResourceVTable* vtable; };
struct DeviceVTable {
    void* queryInterface;
    uint32_t (RIFF_STDCALL *addRef)(Device*);
    void* slots2Through25[24];
    int32_t (RIFF_STDCALL *createVertexBuffer)(Device*, uint32_t, uint32_t, uint32_t, uint32_t, Resource**, void*);
    int32_t (RIFF_STDCALL *createIndexBuffer)(Device*, uint32_t, uint32_t, uint32_t, uint32_t, Resource**, void*);
};
struct Device { DeviceVTable* vtable; };
// Original VA 0x5429a0, ECX=this, callee pops four 32-bit arguments.
// Layout is the 32-bit original; native ports may naturally widen pointers.
struct Buffer {
    Device* device;                 // +0
    Resource* vertexBuffer;         // +4
    Resource* indexBuffer;          // +8
    uint32_t vertexCursor;          // +12
    uint32_t indexCursor;           // +16
    uint32_t vertexBytes;           // +20
    uint32_t indexCount;            // +24
    int32_t RIFF_THISCALL allocate(Device*, uint8_t dynamic, uint32_t bytes, uint32_t count);
};
}
#endif
