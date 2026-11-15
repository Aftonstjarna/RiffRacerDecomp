#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_sphere_batched_support_without_margin(
    const void*, const riff::Vector4*, riff::Vector4*, int32_t);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) b[i]=static_cast<unsigned char>(seed+i*73);
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
struct Buffer { riff::Vector4 v[261]; };
struct Object { unsigned char before[16]; riff::Sphere sphere; unsigned char after[79]; };
extern "C" int test_main() {
    unsigned fs[8]={0x13579bdfu,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    const unsigned saved=test_get_mxcsr();
    const int32_t counts[]={(-2147483647-1),-257,-1,0,1,2,6,17,257};
    const uint32_t patterns[]={0,0x80000000u,1,0x007fffffu,0x7f800000u,
        0xff800000u,0x7fc12345u,0x7f812345u,0x3f800000u,0x7f7fffffu};
    for(unsigned mode=0;mode<4;++mode) for(unsigned pat=0;pat<10;++pat)
    for(unsigned c=0;c<9;++c) for(unsigned alias=0;alias<4;++alias) {
        Buffer a,b,expected,dirs,dirsBefore;
        Object object;
        unsigned char objectBefore[sizeof(Object)];
        fill(&object,sizeof(object),pat+31);
        // Preserve all opaque bytes, including padding, without interpreting them.
        for(unsigned k=0;k<sizeof(object);++k)
            objectBefore[k]=reinterpret_cast<unsigned char*>(&object)[k];
        fill(&a,sizeof(a),pat+1); fill(&b,sizeof(b),pat+1);
        fill(&expected,sizeof(expected),pat+1);
        for(unsigned k=0;k<sizeof(dirs);++k) {
            unsigned char value=static_cast<unsigned char>(patterns[pat] >> ((k%4)*8));
            reinterpret_cast<unsigned char*>(&dirs)[k]=value;
            reinterpret_cast<unsigned char*>(&dirsBefore)[k]=value;
        }
        int32_t n=counts[c];
        if(n>0) for(unsigned k=16;k<16+static_cast<unsigned>(n)*16;++k)
            reinterpret_cast<unsigned char*>(&expected)[k]=0;
        riff::Vector4* oa=&a.v[1]; riff::Vector4* ob=&b.v[1];
        const riff::Vector4* da=alias==0?dirs.v:alias==1?0:alias==2?oa:oa+1;
        const riff::Vector4* db=alias==0?dirs.v:alias==1?0:alias==2?ob:ob+1;
        // Exercise null outputs on the no-access paths as well as guarded arrays.
        if(n<=0 && alias==1) { oa=0; ob=0; }
        unsigned mx=(saved & ~0x603fu) | (mode<<13) | 0x1f80u | 0x21u;
        test_set_mxcsr(mx);
        original_sphere_batched_support_without_margin(&object.sphere,da,oa,n);
        if(test_get_fs_head()!=fs[0] || test_get_mxcsr()!=mx) return 2;
        object.sphere.batchedSupportWithoutMargin(db,ob,n);
        if(test_get_fs_head()!=fs[0] || test_get_mxcsr()!=mx) return 3;
        if(!equal(&a,&b,sizeof(a)) || !equal(&a,&expected,sizeof(a))) return 4;
        if(!equal(&dirs,&dirsBefore,sizeof(dirs))) return 5;
        if(!equal(&object,objectBefore,sizeof(object))) return 6;
    }
    test_set_mxcsr(saved);
    test_write("sphere batch: passed\n",21);
    return 0;
}
