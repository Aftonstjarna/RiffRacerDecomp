#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_record20_append(Record20Vector*, const void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[16];
static unsigned char replacement[256];
static int growth_calls;
void Record20Vector::ensure_spare(unsigned char* position) {
    ++growth_calls;
    unsigned n = static_cast<unsigned>(position - begin);
    for (unsigned i=0;i<n;++i) replacement[i]=begin[i];
    begin=replacement; end=replacement+n; capacity_end=replacement+sizeof(replacement);
}
static unsigned char a[256], b[256];
static int equal(const unsigned char* x,const unsigned char* y,unsigned n) {
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return 0;
    return 1;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678u;
    if(test_install_fs(fs_storage)!=0) return 1;
    unsigned head=test_get_fs_head();
    if(head!=fs_storage[0]) return 2;
    // External, internal (including interior byte offsets), boundary and
    // overlapping sources; compare the entire backing arrays and fields.
    const int offsets[]={0,1,19,20,21,39,40,41,45,55,59,60,61,70,80,100,180};
    for(unsigned k=0;k<sizeof(offsets)/sizeof(offsets[0]);++k) {
        for(unsigned i=0;i<256;++i) a[i]=b[i]=(unsigned char)(i*37u+k*13u);
        Record20Vector x={a+40,a+100,a+200}, y={b+40,b+100,b+200};
        original_record20_append(&x,a+offsets[k]);
        if(test_get_fs_head()!=head) return 3;
        y.append(b+offsets[k]);
        if(!equal(a,b,256) || x.begin!=a+40 || y.begin!=b+40 || x.end!=a+120 || y.end!=b+120 || x.capacity_end!=a+200 || y.capacity_end!=b+200) return 4;
    }
    // Null destination skips the copy but still advances the end pointer.
    Record20Vector x={0,0,reinterpret_cast<unsigned char*>(1)}, y=x;
    original_record20_append(&x,0);
    if(test_get_fs_head()!=head) return 5;
    y.append(0);
    if(x.begin!=y.begin || x.end!=y.end || x.capacity_end!=y.capacity_end || reinterpret_cast<uintptr_t>(x.end)!=20) return 6;
    // Independently check the dependency contract and source rebasing after a
    // relocating reserve; allocator behavior itself is outside this target.
    for(unsigned i=0;i<256;++i) a[i]=(unsigned char)(i*7u);
    Record20Vector z={a+20,a+80,a+80}; growth_calls=0;
    z.append(a+41);
    if(growth_calls!=1 || z.begin!=replacement || z.end!=replacement+80 || !equal(replacement+60,a+40,20)) return 7;
    return 0;
}
