#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_collision_shape_serialize_single(Shape*, Serializer*);
struct ShapeFixture { Shape base; uint32_t guards[5]; };
struct SerializerFixture { Serializer base; uint32_t guards[5]; };
static ShapeFixture shape;
static SerializerFixture serializer;
static ShapeVTable sv[2];
static SerializerVTable zv[2];
static Chunk chunk;
static uint32_t data[4];
static int stage, errors, mode;
static int32_t sizeValue;
static const char typeName[] = "test shape";
static void check(bool ok) { if (!ok) ++errors; }
static int32_t RIFF_THISCALL getSize(Shape* p) {
    check(p == &shape.base && stage++ == 0);
    shape.guards[1] ^= 0x12345678u;
    return sizeValue;
}
static const char* RIFF_THISCALL serializeData(Shape* p, void* buffer, Serializer* s) {
    check(p == &shape.base && s == &serializer.base && stage++ == 2);
    check(buffer == (mode == 2 ? 0 : data));
    data[1] = 0xfedcba98u;
    s->vtable = &zv[1];
    return mode == 1 ? 0 : typeName;
}
static const char* RIFF_THISCALL wrongSerialize(Shape*, void*, Serializer*) { ++errors; return 0; }
static Chunk* RIFF_THISCALL allocate(Serializer* s, int32_t size, int32_t count) {
    check(s == &serializer.base && stage++ == 1 && size == sizeValue && count == 1);
    shape.base.vtable = &sv[1];
    chunk.data = mode == 2 ? 0 : data;
    serializer.guards[2] += 7;
    return &chunk;
}
static void RIFF_THISCALL finalize(Serializer* s, Chunk* c, const char* type, uint32_t tag, Shape* p) {
    check(s == &serializer.base && c == &chunk && stage++ == 3);
    check(type == (mode == 1 ? 0 : typeName) && tag == 0x50414853u && p == &shape.base);
    chunk.length ^= 0x87654321u;
}
static void RIFF_THISCALL wrongFinalize(Serializer*, Chunk*, const char*, uint32_t, Shape*) { ++errors; }
static void reset() {
    stage = 0;
    sv[0].serializedSize = getSize; sv[1].serializedSize = getSize;
    sv[0].serialize = wrongSerialize; sv[1].serialize = serializeData;
    zv[0].allocate = allocate; zv[1].allocate = allocate;
    zv[0].finalize = wrongFinalize; zv[1].finalize = finalize;
    shape.base.vtable = &sv[0]; serializer.base.vtable = &zv[0];
    for (unsigned i=0;i<5;++i) { shape.guards[i]=0xabcdef00u+i; serializer.guards[i]=0x12345600u+i; }
    for (unsigned i=0;i<4;++i) data[i]=0xfeed0000u+i;
    chunk.code=0x88888888u; chunk.length=0x11111111u; chunk.data=0;
}
static void verify() {
    check(stage == 4 && shape.base.vtable == &sv[1] && serializer.base.vtable == &zv[1]);
    for (unsigned i=0;i<5;++i) {
        check(shape.guards[i] == ((0xabcdef00u+i) ^ (i==1 ? 0x12345678u : 0u)));
        check(serializer.guards[i] == 0x12345600u+i+(i==2 ? 7u : 0u));
    }
    for (unsigned i=0;i<4;++i) check(data[i] == (i==1 ? 0xfedcba98u : 0xfeed0000u+i));
    check(chunk.code == 0x88888888u && chunk.length == (0x11111111u ^ 0x87654321u));
    check(chunk.data == (mode==2 ? 0 : data));
}
extern "C" int test_main() {
    const int32_t sizes[] = {0,1,16,4096,-1,(-2147483647-1),2147483647};
    for (mode=0;mode<3;++mode) for (unsigned i=0;i<sizeof(sizes)/sizeof(sizes[0]);++i) {
        sizeValue=sizes[i]; reset(); original_collision_shape_serialize_single(&shape.base,&serializer.base); verify();
        reset(); shape.base.serializeSingle(&serializer.base); verify();
    }
    return errors ? 1 : 0;
}
