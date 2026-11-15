#include "impl.hpp"
using riff::Vector4;
using riff::ConvexHull;
extern "C" void __attribute__((thiscall)) original_convex_hull_batched_support_without_margin(const ConvexHull*,const Vector4*,Vector4*,int32_t);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i];return d; }
extern "C" void* memset(void* d,int c,unsigned n) { unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)c;return d; }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true; }
static float bits(uint32_t u) { float f;memcpy(&f,&u,4);return f; }
static uint32_t state=0x12345678;
static uint32_t randomWord() { state=state*1664525u+1013904223u;return state; }
static float number() { return (int32_t)(randomWord()%200001u-100000u)*0.03125f; }
static int run(int nv,int nd,int mode,unsigned control,bool alias) {
    ConvexHull a;memset(&a,0x5a,sizeof(a));
    Vector4 vertices[12],dirs[10];
    for(int i=0;i<12;++i) { vertices[i]={number(),number(),number(),bits(0x7fc12345)}; }
    for(int i=0;i<10;++i) { dirs[i]={number(),number(),number(),bits(0x7fa12345)}; }
    a.localScaling={1.5f,-2.0f,0.25f,123.0f};a.vertexCount=nv;a.vertices=vertices;
    if(mode==1) { for(int i=0;i<12;++i)vertices[i]={1,2,3,99};for(int i=0;i<10;++i)dirs[i]={0,0,0,77}; }
    if(mode==2) { vertices[0].x=bits(0x7fc12345);dirs[1].y=bits(0x7fc56789); }
    if(mode==3) { a.localScaling={1,1,1,0};for(int i=0;i<12;++i)vertices[i]={-1.0e18f,0,0,0};for(int i=0;i<10;++i)dirs[i]={1,0,0,0}; }
    if(mode==4) { vertices[0].x=bits(0x7f800000);vertices[1].y=bits(0xff800000);dirs[0].x=0; }
    if(mode==5) { a.localScaling={bits(1),-0.0f,bits(0x00800000),0}; }
    ConvexHull saved=a;Vector4 vs[12],ds[10];memcpy(vs,vertices,sizeof(vs));memcpy(ds,dirs,sizeof(ds));
    Vector4 out1[12],out2[12];
    memset(out1,0xa6,sizeof(out1));if(alias)memcpy(out1+1,dirs,sizeof(dirs));memcpy(out2,out1,sizeof(out1));
    test_set_mxcsr(control);
    original_convex_hull_batched_support_without_margin(&a,alias?out1+1:dirs,out1+1,nd);
    unsigned f1=test_get_mxcsr();
    test_set_mxcsr(control);
    a.batchedSupportWithoutMargin(alias?out2+1:dirs,out2+1,nd);
    unsigned f2=test_get_mxcsr();
    if(!equal(out1,out2,sizeof(out1)))return 1;
    if(!equal(&a,&saved,sizeof(a))||!equal(vertices,vs,sizeof(vs))||!equal(dirs,ds,sizeof(ds)))return 2;
    if(f1!=f2)return 3;
    if(nd>0 && nv<=0) { if(out1[1].w!=bits(0xdd5e0b6b))return 4; }
    if(nd>0 && nv>0 && mode==1 && !alias) { if(out1[1].x!=1.5f || out1[1].y!=-4 || out1[1].z!=0.75f || out1[1].w!=0)return 5; }
    return 0;
}
extern "C" int test_main() {
    unsigned old=test_get_mxcsr();
    const int counts[]={-3,0,1,5,10};
    const int hulls[]={-1,0,1,2,12};
    for(int m=0;m<6;++m)for(int i=0;i<5;++i)for(int j=0;j<5;++j)for(int a=0;a<2;++a) {
        int r=run(hulls[i],counts[j],m,0x1f80,a!=0);if(r){test_write("FAIL\n",5);test_set_mxcsr(old);return r;}
    }
    for(int i=0;i<160;++i) { int r=run(12,10,0,0x1f80 | ((i%4)<<13),false);if(r){test_set_mxcsr(old);return r;} }
    test_set_mxcsr(old);test_write("PASS\n",5);return 0;
}
