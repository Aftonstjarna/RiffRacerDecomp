#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_collision_face_list_unlink(CollisionFaceList*, CollisionFace*);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d, int c, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    for (unsigned i=0;i<n;++i) a[i]=static_cast<unsigned char>(c);
    return d;
}
struct Fixture {
    unsigned guardBefore;
    CollisionFaceList list;
    unsigned guardAfter;
    CollisionFace faces[3];
    unsigned endGuard;
};
static Fixture live;
static unsigned char before[sizeof(Fixture)], expected[sizeof(Fixture)];
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static CollisionFace* node(unsigned index) {
    return index==3 ? 0 : &live.faces[index];
}
static bool compare(unsigned target) {
    memcpy(before,&live,sizeof(live));
    original_collision_face_list_unlink(&live.list,&live.faces[target]);
    memcpy(expected,&live,sizeof(live));
    memcpy(&live,before,sizeof(live));
    live.list.unlink(&live.faces[target]);
    return equal(&live,expected,sizeof(live));
}
extern "C" int test_main() {
    // Normal middle removal: verify intended effects independently as well.
    memset(&live,0xa5,sizeof(live));
    live.list.head=&live.faces[0]; live.list.count=3;
    for(unsigned i=0;i<3;++i) {
        live.faces[i].previous=i ? &live.faces[i-1] : 0;
        live.faces[i].next=i<2 ? &live.faces[i+1] : 0;
    }
    if(!compare(1)) return 1;
    if(live.list.head!=&live.faces[0] || live.list.count!=2 ||
       live.faces[0].next!=&live.faces[2] || live.faces[2].previous!=&live.faces[0] ||
       live.faces[1].previous!=&live.faces[0] || live.faces[1].next!=&live.faces[2]) return 2;
    const uint32_t counts[]={0,1,3,0xffffffffu,0x80000000u};
    // Enumerate all six links over three valid nodes or null. Includes head,
    // tail, sole node, absent membership, cycles, shared neighbors, self links.
    for(unsigned graph=0;graph<4096;++graph)
    for(unsigned head=0;head<4;++head)
    for(unsigned target=0;target<3;++target)
    for(unsigned c=0;c<5;++c) {
        memset(&live,0xa5,sizeof(live));
        unsigned bits=graph;
        for(unsigned i=0;i<3;++i) {
            live.faces[i].previous=node(bits&3); bits>>=2;
            live.faces[i].next=node(bits&3); bits>>=2;
        }
        live.list.head=node(head); live.list.count=counts[c];
        if(!compare(target)) return 3;
        if(live.list.count!=counts[c]-1u) return 4;
    }
    test_write("collision-face-list-unlink: passed\n",sizeof("collision-face-list-unlink: passed\n")-1);
    return 0;
}
