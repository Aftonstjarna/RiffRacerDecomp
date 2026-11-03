#include "impl.hpp"
namespace riff {
// D3D9 slots 26/27, D3DFMT_INDEX32=102, D3DPOOL_DEFAULT=0.
// Callers at 0x4a3884/0x4a6661 use 16 MiB and 0x60000 indices;
// callers at 0x540b5e/0x541b30 derive sizes from geometry.
int32_t RIFF_THISCALL Buffer::allocate(Device* requestedDevice, uint8_t dynamic,
                                     uint32_t bytes, uint32_t count) {
    const uint32_t usage = dynamic ? 0x248u : 0x228u;
    int32_t result = requestedDevice->vtable->createVertexBuffer(
        requestedDevice, bytes, usage, 0, 0, &vertexBuffer, 0);
    if (result < 0) return result;
    result = requestedDevice->vtable->createIndexBuffer(
        requestedDevice, count << 2, usage, 0x66, 0, &indexBuffer, 0);
    if (result < 0) {
        vertexBuffer->vtable->release(vertexBuffer);
        vertexBuffer = 0;
        return result;
    }
    device = requestedDevice;
    requestedDevice->vtable->addRef(requestedDevice);
    vertexBytes = bytes;
    indexCount = count;
    vertexCursor = 0;
    indexCursor = 0;
    return 0;
}
}
