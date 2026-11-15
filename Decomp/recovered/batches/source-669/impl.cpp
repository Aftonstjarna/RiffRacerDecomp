#include "impl.hpp"
namespace riff {
// Game.exe VA 0x47c220, size 67; thiscall, two callee-popped arguments.
// Original vtables include 0x9fb0b8, slot +0x30 (0x9fb0e8).
// The caller at 0x47c294 supplies chunk data (+8) and serializer, then
// passes the returned type name to finalizeChunk with the SHAP chunk code.
// Name/unique-pointer terminology follows the Bullet serialization protocol;
// the actual serializer implementations and their ownership are not recovered.
const char* RIFF_THISCALL CollisionShape::serialize(CollisionShapeData* output,
                                                   Serializer* serializer) {
    const char* name = serializer->vtable->findNameForPointer(serializer, this);
    output->name = serializer->vtable->getUniquePointer(serializer, name);
    if (output->name) {
        serializer->vtable->serializeName(serializer, name);
    }
    output->shapeType = shapeType;
    // Original returns the static string at 0x9fb09c. Portable storage here.
    return "btCollisionShapeData";
}
}
