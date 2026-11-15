#ifndef RIFF_SHAPE_SERIALIZE_HPP
#define RIFF_SHAPE_SERIALIZE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct Shape;
struct Serializer;
// Only the observed prefix is modeled. Names describe serialization roles.
struct Chunk { uint32_t code, length; void* data; };
struct ShapeVTable {
    void* unused[11];
    int32_t (RIFF_THISCALL *serializedSize)(Shape*);
    const char* (RIFF_THISCALL *serialize)(Shape*, void*, Serializer*);
};
struct SerializerVTable {
    void* unused[3];
    Chunk* (RIFF_THISCALL *allocate)(Serializer*, int32_t, int32_t);
    void (RIFF_THISCALL *finalize)(Serializer*, Chunk*, const char*, uint32_t, Shape*);
};
struct Serializer { SerializerVTable* vtable; };
struct Shape {
    ShapeVTable* vtable;
    void RIFF_THISCALL serializeSingle(Serializer* serializer);
};
}
#endif
