#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_matrix_scaled_vector_accumulate(riff::MatrixAccumulator*, const float*);
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
struct Guarded { uint32_t before[4]; riff::MatrixAccumulator object; uint32_t after[4]; };
static uint32_t seed=0x492513ab;
static uint32_t next() { seed=seed*1664525u+1013904223u; return seed; }
static const uint32_t edge[] = {
    0,0x80000000u,0x3f800000u,0xbf800000u,0x00800000u,1,0x80000001u,
    0x007fffffu,0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,
    0x7fc12345u,0x7f812345u,0x4b800000u,0x33800000u
};
static void prepare(Guarded& g, unsigned trial) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&g);
    for (unsigned i=0;i<sizeof(g);++i) p[i]=static_cast<unsigned char>(i*37u+trial);
    float* rows[3]={g.object.row0,g.object.row1,g.object.row2};
    for(unsigned r=0;r<3;++r) {
        for(unsigned c=0;c<3;++c) {
            uint32_t v=next();
            if(trial<64) v=edge[(trial+r*3+c)%16];
            else v=(v&0x807fffffu)|(((v>>24)%240+7)<<23);
            rows[r][c]=from_bits(v);
        }
        g.object.scale[r]=trial<64 ? from_bits(edge[(trial+r+3)%16]) : from_bits((next()&0x807fffffu)|0x3f000000u);
        g.object.accumulated[r]=trial<64 ? from_bits(edge[(trial+r+7)%16]) : from_bits((next()&0x807fffffu)|0x43000000u);
    }
    if(trial==64) {
        // Exact known result plus unused fourth-column sentinels.
        for(unsigned r=0;r<3;++r) {
            for(unsigned c=0;c<3;++c) rows[r][c]=(r==c)?1.0f:0.0f;
            g.object.scale[r]=2.0f; g.object.accumulated[r]=1.0f;
        }
    }
    if(trial==65) {
        // Distinguishes (Y+X)+Z from X+(Y+Z).
        g.object.row0[0]=16777216.0f; g.object.row0[1]=-16777216.0f;
        g.object.row0[2]=1.0f; g.object.scale[0]=1.0f;
        g.object.accumulated[0]=0.0f;
    }
}
static int run(unsigned trial, unsigned mode, unsigned control) {
    Guarded original, recovered, before;
    prepare(original,trial); memcpy(&recovered,&original,sizeof(original)); memcpy(&before,&original,sizeof(original));
    float v[3]={1.0f,-2.0f,3.0f};
    if(trial==65) v[0]=v[1]=v[2]=1.0f;
    else if(trial<64) for(unsigned i=0;i<3;++i) v[i]=from_bits(edge[(trial*3+i)%16]);
    const float* a=v; const float* b=v;
    if(mode==1) { a=original.object.accumulated; b=recovered.object.accumulated; }
    if(mode==2) { a=original.object.row1; b=recovered.object.row1; }
    if(mode==3) { a=original.object.scale; b=recovered.object.scale; }
    float saved[3]; memcpy(saved,v,sizeof(v));
    test_set_mxcsr(control);
    original_matrix_scaled_vector_accumulate(&original.object,a);
    unsigned original_status=test_get_mxcsr();
    if(test_get_fs_head()!=0xffffffffu) return 8;
    test_set_mxcsr(control);
    recovered.object.accumulate(b);
    unsigned recovered_status=test_get_mxcsr();
    if(original_status!=recovered_status) return 1;
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&original);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&recovered);
    const unsigned char* z=reinterpret_cast<const unsigned char*>(&before);
    const unsigned start=offsetof(Guarded,object)+0x140;
    for(unsigned i=0;i<sizeof(original);++i) {
        if(x[i]!=y[i]) {
            // C++ does not specify which NaN payload wins when both operands
            // are NaNs. Require matching NaN class/signaling quieting below.
            if(i<start || i>=start+12) return 2;
            unsigned k=(i-start)/4;
            uint32_t u=bits(original.object.accumulated[k]);
            uint32_t w=bits(recovered.object.accumulated[k]);
            if((u&0x7fc00000u)!=0x7fc00000u || (w&0x7fc00000u)!=0x7fc00000u) return 3;
        }
        if((i<start || i>=start+12) && (x[i]!=z[i] || y[i]!=z[i])) return 4;
    }
    for(unsigned i=0;i<3;++i) if(bits(v[i])!=bits(saved[i])) return 5;
    if(trial==64 && mode==0 && (original.object.accumulated[0]!=3.0f || original.object.accumulated[1]!=-3.0f || original.object.accumulated[2]!=7.0f)) return 6;
    if(trial==65 && mode==0 && original.object.accumulated[0]!=1.0f) return 7;
    return 0;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0) return 9;
    if(test_get_fs_head()!=0xffffffffu) return 10;
    for(unsigned rounding=0;rounding<4;++rounding)
        for(unsigned denorm=0;denorm<4;++denorm)
            for(unsigned t=0;t<256;++t)
                for(unsigned mode=0;mode<4;++mode) {
                    unsigned control=0x1f80u|(rounding<<13)|((denorm&1)<<6)|((denorm>>1)<<15);
                    int result=run(t,mode,control);
                    if(result) { test_set_mxcsr(saved); test_write("FAIL\n",5); return result; }
                }
    test_set_mxcsr(saved); test_write("PASS 16384 oracle comparisons\n",30); return 0;
}
