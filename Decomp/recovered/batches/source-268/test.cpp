#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_move_construct(WideString*, WideString*);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memset(void* p, int c, size_t n) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (size_t i=0;i<n;++i) b[i]=static_cast<unsigned char>(c);
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
struct Guarded { uint32_t before[2]; WideString s; uint32_t after[2]; };
static int run(uint32_t cap,uint32_t len,bool oracle,bool self) {
    Guarded src,dst,actual_src,actual_dst,expected_src,expected_dst;
    uint16_t heap[20],saved_heap[20];
    memset(&src,0xa7,sizeof src);memset(&dst,0x5b,sizeof dst);
    for(unsigned i=0;i<20;++i)heap[i]=uint16_t(0xd800+i);
    memcpy(saved_heap,heap,sizeof heap);
    src.s.capacity=cap;src.s.length=len;
    if(cap>=8)src.s.storage.heap=heap;
    else for(unsigned i=0;i<8;++i)src.s.storage.local[i]=uint16_t(i==3?0:0x8100+i);
    memcpy(&actual_src,&src,sizeof src);memcpy(&actual_dst,&dst,sizeof dst);
    memcpy(&expected_src,&src,sizeof src);memcpy(&expected_dst,&dst,sizeof dst);
    WideString* e=self?&expected_src.s:&expected_dst.s;
    e->capacity=7;e->length=0;e->storage.local[0]=0;
    if(!self) {
        if(cap>=8) { e->storage.heap=heap;expected_src.s.storage.heap=0; }
        else if(len!=0xffffffffu) {
            uint32_t count=(len+1)*2;
            memcpy(&e->storage,&src.s.storage,count);
        }
        e->length=len;e->capacity=cap;
    }
    expected_src.s.capacity=7;expected_src.s.length=0;expected_src.s.storage.local[0]=0;
    WideString* d=self?&actual_src.s:&actual_dst.s;
    if(d->move_construct(&actual_src.s)!=d)return 1;
    if(!equal(&actual_src,&expected_src,sizeof src)||!equal(&actual_dst,&expected_dst,sizeof dst))return 2;
    if(oracle) {
        if(original_wide_move_construct(&dst.s,&src.s)!=&dst.s)return 3;
        if(!equal(&actual_src,&src,sizeof src)||!equal(&actual_dst,&dst,sizeof dst))return 4;
    }
    if(!equal(heap,saved_heap,sizeof heap))return 5;
    return 0;
}
extern "C" int test_main() {
    // Heap path never dereferences the transferred pointer. Full object bytes
    // check untouched union bytes and guards as well as source's four-byte clear.
    const uint32_t capacities[]={8,9,31,0xffffffffu};
    const uint32_t lengths[]={0,1,7,8,19,0xffffffffu};
    for(unsigned c=0;c<4;++c)for(unsigned l=0;l<6;++l) {
        int r=run(capacities[c],lengths[l],true,false);if(r)return r;
    }
    for(unsigned c=0;c<8;++c) {
        int r=run(c,0xffffffffu,true,false);if(r)return 10+r;
        // 0x7fffffff+1 doubles to zero: the import is still invoked with count
        // zero in the original, so only expected-state validation is possible.
        r=run(c,0x7fffffffu,false,false);if(r)return 20+r;
        for(unsigned n=0;n<8;++n) {r=run(c,n,false,false);if(r)return 30+r;}
    }
    int r=run(7,5,false,true);if(r)return 40+r;
    r=run(31,19,false,true);if(r)return 50+r;
    const char message[]="PASS: original heap/skip paths; inline/self expected-state checks\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
