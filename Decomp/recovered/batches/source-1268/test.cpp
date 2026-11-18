#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* original_worker_string_compose(NarrowString*,NarrowString*,const NarrowString*);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_append_substring(NarrowString*,const NarrowString*,uint32_t,uint32_t);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_move_construct(NarrowString*,NarrowString*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d,const void* s,size_t n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(size_t i=0;i<n;++i)a[i]=b[i]; return d; }
extern "C" void* memset(void* d,int v,size_t n) { unsigned char* a=(unsigned char*)d; for(size_t i=0;i<n;++i)a[i]=(unsigned char)v; return d; }
typedef void* (*Copy)(void*,const void*,size_t);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy;
NarrowString* RIFF_THISCALL NarrowString::append_substring(const NarrowString* s,uint32_t p,uint32_t n) { return original_narrow_append_substring(this,s,p,n); }
NarrowString* RIFF_THISCALL NarrowString::move_construct(NarrowString* s) { return original_narrow_move_construct(this,s); }
struct Fixture { uint32_t before; NarrowString left, right, out; uint32_t after; char heap[80]; };
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true; }
static void init(Fixture& f,unsigned l,unsigned r,bool self) {
    memset(&f,0xa5,sizeof f); f.left.storage.heap=f.heap;f.left.length=l;f.left.capacity=63;
    for(unsigned i=0;i<l;++i) { f.heap[i]=(char)('A'+i%26); } f.heap[l]=0;
    f.right.length=r;f.right.capacity=15;for(unsigned i=0;i<r;++i)f.right.storage.local[i]=(char)('a'+i%26);f.right.storage.local[r]=0;
    (void)self;
}
static int run(unsigned l,unsigned r,bool self,unsigned head) {
    Fixture a,b;init(a,l,r,self);init(b,l,r,self);
    NarrowString* ar=self?&a.left:&a.right;NarrowString* br=self?&b.left:&b.right;
    if(worker_string_compose(&a.out,&a.left,ar)!=&a.out)return 1;
    if(test_get_fs_head()!=head)return 2;
    if(original_worker_string_compose(&b.out,&b.left,br)!=&b.out)return 3;
    if(test_get_fs_head()!=head)return 4;
    // Normalize the transferred heap pointers before comparing every byte.
    if(a.out.storage.heap!=a.heap || b.out.storage.heap!=b.heap)return 5;
    a.out.storage.heap=0;b.out.storage.heap=0;
    if(!equal(&a,&b,sizeof a))return 6;
    if(a.out.length!=l+(self?l:r)||a.out.capacity!=63||a.left.length!=0||a.left.capacity!=15||a.left.storage.local[0]!=0)return 7;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"32-bit layout");
    static unsigned fs[16];fs[0]=0x12345678;if(test_install_fs(fs)!=0)return 10;unsigned head=fs[0];if(test_get_fs_head()!=head)return 11;
    for(unsigned l=0;l<=30;l+=3)for(unsigned r=0;r<=15;++r){int e=run(l,r,false,head);if(e)return e;}
    for(unsigned l=0;l<=30;l+=3){int e=run(l,0,true,head);if(e)return e;}
    return 0;
}
