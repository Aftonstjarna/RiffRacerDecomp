#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_window_frame(Window*);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i];return d; }
static bool eq(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true; }
static bool str(const char* a,const char* b){while(*a && *a==*b){++a;++b;}return *a==*b;}
struct Scenario { unsigned loadOK, lookupOK; int32_t status,rectResult,top,frameTop; };
static Scenario s;
static unsigned trace[16], count, bad;
static Window* active;
static void event(unsigned v){if(count<16)trace[count++]=v;else bad=1;}
static int32_t WF_STDCALL query(uint32_t h,uint32_t attr,void* p,uint32_t bytes) {
 event(4); if(h!=active->secondaryWindow||attr!=9||bytes!=16)bad=1;
 Rect* r=(Rect*)p; r->left=11;r->top=s.frameTop;r->right=22;r->bottom=33;return s.status;
}
static uint32_t WF_STDCALL load(const char* p){event(1);if(!str(p,"dwmapi.dll"))bad=1;return s.loadOK?0x76543210u:0;}
static FrameQuery WF_STDCALL lookup(uint32_t m,const char* p){event(2);if(m!=0x76543210u||!str(p,"DwmGetWindowAttribute"))bad=1;return s.lookupOK?query:0;}
static int32_t WF_STDCALL release(uint32_t m){event(5);if(m!=0x76543210u)bad=1;return 0;}
static int32_t WF_STDCALL rect(uint32_t h,Rect* r){event(3);if(h!=active->secondaryWindow)bad=1;r->left=-12;r->top=s.top;r->right=190;r->bottom=120;return s.rectResult;}
// Local linker places this data at the original import/string/cookie addresses.
// These are data fixtures, not executable trampolines or original code bytes.
unsigned char oracle_iat[0x528] __attribute__((section(".oracle_iat"),aligned(4)))={0};
char oracle_names[0x70] __attribute__((section(".oracle_names"),aligned(1)))={0};
uint32_t oracle_cookie __attribute__((section(".oracle_cookie"),aligned(4)))=0x12345678;
static void reset(Window* w){active=w;count=bad=0;for(unsigned i=0;i<16;++i)trace[i]=0;}
extern "C" int test_main(){
 FrameApi api={load,lookup,release,rect};
 bool mapped=(uint32_t)oracle_iat==0x92d000u && (uint32_t)oracle_names==0x9fbd50u && (uint32_t)&oracle_cookie==0xbaabc0u;
 if(mapped){
  *(decltype(api.load)*)(oracle_iat+0xdc)=load;
  *(decltype(api.lookup)*)(oracle_iat+0xe0)=lookup;
  *(decltype(api.release)*)(oracle_iat+0xe4)=release;
  *(decltype(api.windowRect)*)(oracle_iat+0x524)=rect;
  const char* name="DwmGetWindowAttribute";for(unsigned i=0;i<21;++i)oracle_names[i]=name[i];
  name="dwmapi.dll";for(unsigned i=0;i<11;++i)oracle_names[0x64+i]=name[i];
 }
 const uint32_t edges[]={0,1,7,0x7fffffffu,0x80000000u,0xffffffffu};
 unsigned cases=0;
 for(unsigned l=0;l<2;++l)for(unsigned k=0;k<2;++k)
 for(unsigned st=0;st<4;++st)for(unsigned rr=0;rr<2;++rr)
 for(unsigned a=0;a<6;++a)for(unsigned b=0;b<6;++b)for(unsigned o=0;o<6;++o){
  s.loadOK=l;s.lookupOK=k;s.status=st==0?0:st==1?1:st==2?-1:(int32_t)0x80000000u;
  s.rectResult=rr;s.top=(int32_t)edges[a];s.frameTop=(int32_t)edges[b];
  struct Fixture {uint32_t before[4]; Window w;uint32_t after[4];} initial,x,y;
  unsigned char* p=(unsigned char*)&initial;for(unsigned i=0;i<sizeof(initial);++i)p[i]=(unsigned char)(i*37+cases);
  initial.w.secondaryWindow=0x87654321u; initial.w.verticalOffset=edges[o];x=initial;y=initial;
  reset(&x.w);x.w.frameWithApi(api);
  unsigned delta=edges[a]-edges[b];
  if(l&&k&&s.status>=0&&delta&&delta<0x80000000u)initial.w.verticalOffset+=delta;
  if(!eq(&x,&initial,sizeof(x))||bad)return 1;
  unsigned expected[]={1,2,3,4,5};unsigned n=l?(k?5:3):1;
  if(l&&!k){expected[2]=5;}
  if(count!=n||!eq(trace,expected,n*4))return 2;
  if(mapped){
   reset(&y.w);original_window_frame(&y.w);
   if(bad||count!=n||!eq(trace,expected,n*4)||!eq(&x,&y,sizeof(x)))return 3;
   y=initial; y.w.verticalOffset=edges[o]; reset(&y.w);y.w.frame();
   if(bad||count!=n||!eq(trace,expected,n*4)||!eq(&x,&y,sizeof(x)))return 4;
  }
  ++cases;
 }
 if(mapped)test_write("PASS: 6912 direct original comparisons\n",sizeof("PASS: 6912 direct original comparisons\n")-1);
 else test_write("PASS: C++ checks; oracle requires fixed data mappings\n",sizeof("PASS: C++ checks; oracle requires fixed data mappings\n")-1);
 return 0;
}
