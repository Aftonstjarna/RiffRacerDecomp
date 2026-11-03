#include "impl.hpp"
using namespace riff;
extern "C" bool __attribute__((thiscall)) original_effect_target(Graphics*);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) {
    unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s;
    for(unsigned i=0;i<n;++i)a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d,int c,unsigned n) {
    unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)c;return d;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
// Fixed-address dependency fixtures. They are C++ test doubles, NOT accepted
// original helpers. The target and cookie-check are the only assembly oracles.
// An external test launcher must supply an i386 FS descriptor based at oracle_tls.
uint32_t oracle_tls[1024] __attribute__((section(".oracle_tls"),aligned(4096)))={0};
uint32_t oracle_cookie __attribute__((section(".oracle_cookie"),aligned(4)))=0x12345678;
FreeString oracle_free __attribute__((section(".oracle_free"),aligned(4)));
char oracle_texture_prefix[] __attribute__((section(".oracle_texture_prefix"),aligned(1)))=
    "Failed to create effect target texture. Error: ";
char oracle_surface_prefix[] __attribute__((section(".oracle_surface_prefix"),aligned(1)))=
    "Failed to get effect target surface from texture. Error: ";
static Graphics* active;
static int32_t createHR, surfaceHR;
static uint32_t formatValue;
static unsigned writeMask, nullMask, mutation, bad, count, oldHeap;
static char oldBuffer[128], descriptionBuffer[128], resultBuffer[256];
static Interface dev, texture, oldTexture, surface, oldSurface;
static void* deviceVT[24];static void* textureVT[19];
struct Event { unsigned id; Interface* t; Interface* s; uint32_t length, capacity; unsigned first; };
static Event events[16];
static void event(unsigned id) {
    if(count>=16){bad=1;return;}
    Event& x=events[count++];memset(&x,0,sizeof(x));x.id=id;
    x.t=active->effectTexture;x.s=active->effectSurface;
    x.length=active->lastError.length;x.capacity=active->lastError.capacity;
    x.first=(unsigned char)active->lastError.storage.small[0];
}
static unsigned copyText(char* d,const char* s) {unsigned n=0;while((d[n]=s[n])!=0)++n;return n;}
static void empty(NarrowString* s) {s->length=0;s->capacity=15;s->storage.small[0]=0;}
static void releaseA(void* p) {event(6);if(p!=oldBuffer)bad=1;}
static void releaseB(void* p) {event(7);if(p!=oldBuffer)bad=1;}
extern "C" NarrowString* __attribute__((fastcall,section(".oracle_describe"),noinline))
spy_describe(NarrowString* out,int32_t hr) {
    event(3);if(hr!=(createHR<0?createHR:surfaceHR))bad=1;
    memset(out,0,sizeof(*out));out->capacity=127;out->storage.heap=descriptionBuffer;
    out->length=copyText(descriptionBuffer,"synthetic HRESULT description");return out;
}
extern "C" NarrowString* __attribute__((section(".oracle_prefix"),noinline))
spy_prefix(NarrowString* out,const char* prefix,NarrowString* description) {
    event(4);
    const char* wanted=createHR<0?oracle_texture_prefix:oracle_surface_prefix;
    // Both adapters and original must pass exact original prefix addresses.
    if(prefix!=wanted || description->storage.heap!=descriptionBuffer || description->capacity!=127)bad=1;
    memset(out,0,sizeof(*out));out->capacity=255;out->storage.heap=resultBuffer;
    unsigned n=copyText(resultBuffer,prefix);
    out->length=n+copyText(resultBuffer+n,descriptionBuffer);
    // The real 0x4b2d20 prepends in place then move-constructs its result.
    empty(description);
    if(mutation) oracle_free=releaseB;
    return out;
}
extern "C" void __attribute__((thiscall,section(".oracle_move"),noinline))
spy_move(NarrowString* dst,NarrowString* src) {
    event(5);
    if(dst!=&active->lastError || dst->length || dst->capacity!=15 || dst->storage.small[0])bad=1;
    if(src->capacity>=16) {dst->storage.heap=src->storage.heap;src->storage.heap=0;}
    else for(unsigned i=0;i<=src->length;++i)dst->storage.small[i]=src->storage.small[i];
    dst->length=src->length;dst->capacity=src->capacity;empty(src);
}
extern "C" NarrowString* __attribute__((thiscall,section(".oracle_assign"),noinline))
spy_assign(NarrowString* dst,NarrowString* src) {
    event(8);
    if(dst!=src) {
        if(dst->capacity>=16) oracle_free(dst->storage.heap);
        empty(dst);spy_move(dst,src);
    }
    return dst;
}
static int32_t RR_STDCALL create(Interface* d,uint32_t w,uint32_t h,uint32_t levels,
    uint32_t usage,uint32_t format,uint32_t pool,Interface** out,void* shared) {
    event(1);
    if(d!=&dev||w!=active->width||h!=active->height||levels!=1||usage!=1||format!=active->effectFormat||pool||
       out!=&active->effectTexture||shared)bad=1;
    if(writeMask&1)*out=(nullMask&1)?0:&texture;
    // Proves the next call uses the stored output, rather than the device again.
    if(mutation)active->width^=0x13579bdfu;
    return createHR;
}
static int32_t RR_STDCALL getSurface(Interface* t,uint32_t level,Interface** out) {
    event(2);
    if(t!=((writeMask&1)?&texture:&oldTexture)||level||out!=&active->effectSurface)bad=1;
    if(writeMask&2)*out=(nullMask&2)?0:&surface;
    return surfaceHR;
}
struct Guarded {uint32_t before[4];Graphics g;uint32_t after[4];};
static void initialize(Guarded& x,unsigned enabled,uint32_t w,uint32_t h) {
    unsigned char* p=(unsigned char*)&x;
    for(unsigned i=0;i<sizeof(x);++i)p[i]=(unsigned char)(i*37+19);
    x.g.effectFormat=formatValue;x.g.device=&dev;x.g.width=w;x.g.height=h;x.g.effectEnabled=(uint8_t)enabled;
    x.g.effectTexture=&oldTexture;x.g.effectSurface=&oldSurface;
    x.g.lastError.length=3;x.g.lastError.capacity=oldHeap?16:15;
    if(oldHeap)x.g.lastError.storage.heap=oldBuffer;
    else copyText(x.g.lastError.storage.small,"old");
}
static void reset(Graphics* g) {active=g;count=bad=0;oracle_free=releaseA;memset(events,0,sizeof(events));}
static bool mapped() {
    return (uintptr_t)&oracle_cookie==0xbaabc0u && (uintptr_t)&oracle_free==0x92d4b0u &&
       (uintptr_t)spy_describe==0x44f380u && (uintptr_t)spy_prefix==0x4b2d20u &&
       (uintptr_t)spy_move==0x416fa0u && (uintptr_t)spy_assign==0x440a20u &&
       (uintptr_t)oracle_texture_prefix==0x9fc5f4u && (uintptr_t)oracle_surface_prefix==0x9fc740u;
}
static bool run(unsigned enabled,uint32_t w,uint32_t h,bool oracle) {
    Guarded a,b,expected;initialize(a,enabled,w,h);b=a;expected=a;
    const ErrorServices e={spy_describe,spy_prefix,spy_move,spy_assign,&oracle_free,
        oracle_texture_prefix,oracle_surface_prefix};
    reset(&a.g);bool r=a.g.createEffectTargetUsing(e);
    if(bad)return false;
    bool wanted=!enabled || (createHR>=0 && surfaceHR>=0);
    if(r!=wanted)return false;
    if(enabled) {
        if(writeMask&1)expected.g.effectTexture=(nullMask&1)?0:&texture;
        if(mutation)expected.g.width^=0x13579bdfu;
        if(createHR>=0 && (writeMask&2))expected.g.effectSurface=(nullMask&2)?0:&surface;
        if(!wanted) {
            // Move of a heap string overwrites only the pointer and metadata;
            // the remaining twelve storage bytes are intentionally untouched.
            expected.g.lastError.storage.heap=resultBuffer;
            expected.g.lastError.length=a.g.lastError.length;
            expected.g.lastError.capacity=255;
            if(a.g.lastError.length<45)return false;
        }
    }
    if(!equal(&a,&expected,sizeof(a)))return false;
    unsigned n=count;Event saved[16];memcpy(saved,events,sizeof(saved));
    unsigned callCount=!enabled?0:createHR<0?1:2;
    if(n<callCount)return false;
    if(callCount && events[0].id!=1)return false;
    if(callCount==2 && events[1].id!=2)return false;
    if(wanted && n!=callCount)return false;
    if(!wanted) {
        unsigned ids[7],k=0;ids[k++]=1;if(createHR>=0)ids[k++]=2;
        ids[k++]=3;ids[k++]=4;if(createHR>=0)ids[k++]=8;
        if(oldHeap)ids[k++]=mutation?7:6;
        ids[k++]=5;
        if(n!=k)return false;
        for(unsigned i=0;i<k;++i)if(events[i].id!=ids[i])return false;
    }
    if(oracle) {
        reset(&b.g);bool original=original_effect_target(&b.g);
        if(bad||original!=r||count!=n||!equal(&a,&b,sizeof(a))||!equal(saved,events,n*sizeof(Event)))return false;
        // Also exercise the genuine member's fixed original helper bindings.
        initialize(b,enabled,w,h);reset(&b.g);bool direct=b.g.createEffectTarget();
        if(bad||direct!=r||count!=n||!equal(&a,&b,sizeof(a))||!equal(saved,events,n*sizeof(Event)))return false;
    }
    return true;
}
extern "C" int test_main() {
    deviceVT[23]=(void*)create;textureVT[18]=(void*)getSurface;
    dev.vtable=deviceVT;texture.vtable=oldTexture.vtable=textureVT;
    bool oracle=mapped();
    const int32_t hr[]={0,1,2147483647,(-2147483647-1),-1,(int32_t)0x8876086cu};
    const uint32_t dims[]={0,1,720,4096,0x80000000u,0xffffffffu};
    const unsigned enables[]={0,1,2,255};
    const uint32_t formats[]={0,21,22,113,0x80000000u,0xffffffffu};
    for(unsigned f=0;f<6;++f) {
    formatValue=formats[f];
    for(unsigned en=0;en<4;++en)for(unsigned w=0;w<6;++w)for(unsigned h=0;h<6;++h)
    for(unsigned a=0;a<6;++a)for(unsigned b=0;b<6;++b)
    for(writeMask=0;writeMask<4;++writeMask)for(nullMask=0;nullMask<4;++nullMask)for(oldHeap=0;oldHeap<2;++oldHeap)
    for(mutation=0;mutation<2;++mutation) {
        createHR=hr[a];surfaceHR=hr[b];
        // Original unconditionally dereferences texture after any nonnegative HRESULT.
        // Null texture outputs are meaningful on failure, never repaired here.
        if(createHR>=0 && (nullMask&1))continue;
        if(!run(enables[en],dims[w],dims[h],oracle))return 1;
    }
    }
    if(oracle) {const char m[]="PASS: 1492992 original differential cases; external string/COM test doubles\n";test_write(m,sizeof(m)-1);}
    else {const char m[]="PASS: 1492992 C++ cases; LIMIT: fixed-address oracle fixtures/TLS not configured\n";test_write(m,sizeof(m)-1);}
    return 0;
}
