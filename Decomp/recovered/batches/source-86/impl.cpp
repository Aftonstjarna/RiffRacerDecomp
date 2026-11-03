#include "impl.hpp"
namespace riff {
static void release(Interface* object) {
    reinterpret_cast<Release>(object->vtable[2])(object);
}
// VA 0x52D840, ECX=this, two stack arguments, callee pops 8; AL is bool.
// Caller 0x52DB44 supplies manager+8, then records advance by 16 bytes.
// COM vtable slots are stdcall (explicit interface pointer on stack).
bool ShaderPair::createUsing(const uint32_t* vertexCode, const uint32_t* pixelCode,
                             DeviceOwner* volatile* owner, GetConstants volatile* constants) {
    Interface* device = (*owner)->device;
    if (reinterpret_cast<CreateShader>(device->vtable[0x16c/4])(device, vertexCode, &vertex) < 0)
        return false;
    if ((*constants)(vertexCode, &vertexConstants) < 0) {
        // No null check here in original. Failed calls may still write output slots.
        release(vertex);
        vertex = 0;
        return false;
    }
    device = (*owner)->device; // Original reloads the global after vertex callbacks.
    if (reinterpret_cast<CreateShader>(device->vtable[0x1a8/4])(device, pixelCode, &pixel) >= 0) {
        if ((*constants)(pixelCode, &pixelConstants) >= 0)
            return true;
        release(pixel);
        pixel = 0;
    }
    if (vertexConstants) release(vertexConstants);
    // The shader load precedes the table-slot clear in the original.
    Interface* savedVertex = vertex;
    vertexConstants = 0;
    if (savedVertex) release(savedVertex);
    vertex = 0;
    return false;
}
bool RIFF_THISCALL ShaderPair::create(const uint32_t* v, const uint32_t* p) {
    return createUsing(v, p, reinterpret_cast<DeviceOwner* volatile*>(0xbfcc44u),
                       reinterpret_cast<GetConstants volatile*>(0x92d64cu));
}
}
