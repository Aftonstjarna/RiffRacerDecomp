#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_close_upvalues(State*, Value*);
// Reallocate has a private hybrid ABI: ECX=state, EDX=block, old/new on
// caller-popped stack. regparm(3)'s unused EAX slot expresses it exactly.
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(uint32_t unusedEax, void* block, State* state, uint32_t, uint32_t);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsStorage[32];
static unsigned fsFailure;
static_assert(sizeof(Upvalue)==20, "original i386 upvalue layout");
static_assert(offsetof(State,openUpvalues)==0x58, "state layout");
static_assert(offsetof(Global,root)==0x1c, "global layout");
struct Fixture {
    State state;
    uint32_t globalWords[32];
    Upvalue nodes[5];
    Value values[5];
    Upvalue sentinel;
    uint8_t child[16];
    uint32_t calls, bad, freed[5], observedHead[5];
};
static Fixture f;
static unsigned char expected[sizeof(Fixture)];
static unsigned barrierCalls;
extern "C" void* freeObserver(void* userdata, void* block, uint32_t oldSize, uint32_t newSize) {
    Fixture* a = static_cast<Fixture*>(userdata);
    unsigned i=a->calls++;
    if (i>=5 || oldSize!=20 || newSize!=0) {a->bad=1;return 0;}
    a->freed[i]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(block));
    a->observedHead[i]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(a->state.openUpvalues));
    // Do not deallocate fixture memory: recording allocator proves call order,
    // exact size and accounting while permitting untouched-byte comparisons.
    return 0;
}
namespace riff {
void* reallocate(State* s, void* p, uint32_t oldSize, uint32_t newSize) {
    void* result=original_script_reallocate(0,p,s,oldSize,newSize);
    if(test_get_fs_head()!=fsStorage[0])fsFailure=1;
    return result;
}
void barrier(State*, Upvalue*, void*) { ++barrierCalls; }
}
static void init(unsigned count, unsigned mark, unsigned white, unsigned phase, int tag, bool closedDead) {
    unsigned char* bytes=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof f;++i)bytes[i]=0xa5;
    f.state.global=reinterpret_cast<Global*>(f.globalWords);
    f.state.openUpvalues=count?&f.nodes[0]:0;
    f.state.global->currentWhite=static_cast<uint8_t>(white);
    f.state.global->gcPhase=static_cast<uint8_t>(phase);
    f.state.global->root=&f.nodes[4];
    f.globalWords[3]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&freeObserver));
    f.globalWords[4]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&f));
    f.globalWords[17]=1000; // totalbytes at +44, decremented by original allocator
    f.calls=f.bad=0;
    for(unsigned i=0;i<5;++i){f.freed[i]=f.observedHead[i]=0;}
    f.child[5]=0; // avoid unavailable original barrier (explicit coverage limit)
    f.sentinel.storage.open.next=count?&f.nodes[0]:&f.sentinel;
    f.sentinel.storage.open.previous=count?&f.nodes[count-1]:&f.sentinel;
    for(unsigned i=0;i<count;++i){
        Upvalue& u=f.nodes[i];
        u.next=i+1<count?&f.nodes[i+1]:0;
        u.marked=static_cast<uint8_t>(mark);
        u.value=&f.values[count-1-i];
        f.values[count-1-i].payload=tag>=4?static_cast<uint32_t>(reinterpret_cast<uintptr_t>(f.child)):0xfedcba98u+i;
        f.values[count-1-i].tag=tag;
        u.storage.open.previous=i?&f.nodes[i-1]:&f.sentinel;
        u.storage.open.next=i+1<count?&f.nodes[i+1]:&f.sentinel;
        if(closedDead)u.value=&u.storage.closed;
    }
    barrierCalls=0;
}
static int compare(unsigned count,unsigned mark,unsigned white,unsigned phase,int tag,unsigned levelMode,bool closedDead=false) {
    init(count,mark,white,phase,tag,closedDead);
    Value* level=levelMode==0?reinterpret_cast<Value*>(0):
                 levelMode==1?reinterpret_cast<Value*>(~static_cast<uintptr_t>(0)):
                 &f.values[levelMode-2];
    original_script_close_upvalues(&f.state,level);
    if(test_get_fs_head()!=fsStorage[0])return 4;
    if(f.bad)return 1;
    for(unsigned i=0;i<sizeof f;++i) expected[i]=reinterpret_cast<unsigned char*>(&f)[i];
    init(count,mark,white,phase,tag,closedDead);
    f.state.closeUpvalues(level);
    if(barrierCalls)return 2;
    for(unsigned i=0;i<sizeof f;++i)if(expected[i]!=reinterpret_cast<unsigned char*>(&f)[i])return 3;
    return 0;
}
extern "C" int test_main() {
    fsStorage[0]=0xffffffffu;
    if(test_install_fs(fsStorage)!=0)return 20;
    // Whole-fixture equality covers unknown state/global bytes, list neighbors,
    // inline payload/tag, allocator callbacks, root order and unaffected slots.
    unsigned cases=0;
    const int tags[]={-1,0,3,4,5};
    for(unsigned count=0;count<=4;++count)
      for(unsigned mark=0;mark<32;++mark)
       for(unsigned white=0;white<4;++white)
        for(unsigned phase=0;phase<3;++phase)
         for(unsigned t=0;t<5;++t)
          for(unsigned level=0;level<6;++level){
            if(compare(count,mark,white,phase,tags[t],level))return 10;
            ++cases;
          }
    // Preserve upper mark bits and test mixed live/dead chains.
    const unsigned upperMarks[]={0x80,0x84,0xfd,0xff};
    for(unsigned i=0;i<4;++i)
      if(compare(4,upperMarks[i],2,1,5,0))return 15;
    init(4,0,2,0,3,false);
    f.nodes[1].marked=1;
    f.nodes[3].marked=1;
    original_script_close_upvalues(&f.state,reinterpret_cast<Value*>(0));
    if(test_get_fs_head()!=fsStorage[0])return 21;
    for(unsigned i=0;i<sizeof f;++i)expected[i]=reinterpret_cast<unsigned char*>(&f)[i];
    init(4,0,2,0,3,false);
    f.nodes[1].marked=1;
    f.nodes[3].marked=1;
    f.state.closeUpvalues(reinterpret_cast<Value*>(0));
    for(unsigned i=0;i<sizeof f;++i)
      if(expected[i]!=reinterpret_cast<unsigned char*>(&f)[i])return 16;
    // Dead already-closed nodes skip unlinking (otherwise union is links).
    if(compare(1,1,2,0,0,0,true))return 11;
    // Independent assertions make critical semantics explicit, beyond equality.
    init(3,0x80,2,0,3,false);
    f.state.closeUpvalues(&f.values[1]);
    if(f.state.openUpvalues!=&f.nodes[2] || f.state.global->root!=&f.nodes[1] ||
       f.nodes[1].next!=&f.nodes[0] || f.nodes[0].next!=&f.nodes[4] ||
       f.nodes[0].marked!=0x82 || f.nodes[1].marked!=0x82 ||
       f.nodes[1].value!=&f.nodes[1].storage.closed ||
       f.nodes[1].storage.closed.payload!=0xfedcba99u || f.calls)return 12;
    init(3,1,2,0,0,false);
    f.state.closeUpvalues(reinterpret_cast<Value*>(0));
    if(f.calls!=3 || f.globalWords[17]!=940 || f.state.openUpvalues ||
       f.sentinel.storage.open.next!=&f.sentinel ||
       f.sentinel.storage.open.previous!=&f.sentinel ||
       f.observedHead[0]!=reinterpret_cast<uintptr_t>(&f.nodes[1]))return 13;
    if(cases!=57600 || fsFailure)return 14;
    test_write("close-upvalues differential tests passed\n",sizeof("close-upvalues differential tests passed\n")-1);
    return 0;
}
