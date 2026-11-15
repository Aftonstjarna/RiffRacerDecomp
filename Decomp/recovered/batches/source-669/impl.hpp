#ifndef RIFF_COLLISION_SHAPE_HPP
#define RIFF_COLLISION_SHAPE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Serializer;
// Only the three observed slots are named. Other operations are out of scope.
struct SerializerVtable {
    void* unused00[6];
    void* (RIFF_THISCALL *getUniquePointer)(Serializer*, const void*); // +0x18
    void* unused1c[2];
    const char* (RIFF_THISCALL *findNameForPointer)(Serializer*, const void*); // +0x24
    void* unused28;
    void (RIFF_THISCALL *serializeName)(Serializer*, const char*); // +0x2c
};
struct Serializer { SerializerVtable* vtable; };
struct CollisionShapeData {
    void* name;
    int32_t shapeType;
    // The routine leaves any trailing serialized padding untouched.
};
struct CollisionShape {
    void* originalVtable; // +0: not used by this routine
    int32_t shapeType;   // +4
    const char* RIFF_THISCALL serialize(CollisionShapeData* output, Serializer* serializer);
};
}
#endif
