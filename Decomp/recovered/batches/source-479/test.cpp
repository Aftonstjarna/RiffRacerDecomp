#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_move_construct(NarrowString*, NarrowString*);
extern "C" void test_write(const char*, unsigned);
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
struct Guarded { uint32_t before[2]; NarrowString s; uint32_t after[2]; };
static int run(uint32_t cap,uint32_t len,bool oracle,bool self,bool null_heap) {
    Guarded src,dst,actual_src,actual_dst,expected_src,expected_dst;
    unsigned char heap[64],saved_heap[64];
    memset(&src,0xa7,sizeof src);memset(&dst,0x5b,sizeof dst);
    for(unsigned i=0;i<64;++i)heap[i]=static_cast<unsigned char>(0x80+i);
    memcpy(saved_heap,heap,sizeof heap);
    src.s.capacity=cap;src.s.length=len;
    if(cap>=16)src.s.storage.heap=null_heap?0:heap;
    else for(unsigned i=0;i<16;++i)src.s.storage.local[i]=static_cast<unsigned char>(i==3?0:0x81+i);
    memcpy(&actual_src,&src,sizeof src);memcpy(&actual_dst,&dst,sizeof dst);
    memcpy(&expected_src,&src,sizeof src);memcpy(&expected_dst,&dst,sizeof dst);
    NarrowString* e=self?&expected_src.s:&expected_dst.s;
    e->capacity=15;e->length=0;e->storage.local[0]=0;
    if(!self) {
        if(cap>=16) {e->storage.heap=src.s.storage.heap;expected_src.s.storage.heap=0;}
        else if(len!=0xffffffffu)memcpy(&e->storage,&src.s.storage,len+1);
        e->length=len;e->capacity=cap;
    }
    expected_src.s.capacity=15;expected_src.s.length=0;expected_src.s.storage.local[0]=0;
    NarrowString* d=self?&actual_src.s:&actual_dst.s;
    if(d->move_construct(&actual_src.s)!=d)return 1;
    if(!equal(&actual_src,&expected_src,sizeof src)||!equal(&actual_dst,&expected_dst,sizeof dst))return 2;
    if(oracle) {
        if(original_narrow_move_construct(&dst.s,&src.s)!=&dst.s)return 3;
        if(!equal(&actual_src,&src,sizeof src)||!equal(&actual_dst,&dst,sizeof dst))return 4;
    }
    if(!equal(heap,saved_heap,sizeof heap))return 5;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(void*)==4,"oracle is i386");
    const uint32_t caps[]={16,17,31,0x80000000u,0xffffffffu};
    const uint32_t lens[]={0,1,15,16,63,0xffffffffu};
    for(unsigned c=0;c<5;++c)for(unsigned l=0;l<6;++l)for(unsigned z=0;z<2;++z) {
        int r=run(caps[c],lens[l],true,false,z!=0);if(r)return r;
    }
    for(unsigned c=0;c<16;++c) {
        int r=run(c,0xffffffffu,true,false,false);if(r)return 10+r;
        // No trusted memmove IAT binding: expected states only on this path.
        for(unsigned n=0;n<16;++n) {r=run(c,n,false,false,false);if(r)return 20+r;}
    }
    int r=run(15,8,false,true,false);if(r)return 30+r;
    r=run(31,63,false,true,false);if(r)return 40+r;
    const char message[]="PASS: original heap/skip paths; inline/self expected-state checks\n";
    test_write(message,sizeof message-1);
    return 0;
}
