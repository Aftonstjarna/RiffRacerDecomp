#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_pointer(WideString*,const uint16_t*);
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_range(WideString*,const uint16_t*,uint32_t);
extern "C" void test_write(const char*,unsigned);
static unsigned calls;
static uint32_t seen_count;
static const uint16_t* seen_source;
WideString* RIFF_THISCALL WideString::assign_range(const uint16_t* s,uint32_t n) {
    ++calls;
    seen_source=s;
    seen_count=n;
    return original_wide_assign_range(this,s,n);
}
extern "C" void* memcpy(void* d,const void* s,unsigned n) {
    unsigned char* x=static_cast<unsigned char*>(d);
    const unsigned char* y=static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i) { x[i]=y[i]; }
    return d;
}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4))) = memcpy;
static void fill(void* d,unsigned n,unsigned char v) {
    unsigned char* p=static_cast<unsigned char*>(d);
    for(unsigned i=0;i<n;++i) { p[i]=v; }
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) { if(x[i]!=y[i]) { return false; } }
    return true;
}
struct Guard { uint32_t before[2]; WideString s; uint32_t after[2]; };
// kind 0 external, 1 self base, 2 self interior, 3 own terminator.
static int run(unsigned cap,unsigned len,unsigned kind,unsigned pos) {
    Guard a,b;
    uint16_t ha[1040],hb[1040],ext[1030],saved[1030];
    fill(&a,sizeof a,0xa5);
    fill(ha,sizeof ha,0x6d);
    a.s.capacity=cap;
    a.s.length=len;
    if(cap>=8) { a.s.storage.heap=ha+2; }
    uint16_t* da=cap<8?a.s.storage.local:ha+2;
    for(unsigned i=0;i<len;++i) { da[i]=uint16_t(0x8100+i); }
    da[len]=0;
    // Interior empty substring avoids the unbound memmove CRT import.
    if(kind==2) { da[pos]=0; }
    b=a;
    memcpy(hb,ha,sizeof ha);
    if(cap>=8) { b.s.storage.heap=hb+2; }
    uint16_t* db=cap<8?b.s.storage.local:hb+2;
    for(unsigned i=0;i<1030;++i) { ext[i]=uint16_t(0xd800+(i%0x800)); }
    // A zero terminates even if more nonzero units follow it.
    ext[len]=0;
    memcpy(saved,ext,sizeof ext);
    const uint16_t* sa=kind==0?ext:kind==1?da:kind==2?da+pos:da+len;
    const uint16_t* sb=kind==0?ext:kind==1?db:kind==2?db+pos:db+len;
    unsigned expected=(kind==3||kind==2)?0:len;
    calls=0;
    if(a.s.assign_pointer(sa)!=&a.s) { return 1; }
    if(calls!=1||seen_source!=sa||seen_count!=expected) { return 2; }
    if(original_wide_assign_pointer(&b.s,sb)!=&b.s) { return 3; }
    if(!equal(ha,hb,sizeof ha)||!equal(ext,saved,sizeof ext)) { return 4; }
    if(cap>=8) { b.s.storage.heap=ha+2; }
    if(!equal(&a,&b,sizeof a)) { return 5; }
    if(a.s.capacity!=cap) { return 6; }
    // External assignment has simple independent expected effects, including
    // preserved bytes beyond the new terminator and untouched object guards.
    if(kind==0) {
        if(a.s.length!=len) { return 7; }
        for(unsigned i=0;i<len;++i) { if(da[i]!=ext[i]) { return 8; } }
        if(da[len]!=0) { return 9; }
        for(unsigned i=0;i<2;++i) {
            if(a.before[i]!=0xa5a5a5a5u||a.after[i]!=0xa5a5a5a5u) { return 10; }
        }
        for(unsigned i=len+1;i<(cap<8?8:cap+1);++i) {
            if(da[i]!=(cap<8?0xa5a5:0x6d6d)) { return 11; }
        }
    }
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"x86 layout");
    static_assert(offsetof(WideString,length)==16,"length offset");
    static_assert(offsetof(WideString,capacity)==20,"capacity offset");
    copy_import=memcpy;
    const unsigned caps[]={0,1,7,8,15,31,1024};
    for(unsigned c=0;c<7;++c) {
        unsigned cap=caps[c];
        for(unsigned len=0;len<=cap;++len) {
            for(unsigned kind=0;kind<4;++kind) {
                int e=run(cap,len,kind,len?len/2:0);
                if(e) { return e; }
            }
        }
    }
    test_write("wide pointer checks passed\n",27);
    return 0;
}
