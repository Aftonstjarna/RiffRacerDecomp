#ifndef RECOVERED_CONVEX_SERIALIZE_HPP
#define RECOVERED_CONVEX_SERIALIZE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RR_THISCALL __thiscall
#elif defined(__i386__)
#define RR_THISCALL __attribute__((thiscall))
#else
#define RR_THISCALL
#endif
namespace recovered {
// Only the used serializer slots are understood here. No virtual destructor:
// the original calls slots 6, 9 and 11 at byte offsets 0x18, 0x24, 0x2c.
struct Serializer {
    virtual void RR_THISCALL slot0() = 0;
    virtual void RR_THISCALL slot1() = 0;
    virtual void RR_THISCALL slot2() = 0;
    virtual void RR_THISCALL slot3() = 0;
    virtual void RR_THISCALL slot4() = 0;
    virtual void RR_THISCALL slot5() = 0;
    virtual uint32_t RR_THISCALL getUniquePointer(const char* name) = 0;
    virtual void RR_THISCALL slot7() = 0;
    virtual void RR_THISCALL slot8() = 0;
    virtual const char* RR_THISCALL findNameForPointer(const void* shape) = 0;
    virtual void RR_THISCALL slot10() = 0;
    virtual void RR_THISCALL serializeName(const char* name) = 0;
};
// Raw words deliberately retain all floating-point bits, including NaNs.
// This is the relevant 32-bit layout, not a complete recovered Bullet class.
struct ConvexInternalShape {
    uint32_t vtable, shapeType, untouched08;
    uint32_t localScaling[4];
    uint32_t implicitShapeDimensions[4];
    uint32_t collisionMargin, untouched30;
    const char* RR_THISCALL serialize(ConvexInternalShape* data, Serializer* serializer) const;
};
static_assert(sizeof(ConvexInternalShape) == 0x34, "original 32-bit record extent");
}
#endif
