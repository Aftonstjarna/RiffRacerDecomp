#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_viewport_size(Viewport*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
// These test-only dependencies must be placed at the original addresses by
// the local linker. They are controlled doubles, NOT recovered fitting code.
WindowOffsets* oracle_window __attribute__((section(".oracle_window"),aligned(4)));
static Viewport* active;
static uint32_t inputW,inputH,outputW,outputH;
static unsigned calls,errors;
static WindowOffsets destination;
static void fitSpy(uint32_t* w,uint32_t* h) {
    ++calls;
    if(*w!=inputW || *h!=inputH || w==h ||
       active->requestedWidth!=inputW || active->requestedHeight!=inputH)
        ++errors;
    *w=outputW; *h=outputH;
    // Confirms that the destination singleton is loaded after the call.
    window=&destination; oracle_window=&destination;
}
extern "C" void __attribute__((thiscall,section(".oracle_fit"),noinline)) oracle_fit(uint32_t* w,uint32_t* h) { fitSpy(w,h); }
static void fill(void* p,unsigned n) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i) b[i]=(unsigned char)(i*37+19); }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false; return true; }
struct Guarded { uint32_t before[4]; Viewport value; uint32_t after[4]; };
static int32_t signedBits(uint32_t h) { return h<0x80000000u ? (int32_t)h : -1-(int32_t)~h; }
static bool run(uint32_t w,uint32_t h,unsigned flag,bool mapped) {
    Guarded a,b,expected; fill(&a,sizeof(a)); a.value.fitEnabled=(uint8_t)flag;
    b=a; expected=a;
    inputW=w; inputH=h;
    expected.value.requestedWidth=w; expected.value.requestedHeight=h;
    expected.value.width=flag?outputW:w; expected.value.height=flag?outputH:h;
    expected.value.offsetX=flag?(w-outputW)>>1:0;
    expected.value.offsetY=flag?(h-outputH)>>1:0;
    expected.value.heightTenthMinusTwo=signedBits(expected.value.height)/10-2;
    WindowOffsets initial; fill(&initial,sizeof(initial)); destination=initial;
    calls=errors=0; active=&a.value; window=0; oracle_window=0;
    a.value.setSize(w,h);
    if(errors || calls!=(flag?1u:0u) || !equal(&a,&expected,sizeof(a))) return false;
    WindowOffsets wanted=initial;
    if(flag) { wanted.x=expected.value.offsetX; wanted.y=expected.value.offsetY; }
    if(!equal(&wanted,&destination,sizeof(wanted))) return false;
    if(flag && !mapped) return true;
    destination=initial; calls=errors=0; active=&b.value; oracle_window=0;
    original_viewport_size(&b.value,w,h);
    return !errors && calls==(flag?1u:0u) && equal(&a,&b,sizeof(a)) && equal(&wanted,&destination,sizeof(wanted));
}
extern "C" int test_main() {
    fitDimensions=fitSpy;
    bool mapped=(uintptr_t)&oracle_window==0xbfcc28u && (uintptr_t)&oracle_fit==0x4a1c30u;
    const uint32_t values[]={0,1,2,9,10,11,19,20,21,720,1080,1920,0x7fffffffu,0x80000000u,0x80000001u,0xfffffff6u,0xffffffffu};
    for(unsigned i=0;i<sizeof(values)/sizeof(values[0]);++i)
      for(unsigned j=0;j<sizeof(values)/sizeof(values[0]);++j) {
        if(!run(values[i],values[j],0,mapped)) return 1;
        for(unsigned mode=0;mode<4;++mode) {
            outputW=mode==0?values[i]:mode==1?values[i]/2:mode==2?values[i]+3:0xffffffffu;
            outputH=mode==0?values[j]:mode==1?values[j]/2:mode==2?values[j]+5:0x80000000u;
            if(!run(values[i],values[j],mode&1?255:1,mapped)) return 2;
        }
      }
    if(mapped) { const char s[]="PASS: original viewport differential, both paths with controlled fit dependency\n"; test_write(s,sizeof(s)-1); }
    else { const char s[]="PASS: original unfitted path; LIMIT: fitted oracle requires .oracle_fit=0x4a1c30 and .oracle_window=0xbfcc28\n"; test_write(s,sizeof(s)-1); }
    return 0;
}
extern "C" void* memcpy(void* to,const void* from,size_t n) { unsigned char* d=(unsigned char*)to; const unsigned char* s=(const unsigned char*)from; for(size_t i=0;i<n;++i) d[i]=s[i]; return to; }
extern "C" void* memset(void* to,int value,size_t n) { unsigned char* d=(unsigned char*)to; for(size_t i=0;i<n;++i) d[i]=(unsigned char)value; return to; }
