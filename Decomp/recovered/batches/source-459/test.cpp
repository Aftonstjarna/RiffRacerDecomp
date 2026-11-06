#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_construct_terminated(NarrowString*,const char*);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_range(NarrowString*,const char*,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned head, calls, seen_count;
static const char* seen_source;
static bool bad;
static unsigned char pre_helper[24];
static void fill(void* p,unsigned n,unsigned char v) {
    unsigned char* d=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i)d[i]=v;
}
static void* copy(void* d,const void* s,unsigned n) {
    unsigned char* x=static_cast<unsigned char*>(d);
    const unsigned char* y=static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i)x[i]=y[i];
    return d;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=copy;
NarrowString* RIFF_THISCALL NarrowString::assign_range(const char* p,uint32_t n) {
    ++calls; seen_source=p; seen_count=n;
    if(!equal(this,pre_helper,24))bad=true;
    // Tests intentionally stay in inline storage; no invented growth stub.
    if(n>15)__builtin_trap();
    if(original_narrow_assign_range(this,p,n)!=this)bad=true;
    if(test_get_fs_head()!=head)bad=true;
    // Verify that the recovered constructor ignores this dependency's return.
    return 0;
}
struct Guarded { uint32_t before[2]; NarrowString s; uint32_t after[2]; };
static int one(unsigned n,unsigned pattern,unsigned oldcap,unsigned mode) {
    Guarded a,b,expected;
    unsigned char source[64],saved[64];
    fill(&a,sizeof a,static_cast<unsigned char>(pattern));
    a.s.length=0x87654321; a.s.capacity=oldcap;
    for(unsigned i=0;i<64;++i)source[i]=static_cast<unsigned char>(1+(i*97+pattern)%255);
    source[n]=0;
    // Base alias must see the NUL written before the scan; the other alias
    // is already empty and avoids overlapping nonempty memcpy semantics.
    if(mode==2)a.s.storage.local[15]=0;
    b=a; expected=a;
    copy(saved,source,64);
    expected.s.capacity=15;expected.s.length=0;expected.s.storage.local[0]=0;
    copy(pre_helper,&expected.s,24);
    const char* pa=reinterpret_cast<const char*>(source);
    const char* pb=pa;
    if(mode) {
        unsigned offset=mode==1?0:15;
        pa=a.s.storage.local+offset;pb=b.s.storage.local+offset;n=0;
    }
    for(unsigned i=0;i<n;++i)expected.s.storage.local[i]=static_cast<char>(source[i]);
    expected.s.storage.local[n]=0;expected.s.length=n;
    unsigned prior=calls;
    if(a.s.construct_terminated(pa)!=&a.s)return 1;
    if(calls!=prior+1||seen_source!=pa||seen_count!=n||bad)return 2;
    if(original_narrow_construct_terminated(&b.s,pb)!=&b.s)return 3;
    if(test_get_fs_head()!=head)return 4;
    if(!equal(&a,&expected,sizeof a)||!equal(&b,&expected,sizeof b))return 5;
    if(!equal(source,saved,64))return 6;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"x86 size");
    static_assert(offsetof(NarrowString,length)==16,"length");
    static_assert(offsetof(NarrowString,capacity)==20,"capacity");
    static uint32_t tls[16];tls[0]=0x12345678;
    if(test_install_fs(tls)!=0)return 20;
    head=tls[0];if(test_get_fs_head()!=head)return 21;
    const unsigned caps[]={0,15,16,0xffffffffu};
    const unsigned patterns[]={0x00,0x55,0xa5,0xff};
    for(unsigned c=0;c<4;++c)for(unsigned p=0;p<4;++p) {
        for(unsigned n=0;n<=15;++n) {
            int e=one(n,patterns[p],caps[c],0);if(e)return e;
        }
        for(unsigned mode=1;mode<=2;++mode) {
            int e=one(0,patterns[p],caps[c],mode);if(e)return e;
        }
    }
    const char message[]="narrow-construct-terminated checks passed\n";
    test_write(message,sizeof message-1);
    return 0;
}
