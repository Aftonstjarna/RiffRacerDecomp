#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((regparm(3))) original_script_hook_dispatch(unsigned,uint32_t,State*,uint32_t);
extern "C" void __attribute__((fastcall)) original_script_stack_resize(State*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" { __attribute__((section(".oracle_cookie"),used,aligned(4))) uint32_t cookie=0x12345678; }
extern "C" void* memcpy(void* d,const void* s,unsigned n){for(unsigned i=0;i<n;++i)((char*)d)[i]=((const char*)s)[i];return d;}
extern "C" void* memset(void* d,int c,unsigned n){for(unsigned i=0;i<n;++i)((char*)d)[i]=(char)c;return d;}
static bool equal(const void* a,const void* b,unsigned n){for(unsigned i=0;i<n;++i)if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i])return false;return true;}
static State s; static Frame frames[4]; static unsigned char oldStack[1024],newStack[1024],globals[128];
static unsigned calls,allocCalls,bad,seenEvent,seenArgument; static int seenIndex; static uint32_t seenOld,seenNew; static bool moving,changeFrame,invokeOriginal; static unsigned char seenEnabled; static void* seenLimit;
static void* allocator(void* ud,void* p,uint32_t oldN,uint32_t newN){++allocCalls;seenOld=oldN;seenNew=newN;if(ud!=globals||p!=oldStack||oldN>1024||newN>1024)bad=1;void* dest=moving?(void*)newStack:(void*)oldStack;if(oldN<=1024&&newN<=1024)memcpy(dest,p,oldN<newN?oldN:newN);return dest;}
static void resize(State* state,uint32_t n){original_script_stack_resize(state,n);if(test_get_fs_head()!=0xffffffffu)bad=1;}
static void callback(State* state,HookRecord* r){++calls;seenEvent=r->event;seenArgument=r->argument;seenIndex=r->frameIndex;seenEnabled=state->hookEnabled;seenLimit=state->currentFrame->limit;
 if(invokeOriginal){original_script_hook_dispatch(0,99,state,88);if(test_get_fs_head()!=0xffffffffu)bad=1;}else state->dispatchHook(99,88,resize);
 state->top=(char*)state->stack+120;state->currentFrame->limit=(char*)state->stack+128;state->hookEnabled=7;
 if(changeFrame)state->currentFrame=&frames[3];
}
static void setup(int gap,uint32_t capacity,unsigned mode){memset(&s,0xa5,sizeof s);memset(frames,0x5a,sizeof frames);memset(globals,0,sizeof globals);for(unsigned i=0;i<1024;++i){oldStack[i]=(unsigned char)(i*7+3);newStack[i]=0xcc;}
 *(void**)(globals+12)=(void*)&allocator;*(void**)(globals+16)=globals;*(uint32_t*)(globals+68)=1000;
 s.global=globals;s.stack=oldStack;s.top=oldStack+40;s.base=oldStack+8;s.stackLimit=(void*)((uintptr_t)s.top+(uint32_t)gap);s.stackCapacity=capacity;s.firstFrame=&frames[0];s.currentFrame=&frames[2];s.openUpvalues=0;s.hook=(mode&1)?0:callback;s.hookEnabled=(mode&2)?0:3;
 for(unsigned i=0;i<4;++i){frames[i].unknown00[0]=(uint32_t)(uintptr_t)(oldStack+i*8);frames[i].unknown00[1]=(uint32_t)(uintptr_t)(oldStack+16+i*8);frames[i].limit=oldStack+80+i*8;}
 calls=allocCalls=bad=seenEvent=seenArgument=seenOld=seenNew=0;seenIndex=0;seenEnabled=0;seenLimit=0;
}
struct Snapshot {State state;Frame f[4];unsigned char a[1024],b[1024],g[128];unsigned calls,allocCalls,bad,event,arg;int index;uint32_t oldN,newN;unsigned char enabled;void* limit;};
static void capture(Snapshot& x){memset(&x,0,sizeof x);x.state=s;memcpy(x.f,frames,sizeof frames);memcpy(x.a,oldStack,1024);memcpy(x.b,newStack,1024);memcpy(x.g,globals,128);x.calls=calls;x.allocCalls=allocCalls;x.bad=bad;x.event=seenEvent;x.arg=seenArgument;x.index=seenIndex;x.oldN=seenOld;x.newN=seenNew;x.enabled=seenEnabled;x.limit=seenLimit;}
extern "C" int test_main(){static uint32_t fs[8];fs[0]=0xffffffffu;if(test_install_fs(fs)!=0)return 1;
 const int gaps[]={-2147483647-1,-1,0,159,160,161,2147483647};const uint32_t caps[]={10,19,20,30};const uint32_t events[]={0,4,0xffffffffu};
 for(unsigned g=0;g<7;++g)for(unsigned c=0;c<4;++c)for(unsigned e=0;e<3;++e)for(unsigned mode=0;mode<4;++mode)for(unsigned bits=0;bits<4;++bits){moving=(bits&1)!=0;changeFrame=(bits&2)!=0;setup(gaps[g],caps[c],mode);State before=s;Frame beforeFrames[4];memcpy(beforeFrames,frames,sizeof frames);invokeOriginal=true;original_script_hook_dispatch(0,events[e],&s,0x87654321);if(test_get_fs_head()!=0xffffffffu||bad)return 2;
 bool active=mode==0;bool grow=active&&gaps[g]<=160;uint32_t req=caps[c]<20?caps[c]+20:caps[c]*2;
 if(calls!=(active?1u:0u)||allocCalls!=(grow?1u:0u))return 3;
 if(active&&(seenEvent!=events[e]||seenArgument!=0x87654321||seenIndex!=(events[e]==4?0:2)||seenEnabled!=0||seenLimit!=(moving&&grow?(void*)(newStack+200):(void*)(oldStack+200))))return 4;
 if(grow&&(seenOld!=caps[c]*8||seenNew!=(req+6)*8))return 5;
 if(!active&&(!equal(&s,&before,sizeof s)||!equal(frames,beforeFrames,sizeof frames)))return 6;
 if(active&&(s.hookEnabled!=1||s.top!=(grow&&moving?(void*)(newStack+40):(void*)(oldStack+40))||s.currentFrame->limit!=(grow&&moving?(void*)(newStack+96):(void*)(oldStack+96))))return 7;
 Snapshot oracle,result;capture(oracle);setup(gaps[g],caps[c],mode);invokeOriginal=false;s.dispatchHook(events[e],0x87654321,resize);capture(result);if(!equal(&oracle,&result,sizeof oracle))return 8;
 }
 // Non-aligned and negative frame offsets exercise signed division toward zero.
 const int offsets[]={-49,-25,-24,-23,-1,0,1,23,24,25,49};
 for(unsigned i=0;i<11;++i){setup(200,20,0);changeFrame=false;moving=false; s.firstFrame=(Frame*)((uintptr_t)s.currentFrame-(uint32_t)offsets[i]);invokeOriginal=true;original_script_hook_dispatch(0,3,&s,7);if(test_get_fs_head()!=0xffffffffu||seenIndex!=offsets[i]/24||bad)return 9;Snapshot oracle,result;capture(oracle);setup(200,20,0);s.firstFrame=(Frame*)((uintptr_t)s.currentFrame-(uint32_t)offsets[i]);invokeOriginal=false;s.dispatchHook(3,7,resize);capture(result);if(!equal(&oracle,&result,sizeof oracle))return 10;}
 test_write("PASS\n",5);return 0;}
