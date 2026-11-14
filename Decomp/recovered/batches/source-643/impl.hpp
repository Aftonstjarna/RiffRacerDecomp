#ifndef RIFF_CONVEX_AABB_HPP
#define RIFF_CONVEX_AABB_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Original 32-bit btConvexInternalAabbCachingShape storage. The vtable token
// records the original identity; a Linux port must supply its own dispatch.
// No C++ virtual functions: host pointer size must not change these offsets.
struct ConvexAabbCachingShape {
    uint32_t vtable;                  // +00: original virtual table address
    int32_t shapeType;                // +04: CUSTOM_CONVEX_SHAPE_TYPE (35)
    uint32_t userPointer;             // +08: original 32-bit pointer
    float localScaling[4];           // +0c: xyz=1, w=0
    unsigned char implicitDimensions[16]; // +1c: not initialized here
    float collisionMargin;           // +2c: 0.04f
    unsigned char unknown30[4];       // +30: untouched
    float localAabbMin[4];            // +34: xyz=1, w=0
    float localAabbMax[4];            // +44: xyz=-1, w=0
    unsigned char localAabbValid;     // +54
    unsigned char tailPadding[3];     // +55: untouched
    // VA 0x47b640, 118 bytes. Models the constructor's ECX input and EAX
    // return explicitly while leaving object lifetime management to the port.
    ConvexAabbCachingShape* RIFF_THISCALL construct();
};
static_assert(offsetof(ConvexAabbCachingShape, collisionMargin)==0x2c,"layout");
static_assert(offsetof(ConvexAabbCachingShape, localAabbMin)==0x34,"layout");
static_assert(offsetof(ConvexAabbCachingShape, localAabbValid)==0x54,"layout");
static_assert(sizeof(ConvexAabbCachingShape)==0x58,"layout");
}
#endif
