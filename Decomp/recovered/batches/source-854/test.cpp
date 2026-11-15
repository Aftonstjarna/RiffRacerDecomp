#include "impl.hpp"
using namespace riff;
extern "C" String* __attribute__((regparm(3))) original_script_string_intern(unsigned,const char*,State*,uint32_t);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(unsigned,void*,State*,uint32_t,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void* d,int c,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c;return d;}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copySlot __attribute__((section(".test_iat"),used,aligned(4)))=memcpy;
static bool same(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
struct Storage { String h; char data[520]; };
static State state;
static Global globals,alternate;
static String* buckets[64];static String* otherBuckets[64];
static Storage nodes[4],allocation;
static char input[520];
static unsigned calls,bad,requested,resizeCalls,resizeSize;
static bool mutate;
static void* allocator(void* ud,void* old,uint32_t oldN,uint32_t newN){
    ++calls;requested=newN;
    if(ud!=&globals||old||oldN||newN>sizeof allocation)bad=1;
    if(mutate)state.global=&alternate;
    return &allocation;
}
static void* reallocate(State* s,void* p,uint32_t oldN,uint32_t newN){
    void* r=original_script_reallocate(0,p,s,oldN,newN);
    if(test_get_fs_head()!=0xffffffffu)bad=1;
    return r;
}
static void resize(State* s,uint32_t n){
    ++resizeCalls;resizeSize=n;if(s!=&state)bad=1;
    // Dependency boundary only: publication must precede the growth call.
    Global* g=s->global;
    if(g->buckets[allocation.h.hash&(g->capacity-1)]!=&allocation.h)bad=1;
}
static void sizeError(State*){bad=1;}
static const Services services={reallocate,resize,sizeError};
static uint32_t hashText(unsigned n){uint32_t h=n,step=(n>>5)+1;for(unsigned i=n;i>=step;i-=step)h^=(h<<5)+(h>>2)+(uint8_t)input[i-1];return h;}
// mode 0: empty bucket; 1: exact key after length mismatch; 2: same-length
// mismatches at each tested byte; 3: exact key after both collision kinds.
static void setup(unsigned len,unsigned mode,unsigned mismatch,unsigned mark,unsigned white,bool change){
    memset(&state,0xa5,sizeof state);memset(&globals,0x76,sizeof globals);memset(&alternate,0x87,sizeof alternate);
    memset(buckets,0,sizeof buckets);memset(otherBuckets,0,sizeof otherBuckets);
    memset(nodes,0x59,sizeof nodes);memset(&allocation,0xcd,sizeof allocation);
    for(unsigned i=0;i<520;++i)input[i]=(char)((i*71+len*3)&255);
    uint32_t h=hashText(len);
    for(unsigned j=0;j<4;++j){nodes[j].h.next=0;nodes[j].h.length=len;nodes[j].h.mark=(uint8_t)mark;nodes[j].h.hash=h^0xdeadbeef;memcpy(nodes[j].data,input,len);}
    // Stored hash and terminator are never compared on a hit.
    nodes[0].data[len]=(char)0x91;
    nodes[1].h.length=len+1;
    if(len)nodes[2].data[mismatch%len]^=1;else nodes[2].h.length=1;
    if(mode==1){nodes[1].h.next=&nodes[0].h;buckets[h&63]=&nodes[1].h;}
    if(mode==2){nodes[2].h.next=&nodes[1].h;buckets[h&63]=&nodes[2].h;}
    if(mode==3){nodes[2].h.next=&nodes[1].h;nodes[1].h.next=&nodes[0].h;buckets[h&63]=&nodes[2].h;}
    globals.buckets=buckets;globals.capacity=64;globals.count=mode?3:0;
    globals.allocator=(void*)&allocator;globals.allocatorData=&globals;globals.white=(uint8_t)white;
    *(uint32_t*)((uint8_t*)&globals+68)=0xfffffff0u;
    alternate.buckets=otherBuckets;alternate.capacity=32;alternate.count=7;alternate.white=(uint8_t)(white^3);
    state.global=&globals;mutate=change;
    calls=bad=requested=resizeCalls=resizeSize=0;
}
struct Snapshot {State s;Global g,a;String* b[64];String* o[64];Storage n[4],alloc;char in[520];unsigned calls,requested;};
static void capture(Snapshot& s){s.s=state;s.g=globals;s.a=alternate;memcpy(s.b,buckets,sizeof buckets);memcpy(s.o,otherBuckets,sizeof otherBuckets);memcpy(s.n,nodes,sizeof nodes);s.alloc=allocation;memcpy(s.in,input,520);s.calls=calls;s.requested=requested;}
static int run(unsigned len,unsigned mode,unsigned mismatch,unsigned mark,unsigned white,bool change){
    setup(len,mode,mismatch,mark,white,change);Snapshot before;capture(before);
    String* r=original_script_string_intern(0,input,&state,len);
    if(test_get_fs_head()!=0xffffffffu||bad)return 1;
    bool hit=mode==1||mode==3;
    if(r!=(hit?&nodes[0].h:&allocation.h)||calls!=(hit?0u:1u)||(!hit&&requested!=len+17))return 2;
    Snapshot oracle;capture(oracle);
    if(hit){
        if((static_cast<uint8_t>(~white)&(mark&3))!=0)before.n[0].h.mark^=3;
        if(!same(&before,&oracle,sizeof before))return 3;
    }else{
        // Independent checks on initialized and deliberately untouched bytes.
        if(allocation.h.type!=4||allocation.h.reserved||allocation.h.untouched!=0xcd||allocation.h.length!=len||allocation.h.hash!=hashText(len))return 4;
        if(allocation.h.mark!=((change?(white^3):white)&3)||allocation.data[len]!=0||!same(allocation.data,input,len))return 5;
        for(unsigned i=len+1;i<520;++i)if((uint8_t)allocation.data[i]!=0xcd)return 6;
        Global* g=change?&alternate:&globals;
        if(g->count!=(change?8u:(mode?4u:1u))||g->buckets[hashText(len)&(g->capacity-1)]!=r)return 7;
        if(!same(nodes,before.n,sizeof nodes)||!same(input,before.in,520)||!same(state.unknown,before.s.unknown,16)||!same(state.rest,before.s.rest,80))return 8;
        if(*(uint32_t*)((uint8_t*)&globals+68)!=0xfffffff0u+len+17)return 9;
        // Construct the entire expected memory image, including untouched fields.
        Global& expectedGlobal=change?before.a:before.g;
        String** expectedBuckets=change?before.o:before.b;
        unsigned index=hashText(len)&(expectedGlobal.capacity-1);
        before.alloc.h.next=expectedBuckets[index];
        before.alloc.h.type=4;before.alloc.h.mark=expectedGlobal.white&3;
        before.alloc.h.reserved=0;before.alloc.h.hash=hashText(len);before.alloc.h.length=len;
        memcpy(before.alloc.data,input,len);before.alloc.data[len]=0;
        expectedBuckets[index]=&allocation.h;++expectedGlobal.count;
        before.s.global=change?&alternate:&globals;
        *(uint32_t*)((uint8_t*)&before.g+68)+=len+17;
        before.calls=1;before.requested=len+17;
        if(!same(&before,&oracle,sizeof before))return 13;
    }
    setup(len,mode,mismatch,mark,white,change);
    String* recovered=state.intern(input,len,services);Snapshot actual;capture(actual);
    if(recovered!=r||bad||resizeCalls||!same(&oracle,&actual,sizeof oracle))return 10;
    return 0;
}
static int growthBoundaries(){
    // Real resize implementation at 0x4f5d70 has no accepted reference.
    // These source-only cases verify the exact request and signed capacity guard.
    const uint32_t caps[]={1,2,32,0x3ffffffe,0x3fffffff,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<7;++i)for(unsigned j=0;j<3;++j){
        setup(0,0,0,0,0,false);globals.capacity=caps[i];
        globals.count=j==0?caps[i]-1:(j==1?caps[i]:0xffffffffu);
        uint32_t next=globals.count+1;
        state.intern(input,0,services);
        bool grow=next>caps[i]&&static_cast<int32_t>(caps[i])<=0x3ffffffe;
        if(bad||resizeCalls!=(grow?1u:0u)||(grow&&resizeSize!=caps[i]*2)||globals.count!=next)return 11;
    }
    return 0;
}
extern "C" int test_main(){
    static unsigned fs[8];fs[0]=0xffffffffu;if(test_install_fs(fs)!=0)return 12;
    copySlot=memcpy;
    const unsigned lens[]={0,1,2,3,4,5,7,8,9,31,32,33,63,64,65,127,255,511};
    for(unsigned l=0;l<18;++l)for(unsigned mode=0;mode<4;++mode)for(unsigned bits=0;bits<256;++bits){
        int r=run(lens[l],mode,bits,bits,(bits*13)&255,(bits&16)!=0);if(r)return r;
    }
    // All white-bit combinations against all mark bytes on an existing string.
    for(unsigned mark=0;mark<256;++mark)for(unsigned white=0;white<256;++white){int r=run(5,3,2,mark,white,false);if(r)return r;}
    int r=growthBoundaries();if(r)return r;
    test_write("PASS\n",5);return 0;
}
