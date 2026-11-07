#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* original_narrow_range_move_construct(NarrowString*,NarrowString*,NarrowString*);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage=0x13579bdfu;
static bool fs_bad=false;
static NarrowString* oracle_call(NarrowString* a,NarrowString* b,NarrowString* d) {
    NarrowString* result=original_narrow_range_move_construct(a,b,d);
    if(test_get_fs_head()!=fs_storage)fs_bad=true;
    return result;
}
extern "C" void* memset(void* p,int c,size_t n) {
    unsigned char* b=static_cast<unsigned char*>(p);
    for(size_t i=0;i<n;++i)b[i]=static_cast<unsigned char>(c);
    return p;
}
extern "C" void* memcpy(void* d,const void* s,size_t n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    const unsigned char* b=static_cast<const unsigned char*>(s);
    for(size_t i=0;i<n;++i)a[i]=b[i];
    return d;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
struct Block { uint32_t before[2]; NarrowString s[8]; uint32_t after[2]; };
// Full byte comparison includes every inactive union byte and range neighbor.
static int compare(unsigned n,unsigned offset,uint32_t cap,uint32_t len) {
    Block src,dst,a,b;
    unsigned char heap[64],saved[64];
    memset(heap,0xb9,sizeof heap);memcpy(saved,heap,sizeof heap);
    memset(&src,0xa7,sizeof src);memset(&dst,0x5b,sizeof dst);
    for(unsigned i=0;i<8;++i) {
        src.s[i].capacity=cap;src.s[i].length=len;
        if(cap>=16)src.s[i].storage.heap=(i&1)?heap:0;
    }
    memcpy(&a,&src,sizeof src);memcpy(&b,&dst,sizeof dst);
    if(narrow_range_move_construct(a.s+offset,a.s+offset+n,b.s+1)!=b.s+1+n)return 1;
    if(oracle_call(src.s+offset,src.s+offset+n,dst.s+1)!=dst.s+1+n)return 2;
    if(!equal(&a,&src,sizeof src)||!equal(&b,&dst,sizeof dst))return 3;
    if(!equal(heap,saved,sizeof heap))return 4;
    // Independently check published/reset fields, not just agreement.
    for(unsigned i=0;i<n;++i) {
        if(a.s[offset+i].capacity!=15||a.s[offset+i].length||a.s[offset+i].storage.local[0])return 5;
        if(b.s[1+i].capacity!=cap||b.s[1+i].length!=len)return 6;
    }
    return 0;
}
static int inline_expected(unsigned n,unsigned cap,unsigned len,bool self) {
    Block a,b,expected_a,expected_b;
    memset(&a,0xa7,sizeof a);memset(&b,0x5b,sizeof b);
    for(unsigned i=0;i<8;++i) {
        a.s[i].capacity=cap;a.s[i].length=len;
        for(unsigned j=0;j<16;++j)a.s[i].storage.local[j]=static_cast<unsigned char>(j==3?0:0x81+j+i);
    }
    memcpy(&expected_a,&a,sizeof a);memcpy(&expected_b,&b,sizeof b);
    for(unsigned i=0;i<n;++i) {
        NarrowString& src=expected_a.s[i+1];
        NarrowString& dst=self?src:expected_b.s[i+1];
        if(self) {dst.storage.local[0]=0;dst.length=0;dst.capacity=15;}
        else {
            for(unsigned j=0;j<=len;++j)dst.storage.local[j]=src.storage.local[j];
            dst.length=len;dst.capacity=cap;
        }
        src.storage.local[0]=0;src.length=0;src.capacity=15;
    }
    NarrowString* d=self?a.s+1:b.s+1;
    if(narrow_range_move_construct(a.s+1,a.s+1+n,d)!=d+n)return 1;
    return equal(&a,&expected_a,sizeof a)&&equal(&b,&expected_b,sizeof b)?0:2;
}
extern "C" int test_main() {
    static_assert(sizeof(void*)==4,"original oracle ABI is i386 cdecl");
    if(test_install_fs(&fs_storage)!=0)return 50;
    const uint32_t caps[]={16,17,31,0x80000000u,0xffffffffu};
    const uint32_t lengths[]={0,1,15,16,63,0xffffffffu};
    for(unsigned n=0;n<=6;++n)for(unsigned c=0;c<5;++c)for(unsigned l=0;l<6;++l) {
        int r=compare(n,1,caps[c],lengths[l]);if(r)return 10+r;
    }
    for(unsigned cap=0;cap<16;++cap)for(unsigned n=1;n<=6;++n) {
        int r=compare(n,1,cap,0xffffffffu);if(r)return 20+r;
    }
    // Empty range dereferences neither source nor destination, including NULL.
    if(oracle_call(0,0,0)||narrow_range_move_construct(0,0,0))return 30;
    // Exactly one NULL destination skips ALL source accesses/writes.
    Block a,b;memset(&a,0xa7,sizeof a);memcpy(&b,&a,sizeof a);
    if(reinterpret_cast<uintptr_t>(oracle_call(a.s,a.s+1,0))!=24)return 31;
    if(reinterpret_cast<uintptr_t>(narrow_range_move_construct(b.s,b.s+1,0))!=24)return 32;
    if(!equal(&a,&b,sizeof a))return 33;
    for(unsigned i=0;i<sizeof a;++i)if(reinterpret_cast<unsigned char*>(&a)[i]!=0xa7)return 34;
    // No authorized memmove binding: these are explicit expected-state tests.
    for(unsigned cap=0;cap<16;++cap)for(unsigned len=0;len<16;++len)
        for(unsigned n=0;n<=6;++n) {
            if(inline_expected(n,cap,len,false))return 40;
            if(inline_expected(n,cap,len,true))return 41;
        }
    for(unsigned c=0;c<5;++c)for(unsigned n=1;n<=6;++n)
        if(inline_expected(n,caps[c],15,true))return 42;
    if(fs_bad)return 51;
    const char msg[]="PASS: original range heap/overflow/empty/null cases; inline expected states\n";
    test_write(msg,sizeof msg-1);return 0;
}
