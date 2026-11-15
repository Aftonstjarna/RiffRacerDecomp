#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_convex_callback_filter_test(
    const ConvexCallbackFilter*, const ConvexCallbackFilter*);
struct Guarded {
    uint32_t before[2];
    ConvexCallbackFilter filter;
    uint32_t after[3];
};
static bool equal_bytes(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0; i<n; ++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(uint16_t ag, uint16_t am, uint16_t bg, uint16_t bm) {
    Guarded a = {{0x12345678u,0xffffffffu},{0x9f8e50u,ag,am},{0xfeedfaceu,0,0x87654321u}};
    Guarded b = {{0x89abcdefu,0},{0x9fa6a4u,bg,bm},{0xffffffffu,0xdeadbeefu,1}};
    const Guarded saved_a=a, saved_b=b;
    const bool expected = (unsigned(am)&bg)!=0 && (unsigned(ag)&bm)!=0;
    if(a.filter.accepts(&b.filter)!=expected) return 1;
    if(!equal_bytes(&a,&saved_a,sizeof(a)) || !equal_bytes(&b,&saved_b,sizeof(b))) return 2;
    if(original_convex_callback_filter_test(&a.filter,&b.filter)!=expected) return 3;
    if(!equal_bytes(&a,&saved_a,sizeof(a)) || !equal_bytes(&b,&saved_b,sizeof(b))) return 4;
    if(a.filter.accepts(&a.filter) != ((ag&am)!=0)) return 5;
    if(original_convex_callback_filter_test(&a.filter,&a.filter) != ((ag&am)!=0)) return 6;
    if(!equal_bytes(&a,&saved_a,sizeof(a))) return 7;
    return 0;
}
extern "C" int test_main() {
    const uint16_t edge[]={0,1,2,0x7fff,0x8000,0xffff,0x5555,0xaaaa,0xff00,0x00ff};
    for(unsigned a=0;a<10;++a) for(unsigned b=0;b<10;++b)
    for(unsigned c=0;c<10;++c) for(unsigned d=0;d<10;++d) {
        int r=check(edge[a],edge[b],edge[c],edge[d]); if(r) return r;
    }
    for(unsigned a=0;a<16;++a) for(unsigned b=0;b<16;++b)
    for(unsigned c=0;c<16;++c) for(unsigned d=0;d<16;++d) {
        int r=check(uint16_t(1u<<a),uint16_t(1u<<b),uint16_t(1u<<c),uint16_t(1u<<d)); if(r) return r;
    }
    uint32_t state=0x12345678u;
    for(unsigned i=0;i<10000;++i) {
        uint16_t v[4];
        for(unsigned j=0;j<4;++j) { state=state*1664525u+1013904223u; v[j]=uint16_t(state>>16); }
        int r=check(v[0],v[1],v[2],v[3]); if(r) return r;
    }
    return 0;
}
