#include "impl.hpp"
using riff::Vector4;
using riff::ConvexHull;
extern "C" void __attribute__((thiscall)) original_convex_hull_edge_without_margin(ConvexHull*, int32_t, Vector4*, Vector4*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i];return d; }
extern "C" void* memset(void* d,int c,unsigned n) { unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)c;return d; }
static float fromBits(uint32_t u) { float f;memcpy(&f,&u,4);return f; }
struct Fixture { uint32_t pre[4]; ConvexHull hull; Vector4 points[17]; Vector4 a,b; uint32_t post[4]; };
static void initialize(Fixture& f,int count,int pattern) {
    memset(&f,0xa5,sizeof f);
    f.hull.vertexCount=count; f.hull.vertices=f.points+8;
    f.hull.scaling.x=pattern?fromBits(0x80000000):2.0f;
    f.hull.scaling.y=pattern?fromBits(0x7f800000):-3.0f;
    f.hull.scaling.z=pattern?fromBits(0x00000001):0.5f;
    f.hull.scaling.w=fromBits(0x7fc54321);
    const uint32_t special[]={0,0x80000000,0x3f800000,0xbf800000,1,0x7f7fffff,0x7f800000,0xff800000,0x7fc12345,0x7f812345};
    for(int i=0;i<17;++i) {
        f.points[i].x=pattern?fromBits(special[i%10]):float(i-8);
        f.points[i].y=pattern?fromBits(special[(i+3)%10]):float(2*i+1);
        f.points[i].z=pattern?fromBits(special[(i+6)%10]):float(4-i);
        f.points[i].w=fromBits(0x7f812222); // Must never be consumed.
    }
}
static void outputs(Fixture& f,int mode,Vector4*& a,Vector4*& b) {
    a=&f.a;b=&f.b;
    if(mode==1)b=a;
    if(mode==2)a=f.points+8; // First store may overwrite the next input.
    if(mode==3)a=&f.hull.scaling;
    if(mode==4){a=f.points+9;b=f.points+8;}
    if(mode==5)b=&f.hull.scaling;
}
static void number(unsigned n) { char s[9];for(int i=0;i<8;++i)s[i]="0123456789abcdef"[(n>>(28-i*4))&15];s[8]=' ' ;test_write(s,9); }
extern "C" int test_main() {
    uint32_t fs[8]={0x12345678};
    if(test_install_fs(fs)!=0)return 1;
    unsigned saved=test_get_mxcsr();
    const int counts[]={-5,-1,1,2,5};
    const int32_t edges[]={(-2147483647-1),-11,-5,-1,0,1,4,5,11,2147483647};
    for(unsigned rounding=0;rounding<4;++rounding)
    for(unsigned denormal=0;denormal<2;++denormal)
    for(unsigned c=0;c<5;++c)for(unsigned e=0;e<10;++e)
    for(int pattern=0;pattern<2;++pattern)for(int mode=0;mode<6;++mode) {
        // IDIV traps for INT_MIN / -1, for either endpoint.
        if(counts[c]==-1 && (edges[e]==(-2147483647-1) || edges[e]==2147483647))continue;
        Fixture ref,got;initialize(ref,counts[c],pattern);initialize(got,counts[c],pattern);
        Vector4 *ra,*rb,*ga,*gb;outputs(ref,mode,ra,rb);outputs(got,mode,ga,gb);
        unsigned control=0x1f80u|(rounding<<13)|(denormal?0x8040u:0u);
        test_set_mxcsr(control);
        original_convex_hull_edge_without_margin(&ref.hull,edges[e],ra,rb);
        if(test_get_fs_head()!=fs[0])return 2;
        unsigned status=test_get_mxcsr();
        test_set_mxcsr(control);
        got.hull.edgeWithoutMargin(edges[e],*ga,*gb);
        if(test_get_mxcsr()!=status)return 3;
        // Normalize the sole fixture-specific address before comparing every
        // byte: outputs, unused fields, point W lanes and surrounding guards.
        ref.hull.vertices=got.hull.vertices;
        const unsigned char* a=(const unsigned char*)&ref;
        const unsigned char* b=(const unsigned char*)&got;
        for(unsigned i=0;i<sizeof ref;++i)if(a[i]!=b[i]){number(rounding);number(denormal);number(c);number(e);number(pattern);number(mode);number(i);number(a[i]);number(b[i]);return 4;}
    }
    test_set_mxcsr(saved);
    test_write("edge oracle comparisons passed\n",31);
    return 0;
}
