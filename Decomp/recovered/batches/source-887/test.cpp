#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_error_reset_state(State*, int32_t);
extern "C" void __attribute__((fastcall)) original_script_close_upvalues(State*, Value*);
extern "C" void __attribute__((fastcall)) original_script_callinfo_resize(State*, int32_t);
// regparm(3) uses EAX,EDX,ECX and leaves remaining arguments caller-popped.
// The dummy EAX argument expresses the error setter's private ECX/EDX ABI.
extern "C" void __attribute__((regparm(3))) original_script_error_object_set(uint32_t, int32_t, State*, Value*);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsBacking[32];
static unsigned fsBad;
namespace riff {
void closeUpvalues(State* s, Value* p) { original_script_close_upvalues(s,p); if(test_get_fs_head()!=fsBacking[0])fsBad=1; }
void setErrorObject(State* s,int32_t status,Value* p) { original_script_error_object_set(0,status,s,p); if(test_get_fs_head()!=fsBacking[0])fsBad=1; }
void resizeCallInfo(State* s,int32_t n) { original_script_callinfo_resize(s,n); if(test_get_fs_head()!=fsBacking[0])fsBad=1; }
}
static_assert(sizeof(CallInfo)==24,"call-info stride");
static_assert(sizeof(State)==104,"state prefix");
static_assert(offsetof(State,currentCall)==0x14,"current frame");
static_assert(offsetof(State,baseCall)==0x28,"base frame");
static_assert(offsetof(State,nestedCalls)==0x34,"nesting");
static_assert(offsetof(State,openUpvalues)==0x58,"upvalues");
static_assert(offsetof(State,errorFunction)==0x64,"error function");
struct Upvalue {
    Upvalue* next; uint8_t type,marked,pad[2]; Value* value;
    union { Value closed; struct {Upvalue* next; Upvalue* previous;} links; } storage;
};
struct Fixture {
    State s;
    uint32_t global[32];
    CallInfo frames[4];
    CallInfo relocated[20000];
    Value stack[8];
    Upvalue node, sentinel, root;
    uint32_t calls,bad,oldSize,newSize,seenNested,seenHook,seenErrorFunction,seenErrorJump;
    uint32_t seenCurrent,seenBase,seenTop;
};
static Fixture f;
static unsigned char expected[sizeof(Fixture)];
extern "C" void* allocateObserver(void* userdata,void* block,uint32_t oldSize,uint32_t newSize) {
    Fixture* a=static_cast<Fixture*>(userdata);
    ++a->calls;
    a->oldSize=oldSize; a->newSize=newSize;
    a->seenNested=a->s.nestedCalls; a->seenHook=a->s.allowHook;
    a->seenErrorFunction=a->s.errorFunction;
    a->seenErrorJump=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(a->s.errorJump));
    a->seenCurrent=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(a->s.currentCall));
    a->seenBase=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(a->s.base));
    a->seenTop=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(a->s.top));
    if(block!=a->frames || newSize!=480000 || oldSize!=static_cast<uint32_t>(a->s.callCapacity)*24u)a->bad=1;
    // Deterministic relocating allocator: only one active base frame survives.
    a->relocated[0]=a->frames[0];
    return a->relocated;
}
static void initialize(int32_t capacity,unsigned open,unsigned nesting,unsigned mode) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof f;++i)p[i]=0xa5;
    f.s.global=f.global;
    f.global[3]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&allocateObserver));
    f.global[4]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&f));
    f.global[5]=2; // current-white=2, gc-phase=0
    f.global[7]=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&f.root));
    f.global[17]=0x12345678;
    f.s.currentCall=&f.frames[3]; f.s.baseCall=f.frames;
    f.s.lastCall=&f.frames[3]; f.s.base=&f.stack[6];
    f.frames[0].base=&f.stack[2];
    f.s.top=&f.stack[mode?2:7]; // includes source/destination boundary; setter default never copies
    f.s.callCapacity=capacity;
    f.s.nestedCalls=0xabcd; f.s.baseNestedCalls=static_cast<uint16_t>(nesting);
    f.s.allowHook=0xfe;
    f.s.errorJump=reinterpret_cast<void*>(0x12345678u); f.s.errorFunction=0x87654321u;
    f.s.openUpvalues=open?&f.node:0;
    f.node.next=0; f.node.marked=0x80;
    f.node.value=&f.stack[open==2?1:5];
    f.node.storage.links.next=&f.sentinel; f.node.storage.links.previous=&f.sentinel;
    f.sentinel.storage.links.next=&f.node; f.sentinel.storage.links.previous=&f.node;
    f.stack[5].payload=0xfedcba98; f.stack[5].tag=3; // no GC barrier required
    f.calls=f.bad=f.oldSize=f.newSize=0;
    f.seenNested=f.seenHook=f.seenErrorFunction=f.seenErrorJump=0;
    f.seenCurrent=f.seenBase=f.seenTop=0;
}
static int compare(int32_t status,int32_t capacity,unsigned open,unsigned nesting,unsigned mode) {
    initialize(capacity,open,nesting,mode);
    original_script_error_reset_state(&f.s,status);
    if(test_get_fs_head()!=fsBacking[0])return 1;
    if(f.bad)return 2;
    for(unsigned i=0;i<sizeof f;++i)expected[i]=reinterpret_cast<unsigned char*>(&f)[i];
    initialize(capacity,open,nesting,mode);
    f.s.resetAfterError(status);
    for(unsigned i=0;i<sizeof f;++i)if(expected[i]!=reinterpret_cast<unsigned char*>(&f)[i])return 3;
    if(f.s.currentCall!=(capacity>20000?f.relocated:f.frames) || f.s.base!=&f.stack[2] ||
       f.s.top!=&f.stack[3] || f.s.nestedCalls!=nesting || f.s.allowHook!=1 ||
       f.s.errorJump || f.s.errorFunction)return 4;
    if(f.calls!=(capacity>20000?1u:0u))return 5;
    if(f.calls && (f.seenNested!=nesting || f.seenHook!=1 ||
       f.seenErrorFunction!=0x87654321u || f.seenErrorJump!=0x12345678u ||
       f.newSize!=480000 || f.s.lastCall!=&f.relocated[19999] ||
       f.global[17]!=0x12345678u+480000u-static_cast<uint32_t>(capacity)*24u ||
       f.seenCurrent!=reinterpret_cast<uintptr_t>(f.frames) ||
       f.seenBase!=reinterpret_cast<uintptr_t>(&f.stack[2]) ||
       f.seenTop!=reinterpret_cast<uintptr_t>(&f.stack[3])))return 6;
    if(open==1 && (f.s.openUpvalues || f.node.value!=&f.node.storage.closed ||
       f.node.storage.closed.payload!=0xfedcba98 || f.node.storage.closed.tag!=3 ||
       f.global[7]!=reinterpret_cast<uintptr_t>(&f.node)))return 7;
    if(open==2 && (f.s.openUpvalues!=&f.node || f.node.value!=&f.stack[1]))return 8;
    return 0;
}
extern "C" int test_main() {
    fsBacking[0]=0xffffffffu;
    if(test_install_fs(fsBacking)!=0)return 20;
    // Status 2..5 need the external original jump table at 0x4f4cec.
    // It is outside the accepted 92-byte setter reference. Do not substitute
    // executable code or invent a fixed-address fixture binding for it.
    // All other statuses take the genuine setter's default path (top only).
    const int32_t statuses[]={0,1,6,7,-1,(-2147483647-1),2147483647};
    const int32_t capacities[]={-2147483647,-1,0,1,19999,20000,20001,20002,100000,2147483647};
    const unsigned nesting[]={0,1,0x7fff,0x8000,0xffff};
    unsigned count=0;
    for(unsigned a=0;a<7;++a)for(unsigned b=0;b<10;++b)
      for(unsigned c=0;c<3;++c)for(unsigned d=0;d<5;++d)for(unsigned m=0;m<2;++m){
        int result=compare(statuses[a],capacities[b],c,nesting[d],m);
        if(result)return 30+result;
        ++count;
      }
    if(fsBad || count!=2100)return 50;
    const char message[]="reset-state: 2100 original differential cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
