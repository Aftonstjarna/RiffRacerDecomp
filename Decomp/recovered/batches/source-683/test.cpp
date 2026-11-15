#include "impl.hpp"
extern "C" riff::Vector4* __attribute__((thiscall))
original_sphere_support_without_margin(const riff::Sphere*, riff::Vector4*, const riff::Vector4*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Guarded { uint32_t before[4]; riff::Vector4 value; uint32_t after[4]; };
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0;i<n;++i) b[i]=static_cast<unsigned char>(seed+i*37);
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void setBits(riff::Vector4& v, const uint32_t* bits) {
    unsigned char* d=reinterpret_cast<unsigned char*>(&v);
    const unsigned char* s=reinterpret_cast<const unsigned char*>(bits);
    for(unsigned i=0;i<16;++i) d[i]=s[i];
}
extern "C" int test_main() {
    uint32_t fs[8]={0xdeadbeef,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    const uint32_t patterns[][4]={
        {0,0,0,0},{0x3f800000,0xbf800000,0x40000000,0x40800000},
        {0x80000000,1,0x007fffff,0x00800000},
        {0x7f800000,0xff800000,0x7fc12345,0x7f812345},
        {0x7f7fffff,0xff7fffff,0xffffffff,0x80000001}};
    riff::Sphere sphere;
    unsigned char sphereBefore[sizeof(sphere)];
    fill(&sphere,sizeof(sphere),91);
    for(unsigned i=0;i<sizeof(sphere);++i) sphereBefore[i]=reinterpret_cast<unsigned char*>(&sphere)[i];
    unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<4;++mode) {
        unsigned csr=(saved & ~0x6000u) | (mode<<13);
        test_set_mxcsr(csr);
        for(unsigned p=0;p<5;++p) for(unsigned alias=0;alias<3;++alias) {
            Guarded a,b,initial;
            fill(&a,sizeof(a),p+17); fill(&b,sizeof(b),p+17); fill(&initial,sizeof(initial),p+17);
            riff::Vector4 direction,prior;
            setBits(direction,patterns[p]); setBits(prior,patterns[p]);
            setBits(a.value,patterns[4-p]); setBits(b.value,patterns[4-p]);
            const riff::Vector4* da=alias==0 ? &direction : alias==1 ? &a.value : 0;
            const riff::Vector4* db=alias==0 ? &direction : alias==1 ? &b.value : 0;
            if(original_sphere_support_without_margin(&sphere,&a.value,da)!=&a.value) return 2;
            if(test_get_fs_head()!=fs[0] || test_get_mxcsr()!=csr) return 3;
            if(sphere.supportWithoutMargin(&b.value,db)!=&b.value) return 4;
            if(!equal(&a,&b,sizeof(a))) return 5;
            const unsigned char* bytes=reinterpret_cast<const unsigned char*>(&a.value);
            for(unsigned i=0;i<16;++i) if(bytes[i]!=0) return 6;
            if(!equal(a.before,initial.before,16)||!equal(a.after,initial.after,16)) return 7;
            if(!equal(&direction,&prior,16)||!equal(&sphere,sphereBefore,sizeof(sphere))) return 8;
            if(test_get_mxcsr()!=csr || test_get_fs_head()!=fs[0]) return 9;
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
