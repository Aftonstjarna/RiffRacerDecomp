#include "impl.hpp"
// regparm(3) maps unused EAX, last EDX, first ECX; the fourth argument is
// caller-cleaned on stack. This exactly adapts the private original ABI.
extern "C" riff::Record68* __attribute__((regparm(3))) original_record68_range_copy(
    unsigned unused, const riff::Record68* last, const riff::Record68* first,
    riff::Record68* destination);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned fs_storage[8];
static riff::Record68 a[12], b[12];
static void initialize(unsigned seed) {
    for (unsigned r=0;r<12;++r) {
        for(unsigned w=0;w<13;++w)
            a[r].fields[w]=b[r].fields[w]=(seed+r*937U+w*71U)^0xfedcba98U;
        for(unsigned w=0;w<4;++w)
            a[r].tail[w]=b[r].tail[w]=(seed+r*113U+w*727U)^0x80000000U;
    }
}
static bool equal() {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
static int compare(unsigned first,unsigned count,unsigned dest) {
    initialize(first*31+count*7+dest);
    riff::Record68* expected=original_record68_range_copy(0,b+first+count,b+first,b+dest);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    riff::Record68* actual=riff::record68_range_copy(a+first,a+first+count,a+dest);
    if(expected!=b+dest+count || actual!=a+dest+count || !equal()) return 2;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfU;
    if(test_install_fs(fs_storage)!=0) return 10;
    for(unsigned n=0;n<=5;++n) {
        if(compare(0,n,6)) return 11; // disjoint, whole-array guards/source checked
        if(compare(2,n,2)) return 12; // exact alias
        if(compare(0,n,1)) return 13; // forward overlap propagation
        if(compare(1,n,0)) return 14; // backward overlap
    }
    // Empty null range and destination: no dereference.
    if(original_record68_range_copy(0,0,0,0)!=0) return 15;
    if(test_get_fs_head()!=fs_storage[0]) return 16;
    if(riff::record68_range_copy(0,0,0)!=0) return 17;
    // Single null destination skips even an inaccessible source.
    const riff::Record68* p=reinterpret_cast<const riff::Record68*>(0x1000U);
    const riff::Record68* q=reinterpret_cast<const riff::Record68*>(0x1044U);
    if(reinterpret_cast<uintptr_t>(original_record68_range_copy(0,q,p,0))!=68) return 18;
    if(test_get_fs_head()!=fs_storage[0]) return 19;
    if(reinterpret_cast<uintptr_t>(riff::record68_range_copy(p,q,0))!=68) return 20;
    test_write("record68 differential tests passed\n",35);
    return 0;
}
