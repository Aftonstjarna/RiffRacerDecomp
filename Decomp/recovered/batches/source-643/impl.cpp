#include "impl.hpp"
namespace riff {
ConvexAabbCachingShape* RIFF_THISCALL ConvexAabbCachingShape::construct() {
    shapeType = 35;
    userPointer = 0;
    localScaling[0] = 1.0f;
    localScaling[1] = 1.0f;
    localScaling[2] = 1.0f;
    localScaling[3] = 0.0f;
    collisionMargin = 0.04f;
    vtable = 0x009fafdc;
    localAabbMin[0] = 1.0f;
    localAabbMin[1] = 1.0f;
    localAabbMin[2] = 1.0f;
    localAabbMin[3] = 0.0f;
    localAabbMax[0] = -1.0f;
    localAabbMax[1] = -1.0f;
    localAabbMax[2] = -1.0f;
    localAabbMax[3] = 0.0f;
    localAabbValid = 0;
    return this;
}
}
