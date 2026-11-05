#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_substring(NarrowString*,const NarrowString*,uint32_t,uint32_t);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_range(NarrowString*,const char*,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_head;
static bool fs_bad;
static unsigned substring_calls, copy_calls, last_count, last_offset;
static const char* last_source;
NarrowString* RIFF_THISCALL NarrowString::assign_substring(const NarrowString* s,uint32_t offset,uint32_t n) {
    ++substring_calls; last_count=n; last_offset=offset;
    if(s!=this) __builtin_trap();
    NarrowString* result=original_narrow_assign_substring(this,s,offset,n);
    if(test_get_fs_head()!=fs_head) fs_bad=true;
    return result;
}
void RIFF_THISCALL NarrowString::grow(uint32_t,uint32_t) { __builtin_trap(); }
RIFF_NORETURN void narrow_length_error(const char*) { __builtin_trap(); }
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
void* narrow_copy(void* d,const void* s,uint32_t n) {
    ++copy_calls;last_source=static_cast<const char*>(s);last_count=n;
    return copy_bytes(d,s,n);
}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=copy_bytes;
// Positive-offset, nonempty alias shifts need the unbound original memmove
// IAT at 0x92d4a4. These tests deliberately avoid that dependency.
struct Guarded { uint32_t before[2]; NarrowString s; uint32_t after[2]; };
static int one(unsigned cap,unsigned oldlen,unsigned n,unsigned mode,unsigned offset=0) {
    Guarded a,b,expected;
    char ha[260],hb[260],he[260],source[256],saved[256];
    fill(&a,sizeof a,0xa5);fill(ha,sizeof ha,0x6d);
    a.s.capacity=cap;a.s.length=oldlen;
    if(cap>=16)a.s.storage.heap=ha+2;
    char* text=cap>=16?ha+2:a.s.storage.local;
    for(unsigned i=0;i<oldlen;++i)text[i]=char(1+(i*73)%255);
    text[oldlen]=0;
    for(unsigned i=0;i<256;++i)source[i]=i%7==0?0:char(1+(i*97)%255);
    copy_bytes(saved,source,sizeof source);
    b=a;expected=a;copy_bytes(hb,ha,sizeof ha);copy_bytes(he,ha,sizeof ha);
    if(cap>=16)b.s.storage.heap=hb+2;
    const char* pa=source;const char* pb=source;
    unsigned requested=n;
    if(mode==1) { pa=text+offset; pb=(cap>=16?hb+2:b.s.storage.local)+offset;
        n=requested<oldlen-offset?requested:oldlen-offset; }
    if(mode==2) {pa=text+oldlen;pb=(cap>=16?hb+2:b.s.storage.local)+oldlen;n=0;requested=0;}
    if(mode==3) {pa=0;pb=0;n=0;requested=0;}
    char* ex=cap>=16?he+2:expected.s.storage.local;
    for(unsigned i=0;i<n;++i)ex[i]=pa[i];
    ex[n]=0;expected.s.length=n;
    // Self-substring first writes a terminator at offset+selected count,
    // even when erasing the prefix subsequently empties the string.
    if(mode==1) ex[offset+n]=0;
    unsigned old_substring_calls=substring_calls, old_copy_calls=copy_calls;
    if(a.s.assign_range(pa,requested)!=&a.s)return 1;
    if(mode==1) {
        if(substring_calls!=old_substring_calls+1||copy_calls!=old_copy_calls||
           last_offset!=offset||last_count!=requested)return 9;
    } else {
        if(substring_calls!=old_substring_calls)return 10;
        if(copy_calls!=old_copy_calls+(n!=0?1u:0u))return 11;
        if(n!=0&&(last_source!=pa||last_count!=n))return 12;
    }
    if(original_narrow_assign_range(&b.s,pb,requested)!=&b.s)return 3;
    if(test_get_fs_head()!=fs_head||fs_bad)return 4;
    if(!equal(source,saved,sizeof source))return 5;
    if(!equal(&a,&expected,sizeof a))return 6;
    if(cap>=16) {
        if(!equal(ha,he,sizeof ha)||!equal(hb,he,sizeof hb))return 7;
        b.s.storage.heap=ha+2;
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
            if(n>0) {
                e=one(cap,n,0xffffffffu,1);if(e)return e;
                for(unsigned take=0;take<=n;++take) {
                    e=one(cap,n,take,1);if(e)return e;
                }
                for(unsigned off=1;off<n;++off) {
                    e=one(cap,n,0,1,off);if(e)return e;
                }
            }
            e=one(cap,n,0,2);if(e)return e;
            e=one(cap,n,0,3);if(e)return e;
        }
    }
    test_write("narrow-assign-range checks passed\n",sizeof("narrow-assign-range checks passed\n")-1);
    return 0;
}
