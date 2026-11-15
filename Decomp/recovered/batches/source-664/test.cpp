#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_ray_callback_filter_test(
    const riff::RayCallbackFilter*, const riff::BroadphaseFilter*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fsStorage[8];
static uint32_t seed = 0x13579bdfu;
static uint32_t randomWord() { seed = seed * 1664525u + 1013904223u; return seed; }
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(uint16_t cg,uint16_t cm,uint16_t pg,uint16_t pm) {
    struct CallbackStorage { riff::RayCallbackFilter value; unsigned char tail[32]; } c;
    struct ProxyStorage { riff::BroadphaseFilter value; unsigned char tail[32]; } p;
    unsigned char* cb=reinterpret_cast<unsigned char*>(&c);
    unsigned char* pb=reinterpret_cast<unsigned char*>(&p);
    for(unsigned i=0;i<sizeof(c);++i) cb[i]=static_cast<unsigned char>(randomWord()>>16);
    for(unsigned i=0;i<sizeof(p);++i) pb[i]=static_cast<unsigned char>(randomWord()>>16);
    c.value.group=cg; c.value.mask=cm; p.value.group=pg; p.value.mask=pm;
    const CallbackStorage oldc=c; const ProxyStorage oldp=p;
    const bool want=((cg & pm)!=0) && ((cm & pg)!=0);
    bool actual=original_ray_callback_filter_test(&c.value,&p.value);
    if(test_get_fs_head()!=0x12345678u) return 1;
    if(actual!=want) return 2;
    if(!same(&c,&oldc,sizeof(c)) || !same(&p,&oldp,sizeof(p))) return 3;
    if(c.value.accepts(&p.value)!=actual) return 4;
    if(!same(&c,&oldc,sizeof(c)) || !same(&p,&oldp,sizeof(p))) return 5;
    return 0;
}
extern "C" int test_main() {
    fsStorage[0]=0x12345678u;
    if(test_install_fs(fsStorage)!=0) return 10;
    const uint16_t masks[]={0,1,2,0x7fff,0x8000,0xffff,0xaaaa,0x5555};
    for(unsigned a=0;a<8;++a) for(unsigned b=0;b<8;++b)
    for(unsigned c=0;c<8;++c) for(unsigned d=0;d<8;++d) {
        int r=check(masks[a],masks[b],masks[c],masks[d]); if(r) return r;
    }
    // Each pair of one-bit fields independently matches or fails.
    for(unsigned a=0;a<16;++a) for(unsigned b=0;b<16;++b) {
        uint16_t x=static_cast<uint16_t>(1u<<a), y=static_cast<uint16_t>(1u<<b);
        int r=check(x,x,y,y); if(r) return r;
        r=check(x,y,y,x); if(r) return r;
        r=check(x,y,static_cast<uint16_t>(~y),x); if(r) return r;
        r=check(x,y,y,static_cast<uint16_t>(~x)); if(r) return r;
    }
    for(unsigned i=0;i<10000;++i) {
        uint16_t a=static_cast<uint16_t>(randomWord()>>8), b=static_cast<uint16_t>(randomWord()>>8);
        uint16_t c=static_cast<uint16_t>(randomWord()>>8), d=static_cast<uint16_t>(randomWord()>>8);
        int r=check(a,b,c,d); if(r) return r;
    }
    return 0;
}
