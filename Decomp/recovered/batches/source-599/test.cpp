#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_box_vertex_without_margin(const riff::BoxShape*, int32_t, riff::Vector4*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i]; return d; }
extern "C" void* memset(void* d,int c,unsigned n) { unsigned char* a=(unsigned char*)d; for(unsigned i=0;i<n;++i)a[i]=(unsigned char)c; return d; }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false; return true; }
struct Arena { uint32_t before[4]; riff::BoxShape box; uint32_t after[8]; riff::Vector4 out; uint32_t tail[4]; };
static int run(unsigned mode, int32_t index, const uint32_t* values, unsigned alias) {
    Arena a,b,snapshot;
    unsigned char* p=(unsigned char*)&a;
    for(unsigned i=0;i<sizeof(a);++i)p[i]=(unsigned char)(i*37+91);
    // Copy representations directly: float-return helpers on i386 use x87
    // and could quiet signaling NaNs before the oracle sees them.
    memcpy(&a.box.half_extents_without_margin,values,12);
    const uint32_t ignored_w=0x7f800001;
    memcpy(&a.box.half_extents_without_margin.w,&ignored_w,4);
    memcpy(&b,&a,sizeof(a)); memcpy(&snapshot,&a,sizeof(a));
    riff::Vector4* oa=alias? &a.box.half_extents_without_margin:&a.out;
    riff::Vector4* ob=alias? &b.box.half_extents_without_margin:&b.out;
    test_set_mxcsr(mode);
    original_box_vertex_without_margin(&a.box,index,oa);
    unsigned original_status=test_get_mxcsr();
    test_set_mxcsr(mode);
    b.box.vertex_without_margin(index,ob);
    unsigned recovered_status=test_get_mxcsr();
    if(!equal(&a,&b,sizeof(a)) || original_status!=recovered_status) return 1;
    unsigned off=(unsigned)((unsigned char*)oa-(unsigned char*)&a);
    for(unsigned i=0;i<sizeof(a);++i)if((i<off||i>=off+16)&&((unsigned char*)&a)[i]!=((unsigned char*)&snapshot)[i])return 2;
    uint32_t w_bits; memcpy(&w_bits,&oa->w,4);
    if(w_bits!=0) return 3;
    return 0;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    const uint32_t values[][3]={
        {0x3f800000,0x40000000,0x40400000}, {0xbf800000,0xc0200000,0x3eaaaaab},
        {0,0x80000000,0}, {1,0x80000001,0x007fffff},
        {0x00800000,0x7f7fffff,0xff7fffff},
        {0x7f800000,0xff800000,0x3f800000},
        {0x7fc12345,0xffc54321,0x7f800001}, {0xff800001,0x7fc00000,0xffc00000}
    };
    const int32_t indices[]={0,1,2,3,4,5,6,7,8,15,255,-1,-2,-8,2147483647,(-2147483647-1)};
    for(unsigned rounding=0;rounding<4;++rounding)
    for(unsigned denorm=0;denorm<4;++denorm)
    for(unsigned v=0;v<sizeof(values)/sizeof(values[0]);++v)
    for(unsigned i=0;i<sizeof(indices)/sizeof(indices[0]);++i)
    for(unsigned alias=0;alias<2;++alias) {
        unsigned mode=0x1f80u|(rounding<<13)|((denorm&1u)<<6)|((denorm>>1)<<15);
        int result=run(mode,indices[i],values[v],alias);
        if(result) { test_set_mxcsr(saved); test_write("FAIL\n",5); return result; }
    }
    test_set_mxcsr(saved); test_write("PASS: 4096 oracle comparisons\n",30); return 0;
}
