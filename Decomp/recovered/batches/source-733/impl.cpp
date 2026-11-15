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

namespace recovered {
// Game.exe 0x47d2e0..0x47d383; ECX=this, callee pops two arguments.
// Original vtable 0x9fb128, slot 12 (+0x30) contains this function at
// 0x9fb158; constructor installs that vtable at 0x47cd81. No direct call
// instruction to this target was found; polymorphic caller internals are
// outside this slice. Original type strings: 0x9fb0f8 and 0x9fb10c.
// The source count is latched after base serialization, before pointer lookup.
// Nonzero negative counts still allocate/finalize, but copy no elements.
const char* RR_THISCALL ConvexHullShape::serialize(HullData* data, Serializer* serializer) const {
    base.serialize(&data->base, serializer);
    const int32_t count = pointCount;
    data->count = count;
    data->points = count ? serializer->getUniquePointer(points) : 0;
    data->doublePoints = 0;
    if (count) {
        Chunk* chunk = serializer->allocate(16, count);
        uint32_t* output = chunk->data;
        for (int32_t i=0; i<count; ++i) {
            const uint32_t* input = points + static_cast<uint32_t>(i)*4;
            output[0]=input[0]; output[1]=input[1];
            output[2]=input[2]; output[3]=input[3];
            output += 4;
        }
        serializer->finalize(chunk, "btVector3FloatData", 0x59415241u, points);
    }
    return "btConvexHullShapeData";
}
}
