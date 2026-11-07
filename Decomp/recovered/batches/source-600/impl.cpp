#include "impl.hpp"
namespace recovered {
// Game.exe VA 0x438870, 121 bytes. ret 8, ECX=this. The destination's
// word zero is a serialized name pointer, not the source's vtable.
// Callers at 0x47d2ef, 0x48157e, 0x4ca0be and 0x4d1340 extend this record.
// Return text is evidenced at 0x9f9950. No null checks on either argument.
const char* RR_THISCALL ConvexInternalShape::serialize(
    ConvexInternalShape* data, Serializer* serializer) const {
    const char* name = serializer->findNameForPointer(this);
    const uint32_t unique = serializer->getUniquePointer(name);
    data->vtable = unique;
    if (unique) serializer->serializeName(name);
    data->shapeType = shapeType;
    data->implicitShapeDimensions[0] = implicitShapeDimensions[0];
    data->implicitShapeDimensions[1] = implicitShapeDimensions[1];
    data->implicitShapeDimensions[2] = implicitShapeDimensions[2];
    data->implicitShapeDimensions[3] = implicitShapeDimensions[3];
    data->localScaling[0] = localScaling[0];
    data->localScaling[1] = localScaling[1];
    data->localScaling[2] = localScaling[2];
    data->localScaling[3] = localScaling[3];
    data->collisionMargin = collisionMargin;
    return "btConvexInternalShapeData";
}
}
