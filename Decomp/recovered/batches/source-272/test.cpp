#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_terminated(NarrowString*,const char*);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_range(NarrowString*,const char*,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned calls, seen_count;
static const char* seen_source;
static unsigned fs_head;
static bool fs_bad;
NarrowString* RIFF_THISCALL NarrowString::assign_range(const char* p,uint32_t n) {
    ++calls; seen_source=p; seen_count=n;
    NarrowString* result=original_narrow_assign_range(this,p,n);
    if(test_get_fs_head()!=fs_head) fs_bad=true;
    return result;
}
static void fill(void* p,unsigned n,unsigned char v) {
    unsigned char* b=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i)b[i]=v;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
static void* copy_bytes(void* d,const void* s,unsigned n) {
    char* x=static_cast<char*>(d); const char* y=static_cast<const char*>(s);
    for(unsigned i=0;i<n;++i)x[i]=y[i];
    return d;
}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=copy_bytes;
struct Guarded { uint32_t before[2]; NarrowString s; uint32_t after[2]; };
static int one(unsigned cap,unsigned oldlen,unsigned n,unsigned mode) {
    Guarded a,b,expected;
    char ha[260],hb[260],he[260],source[256],saved[256];
    fill(&a,sizeof a,0xa5);fill(ha,sizeof ha,0x6d);
    a.s.capacity=cap;a.s.length=oldlen;
    if(cap>=16)a.s.storage.heap_text=ha+2;
    char* text=cap>=16?ha+2:a.s.storage.inline_text;
    for(unsigned i=0;i<oldlen;++i)text[i]=char(1+(i*73)%255);
    text[oldlen]=0;
    for(unsigned i=0;i<256;++i)source[i]=char(1+(i*97)%255);
    source[n]=0;copy_bytes(saved,source,sizeof source);
    b=a;expected=a;copy_bytes(hb,ha,sizeof ha);copy_bytes(he,ha,sizeof ha);
    if(cap>=16)b.s.storage.heap_text=hb+2;
    const char* pa=source;const char* pb=source;
    // Self/base alias takes the accepted substring->erase(count=0) path.
    // End alias is outside range's strict interior interval.
    if(mode) {unsigned offset=mode==1?0:oldlen; pa=text+offset;
        pb=(cap>=16?hb+2:b.s.storage.inline_text)+offset;n=mode==1?oldlen:0;}
    char* ex=cap>=16?he+2:expected.s.storage.inline_text;
    for(unsigned i=0;i<n;++i)ex[i]=pa[i];
    ex[n]=0;expected.s.length=n;
    unsigned prior=calls;
    if(a.s.assign_terminated(pa)!=&a.s)return 1;
    if(calls!=prior+1||seen_source!=pa||seen_count!=n)return 2;
    if(original_narrow_assign_terminated(&b.s,pb)!=&b.s)return 3;
    if(test_get_fs_head()!=fs_head||fs_bad)return 4;
    if(!equal(source,saved,sizeof source))return 5;
    if(!equal(&a,&expected,sizeof a))return 6;
    if(cap>=16) {
        if(!equal(ha,he,sizeof ha)||!equal(hb,he,sizeof hb))return 7;
        b.s.storage.heap_text=ha+2;
    }
    if(!equal(&a,&b,sizeof a))return 8;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"x86 string size");
    static_assert(offsetof(NarrowString,length)==16,"length");
    static_assert(offsetof(NarrowString,capacity)==20,"capacity");
    static uint32_t tls[16];tls[0]=0x12345678;
    if(test_install_fs(tls)!=0)return 20;
    fs_head=tls[0];if(test_get_fs_head()!=fs_head)return 21;
    const unsigned caps[]={15,16,31,63,127,255};
    for(unsigned c=0;c<6;++c) {
        unsigned cap=caps[c];
        for(unsigned n=0;n<=cap;++n) {
            int e=one(cap,cap,n,0);if(e)return e;
            e=one(cap,n,n,1);if(e)return e;
            e=one(cap,n,0,2);if(e)return e;
        }
    }
    test_write("narrow-assign-terminated checks passed\n",39);
    return 0;
}
