#include "impl.hpp"
extern "C" uint32_t __attribute__((cdecl)) original_audio_memory_read_callback(AudioMemoryState*, void*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static unsigned calls, seen_count;
static const void* seen_source;
static void* seen_dest;
extern "C" void* memcpy(void* d, const void* s, size_t n) {
    unsigned char* out = static_cast<unsigned char*>(d);
    const unsigned char* in = static_cast<const unsigned char*>(s);
    for(size_t i=0;i<n;++i) out[i]=in[i];
    return d;
}
extern "C" void* audited_copy(void* d, const void* s, size_t n) {
    ++calls; seen_count=n; seen_source=s; seen_dest=d;
    return memcpy(d,s,n);
}
typedef void* (*Copy)(void*,const void*,size_t);
Copy copy_iat __attribute__((section(".test_iat"),used,aligned(4))) = audited_copy;
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(uint32_t length,uint32_t cursor,uint32_t request,bool alias) {
    unsigned char source[256], a[256], b[256];
    AudioMemoryState x,y;
    for(unsigned i=0;i<256;++i) {source[i]=(unsigned char)(i*37+13);a[i]=b[i]=0xa5;}
    for(unsigned i=0;i<sizeof(x);++i) reinterpret_cast<unsigned char*>(&x)[i]=0x6b;
    // Arrange a valid source even for wraparound cursor arithmetic on i386.
    x.data=reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(source+16)-cursor);
    x.length=length; x.cursor=cursor; y=x;
    uint32_t count=request < uint32_t(length-cursor)?request:uint32_t(length-cursor);
    void* da=alias?static_cast<void*>(&x.cursor):static_cast<void*>(a+8);
    void* db=alias?static_cast<void*>(&y.cursor):static_cast<void*>(b+8);
    uint32_t r=audio_memory_read_callback(&x,da,request);
    calls=0;
    uint32_t o=original_audio_memory_read_callback(&y,db,request);
    if(r!=count || o!=count || calls!=1 || seen_count!=count || seen_source!=source+16 || seen_dest!=db) return 1;
    if(!equal(&x,&y,sizeof(x)) || !equal(a,b,256)) return 2;
    AudioMemoryState expected=y;
    expected.cursor=cursor;
    if(alias) memcpy(&expected.cursor,source+16,count);
    expected.cursor+=count;
    if(x.cursor!=expected.cursor) return 3;
    // Independent expected state, including every opaque byte and the pointer.
    expected.data=x.data; expected.length=length;
    for(unsigned i=0;i<0x2c;++i) expected.opaque[i]=0x6b;
    if(!equal(&x,&expected,sizeof(x))) return 4;
    if(!alias) for(unsigned i=0;i<256;++i) {
        unsigned char want=(i>=8 && i<8+count)?source[16+i-8]:0xa5;
        if(a[i]!=want) return 5;
    }
    return 0;
}
extern "C" int test_main() {
    copy_iat=audited_copy;
    const uint32_t requests[]={0,1,2,3,4,7,16,63,128,0x80000000u,0xffffffffu};
    for(uint32_t len=0;len<=128;++len)
        for(uint32_t pos=0;pos<=len;++pos)
            for(unsigned j=0;j<sizeof(requests)/sizeof(requests[0]);++j)
                if(check(len,pos,requests[j],false)) return 1;
    if(check(3,9,4,false) || check(0,0xffffffffu,1,false) || check(0xffffffffu,0xfffffffeu,1,false)) return 2;
    for(unsigned n=0;n<=4;++n) if(check(16,0,n,true)) return 3;
    test_write("audio memory read: passed\n",26);
    return 0;
}
