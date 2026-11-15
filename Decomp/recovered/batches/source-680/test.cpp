#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_convex_hull_vertex_without_margin(const ConvexHull*, int32_t, HullVector*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s;
    for(unsigned i=0;i<n;++i) a[i]=b[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void bits(float& f,uint32_t u) { copy(&f,&u,4); }
struct Scene { ConvexHull hull; HullVector points[5]; uint32_t guard0; HullVector out; uint32_t guard1; };
static bool run(unsigned sample,unsigned mode,unsigned alias) {
    static const uint32_t values[]={0,0x80000000,0x3f800000,0xbf800000,0x40000000,0xc0600000,0x3f800001,0x7f7fffff,0x00800000,1,0x80000001,0x7f800000,0xff800000,0x7fc12345,0xffc54321,0x7f812345};
    Scene a,b;
    unsigned char* raw=(unsigned char*)&a;
    for(unsigned i=0;i<sizeof(a);++i) raw[i]=(unsigned char)(i*37+sample);
    for(unsigned i=0;i<5;++i) {
        bits(a.points[i].x,values[(sample+i)%16]);
        bits(a.points[i].y,values[(sample*3+i+1)%16]);
        bits(a.points[i].z,values[(sample*7+i+2)%16]);
    }
    bits(a.hull.localScaling.x,values[(sample/16)%16]);
    bits(a.hull.localScaling.y,values[(sample/16+3)%16]);
    bits(a.hull.localScaling.z,values[(sample/16+7)%16]);
    copy(&b,&a,sizeof(a));
    a.hull.vertices=&a.points[1]; b.hull.vertices=&b.points[1];
    // -1 is valid backing storage here; no range check or count is implied.
    int index=(int)(sample%5)-1;
    HullVector* oa=alias==0?&a.out:alias==1?&a.points[index+1]:alias==2?&a.hull.localScaling:&a.points[2];
    HullVector* ob=alias==0?&b.out:alias==1?&b.points[index+1]:alias==2?&b.hull.localScaling:&b.points[2];
    Scene before; copy(&before,&a,sizeof(a));
    unsigned initial=0x1f80u | ((mode&3)<<13) | ((mode&4)?0x8040u:0);
    test_set_mxcsr(initial);
    a.hull.vertexWithoutMargin(index,*oa);
    unsigned flagsA=test_get_mxcsr();
    test_set_mxcsr(initial);
    original_convex_hull_vertex_without_margin(&b.hull,index,ob);
    unsigned flagsB=test_get_mxcsr();
    if(flagsA!=flagsB || !equal(oa,ob,16)) return false;
    // Normalize relocated pointer only for whole-scene comparison.
    b.hull.vertices=a.hull.vertices;
    if(!equal(&a,&b,sizeof(a))) return false;
    unsigned offset=(unsigned)((unsigned char*)oa-(unsigned char*)&a);
    for(unsigned i=0;i<sizeof(a);++i)
        if((i<offset || i>=offset+16) && ((unsigned char*)&a)[i]!=((unsigned char*)&before)[i]) return false;
    uint32_t w; copy(&w,&oa->w,4);
    return w==0;
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    for(unsigned m=0;m<8;++m) for(unsigned s=0;s<256;++s) for(unsigned a=0;a<4;++a)
        if(!run(s,m,a)) { test_set_mxcsr(saved); char msg[16]="FAIL 000 0 0\n"; msg[5]=char(48+s/100); msg[6]=char(48+(s/10)%10); msg[7]=char(48+s%10); msg[9]=char(48+m); msg[11]=char(48+a); test_write(msg,13); return 1; }
    test_set_mxcsr(saved); test_write("8192 oracle comparisons passed\n",31); return 0;
}
