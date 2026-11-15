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
struct Chunk { uint32_t header[2]; uint32_t* data; };
// Partial serializer interface; no virtual destructor. Hull uses slots 3, 4, 6;
// its accepted base helper also uses slots 9 and 11. Chunk payload is at +8.
struct Serializer {
    virtual void RR_THISCALL slot0() = 0;
    virtual void RR_THISCALL slot1() = 0;
    virtual void RR_THISCALL slot2() = 0;
    virtual Chunk* RR_THISCALL allocate(uint32_t elementSize, int32_t count) = 0;
    virtual void RR_THISCALL finalize(Chunk*, const char* type, uint32_t code, const void* oldPointer) = 0;
    virtual void RR_THISCALL slot5() = 0;
    virtual uint32_t RR_THISCALL getUniquePointer(const void* name) = 0;
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
// Serialized pointers are 32-bit serializer tokens, not host pointers.
struct HullData { ConvexInternalShape base; uint32_t points, doublePoints; int32_t count; };
struct ConvexHullShape {
    ConvexInternalShape base;
    uint32_t opaque34[10]; // Outside this routine; preserved verbatim.
    int32_t pointCount; // +0x5c: latched once after the base call.
    uint32_t pointCapacity; // +0x60: never read or written here.
    uint32_t* points; // +0x64: packed 16-byte vectors, including fourth word.
    const char* RR_THISCALL serialize(HullData*, Serializer*) const;
};
static_assert(sizeof(ConvexHullShape)==0x68, "original source extent");
static_assert(sizeof(HullData)==0x40, "serialized extent");
}
#endif
