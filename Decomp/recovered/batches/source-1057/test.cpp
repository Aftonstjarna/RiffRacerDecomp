#include "impl.hpp"
#include <stddef.h>
using namespace riff;
// Original hybrid ABI: unused EAX, parent EDX, state ECX, caller-popped child.
extern "C" void __attribute__((regparm(3))) original_script_gc_forward_barrier(unsigned, Object*, State*, Object*);
extern "C" void __attribute__((fastcall)) original_script_gc_mark_object(Global*, Object*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs[32];
static unsigned fsBad, calls;
namespace riff {
void markObject(Global* g, Object* o) {
    ++calls;
    original_script_gc_mark_object(g, o);
    if (test_get_fs_head()!=fs[0]) fsBad=1;
}
}
struct Fixture { State state; uint8_t global[64]; uint8_t parent[128]; uint8_t child[128]; };
static Fixture f;
static uint8_t expected[sizeof(Fixture)];
static void init(unsigned phase, unsigned white, unsigned pm, unsigned cm, unsigned type) {
    uint8_t* p=reinterpret_cast<uint8_t*>(&f);
    for (unsigned i=0;i<sizeof f;++i) p[i]=static_cast<uint8_t>(i*37+13);
    f.state.global=reinterpret_cast<Global*>(f.global);
    f.global[20]=static_cast<uint8_t>(white); f.global[21]=static_cast<uint8_t>(phase);
    f.parent[5]=static_cast<uint8_t>(pm); f.child[5]=static_cast<uint8_t>(cm); f.child[4]=static_cast<uint8_t>(type);
}
static int run(unsigned phase,unsigned white,unsigned pm,unsigned cm,unsigned type,bool same) {
    init(phase,white,pm,cm,type);
    Object* parent=reinterpret_cast<Object*>(f.parent);
    Object* child=reinterpret_cast<Object*>(same?f.parent:f.child);
    if (same) f.parent[4]=static_cast<uint8_t>(type);
    original_script_gc_forward_barrier(0,parent,&f.state,child);
    if(test_get_fs_head()!=fs[0]) return 1;
    uint8_t* bytes=reinterpret_cast<uint8_t*>(&f);
    for(unsigned i=0;i<sizeof f;++i) expected[i]=bytes[i];
    init(phase,white,pm,cm,type);
    if (same) f.parent[4]=static_cast<uint8_t>(type);
    calls=0; f.state.forwardBarrier(parent,child);
    if(fsBad || calls!=(phase==1?1u:0u)) return 2;
    for(unsigned i=0;i<sizeof f;++i) if(bytes[i]!=expected[i]) return 3;
    unsigned initial=same?pm:cm;
    if(phase==1 && child->marked!=(initial & 0xfc)) return 4;
    if(phase!=1 && parent->marked!=((pm & 0xf8)|(white & 3))) return 5;
    return 0;
}
extern "C" int test_main() {
    static_assert(offsetof(State,global)==16,"state layout");
    static_assert(offsetof(Global,phase)==21,"global layout");
    static_assert(offsetof(Object,marked)==5,"object layout");
    fs[0]=0x12345678; if(test_install_fs(fs)!=0) return 10;
    const unsigned phases[]={0,1,2,255};
    const unsigned types[]={0,3,11,255}; // marker returns before its external jump table
    for(unsigned a=0;a<4;++a) for(unsigned w=0;w<256;++w)
      for(unsigned m=0;m<256;++m) {
        unsigned c=(m*73+w*19)&255;
        int e=run(phases[a],w,m,c,types[(m+w)&3],false); if(e) return 20+e;
      }
    for(unsigned m=0;m<256;++m) for(unsigned a=0;a<4;++a) {
        int e=run(phases[a],m,m,m,types[m&3],true); if(e) return 30+e;
    }
    return 0;
}
