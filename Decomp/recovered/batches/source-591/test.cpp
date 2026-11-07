#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_body_vector_pair_accumulate(riff::BodyVectorAccumulator*, const float*, const float*);
extern "C" unsigned test_get_mxcsr();
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[16];
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d, int c, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    for (unsigned i=0;i<n;++i) a[i]=static_cast<unsigned char>(c);
    return d;
}
static float from_bits(uint32_t u) { float f; memcpy(&f,&u,4); return f; }
static uint32_t bits(float f) { uint32_t u; memcpy(&u,&f,4); return u; }
struct Guarded { uint32_t pre[4]; riff::BodyVectorAccumulator object; uint32_t post[4]; };
static uint32_t seed=0x492513ab;
static uint32_t next() { seed=seed*1664525u+1013904223u; return seed; }
static const uint32_t edge[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x00800000u,1,0x80000001u,0x007fffffu,0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,0x4b800000u,0x33800000u};
static float value(unsigned trial,unsigned i) {
    if(trial<64) return from_bits(edge[(trial+i)%16]);
    return from_bits((next()&0x807fffffu)|(((next()>>24)%220+17)<<23));
}
static void prepare(Guarded& g,unsigned trial) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&g);
    for(unsigned i=0;i<sizeof(g);++i) p[i]=static_cast<unsigned char>(i*37+trial);
    for(unsigned r=0;r<3;++r) {
        for(unsigned c=0;c<3;++c) g.object.rows[r][c]=value(trial,r*3+c);
        g.object.firstSum[r]=value(trial,r+4);
        g.object.secondSum[r]=value(trial,r+7);
        g.object.componentScale[r]=value(trial,r+2);
        g.object.transformedScale[r]=value(trial,r+3);
    }
    g.object.factor=value(trial,0);
    if(trial==64) {
        for(unsigned r=0;r<3;++r) {
            for(unsigned c=0;c<3;++c) g.object.rows[r][c]=(r==c)?1.0f:0.0f;
            g.object.firstSum[r]=g.object.secondSum[r]=1.0f;
            g.object.componentScale[r]=float(r+2);
            g.object.transformedScale[r]=2.0f;
        }
        g.object.factor=0.5f;
    }
}
static const float* select(riff::BodyVectorAccumulator& o,unsigned mode,const float* v) {
    switch(mode) {
    case 1:return o.firstSum;
    case 2:return o.secondSum;
    case 3:return o.componentScale;
    case 4:return &o.factor;
    case 5:return o.rows[1];
    case 6:return o.transformedScale;
    default:return v;
    }
}
static bool quietNaN(uint32_t u) { return (u&0x7fc00000u)==0x7fc00000u; }
static int run(unsigned trial,unsigned mode,unsigned control) {
    Guarded a,b,before; prepare(a,trial); memcpy(&b,&a,sizeof(a)); memcpy(&before,&a,sizeof(a));
    float v[3]={1.0f,-2.0f,3.0f}, arm[3]={4.0f,5.0f,-6.0f};
    if(trial<64) for(unsigned i=0;i<3;++i) {v[i]=value(trial,i+5); arm[i]=value(trial,i+9);}
    float savedV[3],savedArm[3]; memcpy(savedV,v,12); memcpy(savedArm,arm,12);
    // Independent alias selections include either or both vectors in the
    // first accumulator, which is updated before the cross-product reload.
    unsigned m=mode%7,n=mode/7;
    const float* av=select(a.object,m,v); const float* bv=select(b.object,m,v);
    const float* aa=select(a.object,n,arm); const float* ba=select(b.object,n,arm);
    test_set_mxcsr(control);
    original_body_vector_pair_accumulate(&a.object,av,aa);
    unsigned status=test_get_mxcsr();
    if(test_get_fs_head()!=0xffffffffu) return 1;
    test_set_mxcsr(control);
    b.object.accumulatePair(bv,ba);
    if(test_get_mxcsr()!=status) return 2;
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    const unsigned char* z=reinterpret_cast<const unsigned char*>(&before);
    unsigned start=offsetof(Guarded,object);
    for(unsigned i=0;i<sizeof(a);++i) {
        bool output=(i>=start+0x130 && i<start+0x13c)||(i>=start+0x140 && i<start+0x14c);
        if(!output) { if(x[i]!=z[i] || y[i]!=z[i]) return 3; }
        else if(x[i]!=y[i]) {
            unsigned word=i&~3u; uint32_t u,w; memcpy(&u,x+word,4); memcpy(&w,y+word,4);
            // Payload/sign selection when multiple NaNs participate is compiler
            // dependent; require both to be quiet NaNs, all other bits exact.
            if(!quietNaN(u)||!quietNaN(w)) return 4;
        }
    }
    for(unsigned i=0;i<3;++i) if(bits(v[i])!=bits(savedV[i]) || bits(arm[i])!=bits(savedArm[i])) return 5;
    if(trial==64 && mode==0) {
        const float first[3]={2,-2,7};
        const float second[3]={49,-119,-67}; // arm cross (2,-6,12), scale 2, initial 1
        for(unsigned i=0;i<3;++i) if(a.object.firstSum[i]!=first[i] || a.object.secondSum[i]!=second[i]) return 6;
    }
    return 0;
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr(); fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0) return 10;
    if(test_get_fs_head()!=0xffffffffu) return 11;
    // Zero must return without touching either pointer, even null inputs.
    for(unsigned sign=0;sign<2;++sign) {
        Guarded a,b,before; prepare(a,64); a.object.factor=from_bits(sign<<31); memcpy(&b,&a,sizeof(a)); memcpy(&before,&a,sizeof(a));
        test_set_mxcsr(0x1f80);
        original_body_vector_pair_accumulate(&a.object,0,0);
        if(test_get_fs_head()!=0xffffffffu) return 12;
        if(test_get_mxcsr()!=0x1f80u) return 14;
        b.object.accumulatePair(0,0);
        const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
        const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
        const unsigned char* z=reinterpret_cast<const unsigned char*>(&before);
        for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=z[i] || y[i]!=z[i]) return 13;
        if(test_get_mxcsr()!=0x1f80u) return 15;
    }
    for(unsigned rounding=0;rounding<4;++rounding)
        for(unsigned denorm=0;denorm<4;++denorm)
            for(unsigned t=0;t<256;++t)
                for(unsigned mode=0;mode<49;++mode) {
                    unsigned control=0x1f80u|(rounding<<13)|((denorm&1)<<6)|((denorm>>1)<<15);
                    int result=run(t,mode,control);
                    if(result) {test_set_mxcsr(saved); test_write("FAIL\n",5); return result;}
                }
    test_set_mxcsr(saved); test_write("PASS 200704 oracle comparisons\n",31); return 0;
}
