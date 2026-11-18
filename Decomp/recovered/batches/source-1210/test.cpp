#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_worker_byte_vector_append(WorkerByteVector*, const unsigned char*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned calls, requested;
static unsigned char relocated[128];
void WORKER_THISCALL WorkerByteVector::grow(unsigned count) {
    ++calls; requested=count;
    unsigned n=(unsigned)(reinterpret_cast<uintptr_t>(last)-reinterpret_cast<uintptr_t>(first));
    for(unsigned i=0;i<n;++i) relocated[i]=first[i];
    first=relocated; last=relocated+n; capacity_end=relocated+128;
}
static unsigned char a[128], b[128];
extern "C" int test_main() {
    unsigned fs[8]={0x13579bdf,0,0,0,0,0,0,0};
    if(test_install_fs(fs)) return 1;
    for(unsigned n=0;n<24;++n) for(unsigned src=0;src<100;++src) {
        for(unsigned i=0;i<128;++i) a[i]=b[i]=(unsigned char)(i*37+n*7+src);
        WorkerByteVector x={a+20,a+20+n,a+110}, y={b+20,b+20+n,b+110};
        unsigned char expected=a[src];
        original_worker_byte_vector_append(&y,b+src);
        if(test_get_fs_head()!=fs[0]) return 2;
        x.append(a+src);
        if(calls || x.first!=a+20 || y.first!=b+20 || x.last!=a+21+n || y.last!=b+21+n || x.capacity_end!=a+110 || y.capacity_end!=b+110) return 3;
        if(a[20+n]!=expected) return 4;
        for(unsigned i=0;i<128;++i) if(a[i]!=b[i]) return 5;
    }
    WorkerByteVector x={0,0,reinterpret_cast<unsigned char*>(1)}, y=x;
    original_worker_byte_vector_append(&y,0);
    if(test_get_fs_head()!=fs[0]) return 6;
    x.append(0);
    if(x.first!=y.first || x.last!=y.last || x.capacity_end!=y.capacity_end || reinterpret_cast<uintptr_t>(x.last)!=1) return 7;
    // Source-only contract tests: relocation must rebase an internal alias,
    // whereas an external pointer remains unchanged.
    for(unsigned i=0;i<16;++i) a[i]=(unsigned char)(i+31);
    x.first=a; x.last=a+16; x.capacity_end=a+16;
    x.append(a+5);
    if(calls!=1 || requested!=1 || x.first!=relocated || x.last!=relocated+17 || relocated[16]!=36) return 8;
    unsigned char external=0xa7;
    x.first=a; x.last=a+16; x.capacity_end=a+16;
    x.append(&external);
    if(calls!=2 || requested!=1 || relocated[16]!=0xa7 || x.last!=relocated+17) return 9;
    return 0;
}
