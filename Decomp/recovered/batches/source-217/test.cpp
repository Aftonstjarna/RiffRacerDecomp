#include "impl.hpp"
using namespace riff;
extern "C" bool __attribute__((thiscall)) original_request_case2(Display*,const Request*);
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void* memcpy(void*d,const void*s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void*d,int c,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c;return d;}
static bool eq(const void*a,const void*b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
static void fill(void*p,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)p)[i]=(uint8_t)(i*37+19);}
// Test-only fixed-address storage and ordinary C++ boundary doubles. These do
// not purport to recover Win32/D3D or the resource helpers. Local link positions:
// .b_release=4a6330 .b_restore=4a6560 .b_mode=48cb30 .b_resize=53d2d0
// .b_viewport=4a22e0 .b_finish=4a5b00 .cookie=baabc0 .iat=92d524
// .window=bfcc28 .resources=bfcd0c .unsigned=a071b0.
uint32_t oracle_cookie __attribute__((section(".cookie"),aligned(4)))=0x12345678;
Window* oracle_window __attribute__((section(".window"),aligned(4)));
void* oracle_resources __attribute__((section(".resources"),aligned(4)));
const double oracle_unsigned[2] __attribute__((section(".unsigned"),aligned(8),used))={0.0,4294967296.0};
static int32_t RR_STDCALL getRect(uint32_t,Rect*);
typedef int32_t (RR_STDCALL *GetRect)(uint32_t,Rect*);
GetRect oracle_iat __attribute__((section(".iat"),aligned(4)))=getRect;
struct Guarded {uint32_t pre[4];Display d;uint32_t post[4];};
struct Event {uint32_t id,a,b,c;Guarded state;Window window;Request request;};
static Guarded fixture;
static Window windowState;
static Request request;
static Device device;
static DeviceVtable vtable;
static Window* windowSlot;
static void* resourceSlot;
static uint32_t resourceToken;
static Event trace[16],savedTrace[16];
static unsigned count,resetCalls,mutation,errors,path;
static int32_t resetResult,rollbackResult;
static bool restoreResult;
static void event(unsigned id,uint32_t a=0,uint32_t b=0,uint32_t c=0){
 if(count>=16){++errors;return;}
 Event& e=trace[count++];e.id=id;e.a=a;e.b=b;e.c=c;
 e.state=fixture;e.window=windowState;e.request=request;
}
extern "C" void __attribute__((thiscall,section(".b_release"),noinline)) releaseBoundary(Display*d){
 if(d!=&fixture.d)++errors;
 event(1);
 if(mutation&1){d->source274=91;d->presentation.format^=0x13579;d->saved274=313;}
}
static int32_t RR_STDCALL getRect(uint32_t h,Rect*r){
 event(2,h);r->left=-123;r->top=456;r->right=800;r->bottom=900;
 return 0; // original deliberately ignores failure status
}
static int32_t RR_STDCALL resetBoundary(Device*p,Presentation*pp){
 if(p!=&device || pp!=&fixture.d.presentation)++errors;
 event(3);++resetCalls;
 if(mutation&2){pp->width+=7;pp->height^=0x81;pp->interval^=0x55;fixture.d.source274+=13;}
 return resetCalls==1 ? resetResult : rollbackResult;
}
extern "C" void __attribute__((thiscall,section(".b_resize"),noinline)) resizeBoundary(void*p,uint32_t w,uint32_t h){
 if(p!=&resourceToken)++errors;
 event(4,w,h);
 if(mutation&4){fixture.d.width+=11;fixture.d.samples^=0x13;fixture.d.source274+=3;}
}
extern "C" bool __attribute__((thiscall,section(".b_restore"),noinline)) restoreBoundary(Display*d){
 if(d!=&fixture.d)++errors;
 event(5);
 if(mutation&8){d->width=0xffffffff;d->height=0x80000001;d->backWidth=3;d->backHeight=7;d->unknown278[1]^=0x55;}
 return restoreResult;
}
extern "C" void __attribute__((thiscall,section(".b_mode"),noinline)) modeBoundary(Window*p,uint32_t w,uint32_t h,uint32_t m){
 if(p!=&windowState)++errors;
 event(6,w,h,m);
 if(mutation&16){fixture.d.width=0x80000001;fixture.d.backWidth=7;request.fullscreen=0xe7;request.flag=0xb3;}
}
extern "C" void __attribute__((thiscall,section(".b_viewport"),noinline)) viewportBoundary(Display*d,uint32_t w,uint32_t h){
 if(d!=&fixture.d)++errors;
 event(7,w,h);
 if(mutation&32){request.flag=0xe1;d->source274^=17;}
}
extern "C" void __attribute__((thiscall,section(".b_finish"),noinline)) finishBoundary(Display*d){
 if(d!=&fixture.d)++errors;
 event(8);
 if(mutation&64){d->flag^=0x81;d->unknown4ac[3]^=0x51;}
}
static void initialize(uint32_t x,uint32_t y,uint32_t bw,uint32_t bh,uint32_t s,unsigned m,unsigned diff){
 fill(&fixture,sizeof(fixture));fill(&windowState,sizeof(windowState));fill(&request,sizeof(request));
 device.vtable=&vtable;fixture.d.device=&device;
 request.kind=2;request.width=x;request.height=y;request.backWidth=bw;request.backHeight=bh;
 request.samples=s;request.fullscreen=(uint8_t)m;request.flag=0x83;
 fixture.d.width=x;fixture.d.height=y;fixture.d.backWidth=bw;fixture.d.backHeight=bh;
 fixture.d.samples=s;fixture.d.fullscreen=(uint8_t)m;fixture.d.source274=60;
 switch(diff){case 1:fixture.d.width^=1;break;case 2:fixture.d.height^=1;break;
 case 3:fixture.d.backWidth^=1;break;case 4:fixture.d.backHeight^=1;break;
 case 5:fixture.d.fullscreen^=1;break;case 6:fixture.d.samples^=1;break;}
 windowSlot=oracle_window=&windowState;resourceSlot=oracle_resources=&resourceToken;
 count=errors=resetCalls=0;memset(trace,0,sizeof(trace));
}
static unsigned cases;
static bool run(uint32_t x,uint32_t y,uint32_t bw,uint32_t bh,uint32_t s,unsigned m,unsigned diff,unsigned rounding,bool mapped){
 initialize(x,y,bw,bh,s,m,diff);
 Guarded initial=fixture;Window initialWindow=windowState;Request initialRequest=request;
 test_set_mxcsr(0x1f80|(rounding<<13));
 bool result=fixture.d.requestCase2(&request);
 unsigned csr=test_get_mxcsr();
 if(errors || result!=(!diff || path==0))return false;
 // Independent expected ordinary call sequence and full write footprint.
 if(!mutation){
  unsigned ids[9],n=0;
  if(diff){ids[n++]=1;if(!initial.d.fullscreen)ids[n++]=2;ids[n++]=3;
   if(path==1)ids[n++]=6;
   else{ids[n++]=4;ids[n++]=5;if(path==2){ids[n++]=3;ids[n++]=4;}else{ids[n++]=6;ids[n++]=7;ids[n++]=8;}}
  }
  if(count!=n)return false;
  for(unsigned i=0;i<n;++i)if(trace[i].id!=ids[i])return false;
  Guarded expected=initial;
  if(!diff)expected.d.flag=request.flag;
  else if(path==0){
   expected.d.presentation.width=bw;expected.d.presentation.height=bh;
   expected.d.presentation.samples=(s>=2&&s<=16)?s:0;
   expected.d.presentation.quality=0;expected.d.presentation.windowed=m?0:1;
   expected.d.presentation.refreshRate=m?60:0;
   expected.d.width=x;expected.d.height=y;expected.d.backWidth=bw;expected.d.backHeight=bh;
   expected.d.saved274=60;expected.d.samples=s;expected.d.fullscreen=(uint8_t)m;
   expected.d.scaleX=fixture.d.scaleX;expected.d.scaleY=fixture.d.scaleY;expected.d.flag=request.flag;
  }
  if(!eq(&expected,&fixture,sizeof(fixture)) || !eq(&initialRequest,&request,sizeof(request)))return false;
  Window expectedWindow=initialWindow;
  if(diff&&!initial.d.fullscreen){expectedWindow.savedX=-123;expectedWindow.savedY=456;}
  if(!eq(&windowState,&expectedWindow,sizeof(windowState)))return false;
 }
 Guarded final=fixture;Window finalWindow=windowState;Request finalRequest=request;
 unsigned expectedCount=count;memcpy(savedTrace,trace,sizeof(trace));
 if(mapped){
  initialize(x,y,bw,bh,s,m,diff);test_set_mxcsr(0x1f80|(rounding<<13));
  bool originalResult=original_request_case2(&fixture.d,&request);
  unsigned originalCsr=test_get_mxcsr();
  if(errors || result!=originalResult || csr!=originalCsr || count!=expectedCount ||
     !eq(trace,savedTrace,sizeof(trace)) || !eq(&fixture,&final,sizeof(fixture)) ||
     !eq(&windowState,&finalWindow,sizeof(windowState)) || !eq(&request,&finalRequest,sizeof(request)))return false;
 }
 ++cases;return true;
}
extern "C" int test_main(){
 unsigned oldCsr=test_get_mxcsr();
 RequestBoundaries originalBindings=boundaries;
 vtable.reset=resetBoundary;
 RequestBoundaries api={&windowSlot,&resourceSlot,releaseBoundary,getRect,modeBoundary,resizeBoundary,restoreBoundary,viewportBoundary,finishBoundary};
 boundaries=api;
 bool mapped=(uintptr_t)&oracle_cookie==0xbaabc0 && (uintptr_t)&oracle_window==0xbfcc28 &&
  (uintptr_t)&oracle_resources==0xbfcd0c && (uintptr_t)&oracle_iat==0x92d524 &&
  (uintptr_t)oracle_unsigned==0xa071b0 && (uintptr_t)&releaseBoundary==0x4a6330 &&
  (uintptr_t)&restoreBoundary==0x4a6560 && (uintptr_t)&modeBoundary==0x48cb30 &&
  (uintptr_t)&resizeBoundary==0x53d2d0 && (uintptr_t)&viewportBoundary==0x4a22e0 && (uintptr_t)&finishBoundary==0x4a5b00;
 const uint32_t values[]={0,1,3,720,1920,0xffffff,0x1000001,0x7fffffff,0x80000000,0x80000001,0xffffffff};
 const uint32_t sampleValues[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,0x80000000,0xffffffff};
 const unsigned modes[]={0,1,2,255};
 mutation=0;
 for(path=0;path<3;++path){resetResult=path==1?(int32_t)0x88760868u:0;restoreResult=path!=2;rollbackResult=-1;
  for(unsigned r=0;r<4;++r)for(unsigned m=0;m<4;++m)for(unsigned i=0;i<11;++i)for(unsigned j=0;j<11;++j)for(unsigned d=0;d<7;++d)
   if(!run(values[i],values[j],values[j],values[i],sampleValues[(i+j)%20],modes[m],d,r,mapped)){test_set_mxcsr(oldCsr);return 1;}
  for(unsigned s=0;s<20;++s)for(unsigned m=0;m<4;++m)
   if(!run(1920,1080,1280,720,sampleValues[s],modes[m],6,0,mapped)){test_set_mxcsr(oldCsr);return 2;}
 }
 for(path=0;path<3;++path)for(mutation=1;mutation<128;++mutation){
  resetResult=path==1?-1:1;restoreResult=path!=2;rollbackResult=(mutation&1)?-1:1;
  for(unsigned m=0;m<4;++m)for(unsigned d=1;d<7;++d)
   if(!run(1920,1080,1280,720,16,modes[m],d,mutation%4,mapped)){test_set_mxcsr(oldCsr);return 3;}
 }
 // Also test the implementation's default original-address bindings, including
 // its indirect IAT call, instead of only the portable dependency bindings.
 if(mapped){
  boundaries=originalBindings;
  for(path=0;path<3;++path)for(unsigned r=0;r<4;++r)for(unsigned m=0;m<4;++m)for(unsigned d=0;d<7;++d){
   mutation=(r&1)?127:0;resetResult=path==1?-1:0;restoreResult=path!=2;rollbackResult=-1;
   if(!run(1920,1080,1280,720,17,modes[m],d,r,true)){test_set_mxcsr(oldCsr);return 5;}
  }
 }
 test_set_mxcsr(oldCsr);
 if(cases!=(mapped?50376u:50040u)){test_write("case count mismatch\n",20);return 4;}
 if(mapped)test_write("PASS: 50376 full original differential cases, state, trace, request, MXCSR\n",sizeof("PASS: 50376 full original differential cases, state, trace, request, MXCSR\n")-1);
 else test_write("LIMIT: portable checks passed; original differential tests require fixed boundary/data section mappings documented in test.cpp\n",sizeof("LIMIT: portable checks passed; original differential tests require fixed boundary/data section mappings documented in test.cpp\n")-1);
 return 0;
}
