#include "impl.hpp"
using riff::State;
extern "C" void __attribute__((fastcall)) original_script_stack_resize(State*,uint32_t);
extern "C" void __attribute__((fastcall)) original_script_stack_relocate_pointers(State*,void*);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsStorage[8];
static const uint32_t fsSentinel=0xffffffffu;
struct Frame { void* function; void* top; void* base; uint32_t other[3]; };
struct Upvalue { Upvalue* next; uint32_t untouched; void* value; uint32_t more; };
static unsigned char oldStack[512], newStack[512], globalData[128];
static State s, before;
static Frame frames[3], frameBefore[3];
static Upvalue values[2], valueBefore[2];
static uint32_t calls, seenOld, seenNew;
static void* seenPointer;
static uint32_t failures;
static bool inPlace;
static void check(bool x) { if(!x) ++failures; }
extern "C" void* memcpy(void* a,const void* b,unsigned n) { unsigned char* d=(unsigned char*)a; const unsigned char* p=(const unsigned char*)b; for(unsigned i=0;i<n;++i)d[i]=p[i]; return a; }
extern "C" void* memset(void* a,int c,unsigned n) { unsigned char* p=(unsigned char*)a; for(unsigned i=0;i<n;++i)p[i]=(unsigned char)c; return a; }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* p=(const unsigned char*)a; const unsigned char* q=(const unsigned char*)b; for(unsigned i=0;i<n;++i)if(p[i]!=q[i])return false; return true; }
static void* allocator(void* ud,void* p,uint32_t oldSize,uint32_t newSize) {
    check(ud==globalData); ++calls; seenPointer=p; seenOld=oldSize; seenNew=newSize;
    void* dest=inPlace ? oldStack : newStack;
    // Controlled successful allocator: large boundary requests only record sizes.
    if(newSize<=512u) { unsigned count=oldSize<newSize?oldSize:newSize; if(count<=512)memcpy(dest,p,count); }
    return dest;
}
// Test-only successful-path binding. This is not a recovery of reallocate's
// failure/longjmp/panic behavior or its unusual ECX/EDX + caller-cleaned ABI.
static void* reallocate(State* state,void* p,uint32_t oldSize,uint32_t newSize) {
    void* out=allocator(globalData,p,oldSize,newSize);
    *(uint32_t*)(globalData+68)+=newSize-oldSize;
    check(state==&s); return out;
}
static void* tooLarge(State*) { ++failures; return 0; }
static void relocate(State* state,void* old) { original_script_stack_relocate_pointers(state,old); check(test_get_fs_head()==fsSentinel); }
static const riff::StackServices services={reallocate,tooLarge,relocate};
static void setup(bool linked,bool hasFrames) {
    memset(&s,0xa5,sizeof(s)); memset(globalData,0,sizeof(globalData));
    for(unsigned i=0;i<512;++i) {oldStack[i]=(unsigned char)(i*7+3);newStack[i]=0xcc;}
    *(void**)(globalData+12)=(void*)&allocator; *(void**)(globalData+16)=globalData;
    *(uint32_t*)(globalData+68)=1000;
    s.global=globalData; s.stack=oldStack; s.stackLimit=oldStack+80;
    s.stackCapacity=16; s.top=oldStack+40; s.base=oldStack+8;
    s.firstFrame=frames; s.currentFrame=hasFrames ? (void*)(frames+2) : (void*)((uintptr_t)frames-24);
    s.openUpvalues=linked ? values : 0;
    for(unsigned i=0;i<3;++i) { frames[i].function=oldStack+i*8;frames[i].top=oldStack+64+i*8;frames[i].base=oldStack+16+i*8; for(unsigned j=0;j<3;++j)frames[i].other[j]=0x87654321+i+j; }
    for(unsigned i=0;i<2;++i) {values[i].next=i?0:values+1;values[i].untouched=0x11223344+i;values[i].value=oldStack+24+i*8;values[i].more=0x55667788+i;}
    before=s; memcpy(frameBefore,frames,sizeof(frames)); memcpy(valueBefore,values,sizeof(values));
    calls=0; seenOld=seenNew=0; seenPointer=0;
}
static void validate(uint32_t request,bool linked,bool hasFrames) {
    unsigned char* dest=inPlace?oldStack:newStack;
    check(calls==1 && seenPointer==oldStack && seenOld==128 && seenNew==(request+6u)*8u);
    check(*(uint32_t*)(globalData+68)==1000u+seenNew-128u);
    State expected=before; expected.stack=dest;expected.stackCapacity=request+6u;
    expected.stackLimit=(void*)((uintptr_t)dest+request*8u);expected.top=dest+40;expected.base=dest+8;
    check(equal(&s,&expected,sizeof(s)));
    for(unsigned i=0;i<3;++i) { Frame e=frameBefore[i]; if(hasFrames){ e.function=dest+i*8;e.top=dest+64+i*8;e.base=dest+16+i*8; } check(equal(&frames[i],&e,sizeof(e))); }
    for(unsigned i=0;i<2;++i) {Upvalue e=valueBefore[i];if(linked)e.value=dest+24+i*8;check(equal(&values[i],&e,sizeof(e)));}
    for(unsigned i=0;i<512;++i)check(oldStack[i]==(unsigned char)(i*7+3));
    if(!inPlace && seenNew<=512) for(unsigned i=0;i<512;++i)check(newStack[i]==(i<(seenNew<128?seenNew:128)?(unsigned char)(i*7+3):0xcc));
}
extern "C" int test_main() {
    fsStorage[0]=fsSentinel;
    if(test_install_fs(fsStorage)!=0) {test_write("FS setup failed\n",16);return 1;}
    check(test_get_fs_head()==fsSentinel);
    // Guard's largest accepted ordinary input and modulo-wrap inputs are tested
    // without huge storage: the controlled allocator records sizes, never uses them.
    const uint32_t requests[]={0,1,10,16,32,0x1ffffff8u,0xfffffff9u,0xfffffffau,0xffffffffu};
    for(unsigned k=0;k<sizeof(requests)/sizeof(requests[0]);++k)
      for(unsigned bits=0;bits<8;++bits) {
        inPlace=(bits&1)!=0; bool linked=(bits&2)!=0, hasFrames=(bits&4)!=0;
        setup(linked,hasFrames); original_script_stack_resize(&s,requests[k]); check(test_get_fs_head()==fsSentinel); validate(requests[k],linked,hasFrames);
        State oracle=s;Frame of[3];Upvalue ov[2];unsigned char bytes[512];
        memcpy(of,frames,sizeof(of));memcpy(ov,values,sizeof(ov));memcpy(bytes,newStack,512);
        setup(linked,hasFrames); s.resizeStack(requests[k],services); validate(requests[k],linked,hasFrames);
        check(equal(&s,&oracle,sizeof(s)));check(equal(frames,of,sizeof(of)));check(equal(values,ov,sizeof(ov)));check(equal(newStack,bytes,512));
      }
    if(failures){test_write("FAIL\n",5);return 1;}test_write("PASS\n",5);return 0;
}
