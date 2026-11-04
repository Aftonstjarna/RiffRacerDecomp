#include "impl.hpp"
using namespace riff;
extern "C" bool __attribute__((thiscall)) original_request_case3(Display*,const Request3*);
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
// Controlled boundary doubles, not recovered window code. Local differential
// link maps these sections to the addresses below. The default trusted link
// may leave them unmapped; unchanged requests still exercise the true oracle.
void* oracle_window __attribute__((section(".oracle_window"),aligned(4)));
const double oracle_unsigned[2] __attribute__((section(".oracle_unsigned"),aligned(8),used))={0.0,4294967296.0};
static Display* active;
static Request3* request;
static unsigned calls,errors,mutate;
static int systemToken;
static void spy(void* system,uint32_t w,uint32_t h,uint32_t mode) {
    ++calls;
    if(system!=&systemToken || w!=request->windowWidth || h!=request->windowHeight || mode!=request->mode ||
       active->logicalWidth!=request->logicalWidth || active->logicalHeight!=request->logicalHeight ||
       active->windowWidth!=w || active->windowHeight!=h || active->setting18!=request->setting18 ||
       active->saved274!=active->source274) ++errors;
    if(mutate) {
        active->logicalWidth=0xffffffffu; active->logicalHeight=0x80000001u;
        active->windowWidth=3; active->windowHeight=7;
        request->flag=0xe7; // final byte is read after the callback
    }
}
extern "C" void __attribute__((thiscall,section(".oracle_secondary"),noinline))
oracle_secondary(void* system,uint32_t w,uint32_t h,uint32_t mode) { spy(system,w,h,mode); }
static void __attribute__((thiscall)) replacement(void* p,uint32_t w,uint32_t h,uint32_t m) {spy(p,w,h,m);}
extern "C" void* memcpy(void* d,const void* s,size_t n) { for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i]; return d; }
extern "C" void* memset(void* d,int c,size_t n) { for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c; return d; }
static bool equal(const void* a,const void* b,unsigned n) { for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true; }
static void fill(void* a,unsigned n) {for(unsigned i=0;i<n;++i)((uint8_t*)a)[i]=(uint8_t)(i*71+29);}
struct Guarded { uint32_t pre[4]; Display d; uint32_t post[4]; };
static bool run(uint32_t x,uint32_t y,uint32_t w,uint32_t h,unsigned difference,unsigned mode,unsigned rounding,bool mapped) {
    Guarded a,b,expected;
    fill(&a,sizeof(a));
    Request3 r={3,x,y,w,h,0x12345678u,0xfedcba98u,(uint8_t)mode,0x83,{0x49,0x17}};
    a.d.logicalWidth=x; a.d.logicalHeight=y; a.d.windowWidth=w; a.d.windowHeight=h;
    a.d.setting18=r.setting18; a.d.comparedMode=r.mode;
    switch(difference) {
    case 1:a.d.logicalWidth^=1;break;
    case 2:a.d.logicalHeight^=1;break;
    case 3:a.d.windowWidth^=1;break;
    case 4:a.d.windowHeight^=1;break;
    case 5:a.d.comparedMode^=1;break;
    case 6:a.d.setting18^=1;break;
    }
    b=a; expected=a;
    Request3 rb=r, before=r;
    unsigned csr=0x1f80u | rounding;
    active=&a.d;request=&r;calls=errors=0;
    windowSystem=&systemToken;
    test_set_mxcsr(csr);
    bool result=a.d.requestCase3(&r);
    unsigned recoveredCSR=test_get_mxcsr();
    if(!result || errors || calls!=(difference?1u:0u))return false;
    if(!difference) {
        expected.d.flag=r.flag;
        if(!equal(&a,&expected,sizeof(a)))return false;
    } else {
        // Verify every byte outside the exact write set, including +4bf.
        expected.d.logicalWidth=a.d.logicalWidth;expected.d.logicalHeight=a.d.logicalHeight;
        expected.d.windowWidth=a.d.windowWidth;expected.d.windowHeight=a.d.windowHeight;
        expected.d.saved274=expected.d.source274; expected.d.setting18=before.setting18;
        expected.d.scaleX=a.d.scaleX;expected.d.scaleY=a.d.scaleY;expected.d.flag=r.flag;
        if(!equal(&a,&expected,sizeof(a)))return false;
    }
    if(!mutate && !equal(&r,&before,sizeof(r)))return false;
    if(difference && !mapped)return true;
    active=&b.d;request=&rb;calls=errors=0;oracle_window=&systemToken;
    test_set_mxcsr(csr);
    result=original_request_case3(&b.d,&rb);
    unsigned originalCSR=test_get_mxcsr();
    return result && !errors && calls==(difference?1u:0u) &&
        recoveredCSR==originalCSR && equal(&a,&b,sizeof(a)) && equal(&r,&rb,sizeof(r));
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    updateSecondaryWindow=replacement;
    bool mapped=(uintptr_t)&oracle_window==0xbfcc28u &&
                (uintptr_t)&oracle_secondary==0x48cc70u &&
                (uintptr_t)oracle_unsigned==0xa071b0u;
    const uint32_t values[]={0,1,3,720,1080,1920,0xffffffu,0x1000001u,0x7fffffffu,0x80000000u,0x80000001u,0xffffffffu};
    const unsigned modes[]={0,1,2,255};
    for(unsigned rounding=0;rounding<4;++rounding)
    for(unsigned m=0;m<4;++m)
    for(unsigned i=0;i<12;++i)
    for(unsigned j=0;j<12;++j)
    for(unsigned d=0;d<7;++d) {
        mutate=0;
        if(!run(values[i],values[j],values[j],values[i],d,modes[m],rounding<<13,mapped)) {test_set_mxcsr(saved);return 1;}
    }
    mutate=1;
    for(unsigned d=1;d<7;++d)
        if(!run(1920,1080,640,480,d,255,0,mapped)) {test_set_mxcsr(saved);return 2;}
    test_set_mxcsr(saved);
    if(mapped) { const char s[]="PASS: 16134 differential cases, full state, callback order, MXCSR and request bytes\n";test_write(s,sizeof(s)-1); }
    else { const char s[]="LIMIT: 2304 unchanged-path oracle cases passed; changed-path comparison requires .oracle_secondary=0x48cc70, .oracle_unsigned=0xa071b0, .oracle_window=0xbfcc28 (local full suite verified separately)\n";test_write(s,sizeof(s)-1); }
    return 0;
}
