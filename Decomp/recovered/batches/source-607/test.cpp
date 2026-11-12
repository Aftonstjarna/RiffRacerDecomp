#include "impl.hpp"
extern "C" BoxShape* __attribute__((thiscall)) original_box_shape_construct(BoxShape*, const float*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
struct Storage { uint32_t before[4]; BoxShape shape; uint32_t after[4]; };
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = (unsigned char*)p;
    for (unsigned i=0;i<n;++i) b[i]=(unsigned char)(seed+i*37);
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a;
    const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void set_bits(float* p, uint32_t bits) {
    unsigned char* b=(unsigned char*)p;
    for(unsigned i=0;i<4;++i) b[i]=(unsigned char)(bits>>(8*i));
}
static int run(unsigned mode, unsigned index, int offset) {
    static const uint32_t values[]={0,0x80000000u,0x3f800000u,0xbf800000u,
        0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,1,0x80000001u,
        0x007fffffu,0x00800000u,0x7f7fffffu,0x3eaaaaabu};
    Storage a,b,initial;
    fill(&a,sizeof(a), index*13+mode);
    b=a; initial=a;
    float input[4];
    for(unsigned i=0;i<4;++i) set_bits(&input[i],values[(index+i)%14]);
    const float* ap=input; const float* bp=input;
    if(offset>=0) {
        ap=(const float*)((const unsigned char*)&a.shape+offset);
        bp=(const float*)((const unsigned char*)&b.shape+offset);
    }
    test_set_mxcsr(mode);
    BoxShape* ar=original_box_shape_construct(&a.shape,ap);
    unsigned af=test_get_mxcsr();
    if(test_get_fs_head()!=0xffffffffu) return 1;
    test_set_mxcsr(mode);
    BoxShape* br=b.shape.construct(bp);
    unsigned bf=test_get_mxcsr();
    if(ar!=&a.shape || br!=&b.shape || af!=bf) return 2;
    if(!equal(&a,&b,sizeof(a))) return 3;
    if(!equal(a.before,initial.before,sizeof(a.before)) ||
       !equal(a.after,initial.after,sizeof(a.after)) ||
       a.shape.untouched30!=initial.shape.untouched30) return 4;
    if(offset<0) for(unsigned i=0;i<4;++i)
        if(!equal(&input[i], &values[(index+i)%14],4)) return 5;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs[8]={0xffffffffu,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 10;
    unsigned saved=test_get_mxcsr();
    unsigned count=0;
    for(unsigned rounding=0;rounding<4;++rounding)
      for(unsigned denorm=0;denorm<4;++denorm) {
        unsigned mode=0x1f80u|(rounding<<13)|((denorm&1)<<6)|((denorm>>1)<<15);
        for(unsigned i=0;i<14;++i) {
            int result=run(mode,i,-1); if(result) return 20+result;
            ++count;
        }
        for(int offset=0;offset<=40;offset+=4) {
            int result=run(mode,offset,offset); if(result) return 30+result;
            ++count;
        }
      }
    test_set_mxcsr(saved);
    if(count!=400) return 40;
    test_write("400 box constructor comparisons passed\n",38);
    return 0;
}
