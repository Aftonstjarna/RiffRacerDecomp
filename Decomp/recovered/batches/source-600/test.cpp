#include "impl.hpp"
using namespace recovered;
extern "C" const char* __attribute__((thiscall)) original_convex_internal_shape_serialize(ConvexInternalShape*, ConvexInternalShape*, Serializer*);
struct Probe : Serializer {
    ConvexInternalShape* source;
    ConvexInternalShape* destination;
    const char* name;
    uint32_t unique;
    unsigned calls, failure;
    bool mutate;
    void RR_THISCALL slot0() {} void RR_THISCALL slot1() {}
    void RR_THISCALL slot2() {} void RR_THISCALL slot3() {}
    void RR_THISCALL slot4() {} void RR_THISCALL slot5() {}
    void RR_THISCALL slot7() {} void RR_THISCALL slot8() {}
    void RR_THISCALL slot10() {}
    const char* RR_THISCALL findNameForPointer(const void* p) {
        if (calls != 0 || p != source) failure = 1;
        calls = 1;
        return name;
    }
    uint32_t RR_THISCALL getUniquePointer(const char* p) {
        if (calls != 1 || p != name) failure = 2;
        calls = 2;
        if (mutate) source->shapeType ^= 0x12345678u;
        return unique;
    }
    void RR_THISCALL serializeName(const char* p) {
        if (calls != 2 || p != name || destination->vtable != unique) failure = 3;
        calls = 3;
        if (mutate) source->collisionMargin ^= 0xffffffffu;
    }
};
static bool same(const ConvexInternalShape& a, const ConvexInternalShape& b) {
    const unsigned char* x = reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y = reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    const uint32_t patterns[] = {0,0xffffffffu,0x80000000u,0x7fc12345u,0x7f800001u,0x3f800000u};
    for (unsigned c=0;c<96;++c) {
        ConvexInternalShape a, b, da, db;
        // unsigned-char initialization is legal for every word and padding byte.
        for (unsigned i=0;i<sizeof(a);++i) {
            reinterpret_cast<unsigned char*>(&a)[i] = static_cast<unsigned char>(c*17+i*31);
            reinterpret_cast<unsigned char*>(&da)[i] = static_cast<unsigned char>(0xa5+i);
        }
        a.localScaling[0] = patterns[c%6];
        a.collisionMargin = patterns[(c+1)%6];
        b=a; db=da;
        const ConvexInternalShape before=a, destBefore=da;
        Probe p, q;
        p.source=&a; p.destination=(c&8)?&a:&da;
        p.name=(c&1)?"shape-name":0;
        p.unique=(c&2)?0:((c&4)?0xffffffffu:0x12345678u);
        p.calls=0; p.failure=0; p.mutate=(c&16)!=0;
        q.source=&b; q.destination=(c&8)?&b:&db;
        q.name=p.name; q.unique=p.unique; q.calls=0; q.failure=0; q.mutate=p.mutate;
        const char* r=original_convex_internal_shape_serialize(&a,p.destination,&p);
        const char* s=b.serialize(q.destination,&q);
        if (reinterpret_cast<uintptr_t>(r)!=0x9f9950u) return 1;
        const char expected[]="btConvexInternalShapeData";
        for(unsigned i=0;i<sizeof(expected);++i) if(s[i]!=expected[i]) return 2;
        if(p.failure || q.failure || p.calls!=q.calls || p.calls!=(p.unique?3u:2u)) return 3;
        if(!same(a,b) || !same(da,db)) return 4;
        if(!p.mutate && !(c&8) && !same(a,before)) return 5;
        const ConvexInternalShape& out= *p.destination;
        const ConvexInternalShape& old= (c&8)?before:destBefore;
        if(out.untouched08!=old.untouched08 || out.untouched30!=old.untouched30) return 6;
        if(out.vtable!=p.unique) return 7;
    }
    return 0;
}
