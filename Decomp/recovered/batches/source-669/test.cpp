#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" const char* __attribute__((thiscall)) original_collision_shape_serialize(
    CollisionShape*, CollisionShapeData*, Serializer*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(void*) == 4, "oracle ABI requires i386");
static_assert(offsetof(CollisionShape, shapeType) == 4, "shape layout");
static_assert(offsetof(SerializerVtable, getUniquePointer) == 0x18, "slot");
static_assert(offsetof(SerializerVtable, findNameForPointer) == 0x24, "slot");
static_assert(offsetof(SerializerVtable, serializeName) == 0x2c, "slot");
struct ShapeFixture { CollisionShape shape; uint32_t untouched[6]; };
struct OutputFixture { uint32_t before; CollisionShapeData data; uint32_t after[5]; };
struct Context {
    Serializer serializer;
    ShapeFixture* shape;
    OutputFixture* output;
    const char* name;
    void* unique;
    int32_t lateType;
    unsigned stage, errors, mutation;
    uint32_t guard;
};
static SerializerVtable first, second, third;
static const char text[] = "shape name";
static const char empty[] = "";
static void check(Context* c, bool ok) { if (!ok) ++c->errors; }
static const char* __attribute__((thiscall)) findName(Serializer* s, const void* p) {
    Context* c = reinterpret_cast<Context*>(s);
    check(c, c->stage++ == 0 && p == &c->shape->shape);
    check(c, c->output->data.name == reinterpret_cast<void*>(0x76543210u));
    c->serializer.vtable = &second; // Every call must reload the vtable.
    if (c->mutation) c->shape->shape.shapeType = c->lateType ^ 0x5555;
    return c->name;
}
static void* __attribute__((thiscall)) uniquePointer(Serializer* s, const void* p) {
    Context* c = reinterpret_cast<Context*>(s);
    check(c, c->stage++ == 1 && p == c->name);
    check(c, c->output->data.name == reinterpret_cast<void*>(0x76543210u));
    c->serializer.vtable = &third;
    if (c->mutation) c->shape->shape.shapeType = c->unique ? (c->lateType ^ 0x3333) : c->lateType;
    return c->unique;
}
static void __attribute__((thiscall)) serializeName(Serializer* s, const char* p) {
    Context* c = reinterpret_cast<Context*>(s);
    check(c, c->stage++ == 2 && p == c->name);
    check(c, c->output->data.name == c->unique);
    check(c, c->output->data.shapeType == 0x12345678);
    if (c->mutation) c->shape->shape.shapeType = c->lateType;
}
static bool sameText(const char* a, const char* b) {
    for (unsigned i=0; ; ++i) { if (a[i]!=b[i]) return false; if (!a[i]) return true; }
}
static int run(bool original, const char* name, void* unique, int32_t type,
               unsigned mutation, int32_t lateType) {
    ShapeFixture shape;
    shape.shape.originalVtable = reinterpret_cast<void*>(0x11223344u);
    shape.shape.shapeType = type;
    OutputFixture output;
    output.before = 0xa5a5a5a5u;
    output.data.name = reinterpret_cast<void*>(0x76543210u);
    output.data.shapeType = 0x12345678;
    for (unsigned i=0;i<6;++i) shape.untouched[i]=0xfeed0000u+i;
    for (unsigned i=0;i<5;++i) output.after[i]=0xface0000u+i;
    Context c = { {&first}, &shape, &output, name, unique, lateType, 0, 0, mutation, 0xdeadbeefu };
    const char* result = original ? original_collision_shape_serialize(&shape.shape, &output.data, &c.serializer)
                                 : shape.shape.serialize(&output.data, &c.serializer);
    // Original string need not be mapped: its exact pointer is checked instead.
    if (original) check(&c, reinterpret_cast<uintptr_t>(result)==0x9fb09cu);
    else check(&c, sameText(result, "btCollisionShapeData"));
    check(&c, c.stage == (unique ? 3u : 2u));
    check(&c, output.data.name == unique);
    check(&c, output.data.shapeType == (mutation ? lateType : type));
    check(&c, shape.shape.shapeType == (mutation ? lateType : type));
    check(&c, shape.shape.originalVtable == reinterpret_cast<void*>(0x11223344u));
    check(&c, output.before == 0xa5a5a5a5u && c.guard == 0xdeadbeefu);
    check(&c, c.serializer.vtable == &third && c.name == name && c.unique == unique);
    for (unsigned i=0;i<6;++i) check(&c, shape.untouched[i]==0xfeed0000u+i);
    for (unsigned i=0;i<5;++i) check(&c, output.after[i]==0xface0000u+i);
    return c.errors ? 1 : 0;
}
extern "C" int test_main() {
    first.findNameForPointer = findName;
    second.getUniquePointer = uniquePointer;
    third.serializeName = serializeName;
    const char* names[] = {0, empty, text};
    void* pointers[] = {0, reinterpret_cast<void*>(1u), reinterpret_cast<void*>(0xffffffffu), const_cast<char*>(text)};
    const int32_t types[] = {0, 1, 31, -1, INT32_MIN, INT32_MAX};
    for (unsigned n=0;n<3;++n) for (unsigned p=0;p<4;++p)
      for (unsigned t=0;t<6;++t) for (unsigned m=0;m<2;++m) {
        // Identical fixtures and expected callback traces for source and oracle.
        if (run(true,names[n],pointers[p],types[t],m,types[5-t])) return 1;
        if (run(false,names[n],pointers[p],types[t],m,types[5-t])) return 2;
      }
    static const char message[] = "collision-shape-serialize: 144 paired cases passed\n";
    test_write(message, sizeof(message)-1);
    return 0;
}
