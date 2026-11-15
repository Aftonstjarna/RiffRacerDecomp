#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_stack_push_terminated(State*,const char*);
// Custom original helper ABI: dummy EAX, EDX text, ECX state; caller pops length.
extern "C" void* __attribute__((regparm(3))) original_script_string_intern(unsigned,const char*,State*,uint32_t);
extern "C" void __attribute__((fastcall)) original_script_stack_resize(State*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n){for(unsigned i=0;i<n;++i)((unsigned char*)d)[i]=((const unsigned char*)s)[i];return d;}
extern "C" void* memset(void* d,int c,unsigned n){for(unsigned i=0;i<n;++i)((unsigned char*)d)[i]=(unsigned char)c;return d;}
static bool same(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i])return false;return true;}
static State state;
static unsigned char globals[128], oldStack[1024], newStack[1024];
static uint32_t buckets[8];
struct Node {Node* next;uint8_t type,mark,pad[2];uint32_t hash,length;char text[160];};
static Node node,collision;
static char input[160];
static unsigned calls,bad,oldSeen,newSeen;
static bool inPlace,mutate;
static void* allocator(void* ud,void* p,uint32_t oldN,uint32_t newN){
    ++calls; oldSeen=oldN;newSeen=newN;
    if(ud!=globals||p!=oldStack||oldN>1024||newN>1024)bad=1;
    // The value must already be published before any stack growth.
    Slot* v=(Slot*)(oldStack+16);
    if(v->payload!=(uint32_t)(uintptr_t)&node||v->tag!=4)bad=1;
    void* result=inPlace?(void*)oldStack:(void*)newStack;
    if(oldN<=1024&&newN<=1024)memcpy(result,p,oldN<newN?oldN:newN);
    if(mutate)state.top=(Slot*)(oldStack+32);
    return result;
}
static void* intern(State* s,const char* p,uint32_t n){void* r=original_script_string_intern(0,p,s,n);if(test_get_fs_head()!=0xffffffffu)bad=1;return r;}
static void resize(State* s,uint32_t n){original_script_stack_resize(s,n);if(test_get_fs_head()!=0xffffffffu)bad=1;}
static const PushServices services={intern,resize};
static uint32_t hashText(unsigned n){uint32_t h=n;unsigned step=(n>>5)+1;for(unsigned i=n;i>=step;i-=step)h^=(h<<5)+(h>>2)+(uint8_t)input[i-1];return h;}
static void setup(unsigned len,int gap,uint32_t capacity,unsigned mark,unsigned white){
    memset(&state,0xa5,sizeof state);memset(globals,0,sizeof globals);memset(&node,0x61,sizeof node);memset(&collision,0x72,sizeof collision);
    for(unsigned i=0;i<1024;++i){oldStack[i]=(unsigned char)(i*7+11);newStack[i]=0xcc;}
    for(unsigned i=0;i<160;++i)input[i]=(char)(33+i%90);
    input[len]=0; if(len+1<160)input[len+1]='Z';
    node.next=0;node.type=4;node.mark=(uint8_t)mark;node.length=len;node.hash=hashText(len);memcpy(node.text,input,len+1);
    collision.next=&node;collision.length=len+1;
    for(unsigned i=0;i<8;++i)buckets[i]=0;
    buckets[node.hash&7]=(uint32_t)(uintptr_t)&collision;
    *(void***)(globals)= (void**)buckets;*(uint32_t*)(globals+4)=2;*(uint32_t*)(globals+8)=8;
    *(void**)(globals+12)=(void*)&allocator;*(void**)(globals+16)=globals;globals[20]=(uint8_t)white;*(uint32_t*)(globals+68)=1000;
    state.global=globals;state.stack=oldStack;state.top=(Slot*)(oldStack+16);state.base=oldStack+8;
    state.stackLimit=(void*)((uintptr_t)(oldStack+16)+(uint32_t)gap);state.stackCapacity=capacity;state.openUpvalues=0;
    state.firstFrame=(void*)24;state.currentFrame=0; // Empty inclusive frame range.
    calls=bad=oldSeen=newSeen=0;
}
struct Snapshot {State s;unsigned char g[128],a[1024],b[1024];Node n,c;uint32_t buckets[8];unsigned calls,oldN,newN;};
static void capture(Snapshot& x){x.s=state;memcpy(x.g,globals,128);memcpy(x.a,oldStack,1024);memcpy(x.b,newStack,1024);x.n=node;x.c=collision;memcpy(x.buckets,buckets,32);x.calls=calls;x.oldN=oldSeen;x.newN=newSeen;}
static int run(unsigned len,int gap,uint32_t cap,unsigned mark,unsigned white){
    setup(len,gap,cap,mark,white);State before=state;Node previous=node;unsigned char beforeG[128];memcpy(beforeG,globals,128);
    original_script_stack_push_terminated(&state,input);
    if(bad||test_get_fs_head()!=0xffffffffu)return 1;
    bool grow=gap<=8;uint32_t request=cap<1?cap+1:cap*2;
    if(calls!=(grow?1u:0u)|| (grow&&(oldSeen!=cap*8||newSeen!=(request+6)*8)))return 2;
    unsigned char* dest=grow&&!inPlace?newStack:oldStack;
    State expected=before;expected.top=(Slot*)(dest+(grow&&mutate?40:24));
    if(grow){expected.stack=dest;expected.stackLimit=dest+request*8;expected.stackCapacity=request+6;expected.base=dest+8;*(uint32_t*)(beforeG+68)+=newSeen-oldSeen;}
    if(!same(&state,&expected,sizeof state)||!same(globals,beforeG,128))return 3;
    if(((Slot*)(oldStack+16))->payload!=(uint32_t)(uintptr_t)&node||((Slot*)(oldStack+16))->tag!=4)return 4;
    if(grow&&!inPlace&&oldSeen>=24 && (((Slot*)(dest+16))->payload!=(uint32_t)(uintptr_t)&node||((Slot*)(dest+16))->tag!=4))return 4;
    if(((~white)&(mark&3))!=0)previous.mark^=3;
    if(!same(&node,&previous,sizeof node))return 5;
    Snapshot oracle;capture(oracle);
    setup(len,gap,cap,mark,white);state.pushTerminated(input,services);
    Snapshot recovered;capture(recovered);
    if(bad||!same(&oracle,&recovered,sizeof oracle))return 6;
    // Input and bytes after its first NUL must be untouched.
    for(unsigned i=0;i<160;++i){char expectedByte=i==len?0:(i==len+1?'Z':(char)(33+i%90));if(input[i]!=expectedByte)return 7;}
    return 0;
}
// Source-only boundary probes isolate helper contracts: interning may change top,
// but publication must use the captured slot. Signed extreme capacities cannot
// safely be driven through the real allocation/error helpers with small storage.
static unsigned phase,expectedLength;static uint32_t wanted;static bool growProbe;
static void* boundaryIntern(State* s,const char* p,uint32_t n){
    if(phase++!=0||s!=&state||p!=input||n!=expectedLength)bad=1;
    s->top=(Slot*)(oldStack+40);
    s->stackLimit=(void*)((uintptr_t)s->top+(growProbe?8:9));
    return &node;
}
static void boundaryResize(State* s,uint32_t n){
    if(phase++!=1||s!=&state||n!=wanted||((Slot*)(oldStack+16))->tag!=4||((Slot*)(oldStack+16))->payload!=(uint32_t)(uintptr_t)&node)bad=1;
    s->top=(Slot*)(newStack+64);
}
static int boundaries(){
    const PushServices hooks={boundaryIntern,boundaryResize};
    const uint32_t caps[]={0,1,2,0x7fffffffu,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<6;++i)for(unsigned b=0;b<2;++b){
        setup(5,128,caps[i],0,0);phase=0;expectedLength=5;growProbe=b!=0;
        wanted=(caps[i]==0||caps[i]>=0x80000000u)?caps[i]+1:caps[i]*2;
        state.pushTerminated(input,hooks);
        if(bad||phase!=(b?2u:1u)||state.top!=(Slot*)(b?newStack+72:oldStack+48)||((Slot*)(oldStack+16))->payload!=(uint32_t)(uintptr_t)&node||((Slot*)(oldStack+16))->tag!=4)return 8;
    }
    return 0;
}
extern "C" int test_main(){
    static unsigned fs[8];fs[0]=0xffffffffu;if(test_install_fs(fs)!=0)return 10;
    const unsigned lengths[]={0,1,2,3,4,5,31,32,33,63,127};
    const int gaps[]={-2147483647-1,-8,0,7,8,9,16,128,2147483647};const unsigned caps[]={0,1,2,16};
    for(unsigned l=0;l<11;++l)for(unsigned g=0;g<9;++g)for(unsigned c=0;c<4;++c)for(unsigned bits=0;bits<16;++bits){
        inPlace=(bits&1)!=0;mutate=(bits&2)!=0;
        int r=run(lengths[l],gaps[g],caps[c],bits*17,(bits>>2)&3);if(r)return r;
    }
    int boundaryResult=boundaries();if(boundaryResult)return boundaryResult;
    test_write("PASS\n",5);return 0;
}
