#include "impl.hpp"
extern "C" void* __attribute__((regparm(3))) original_record56_range_transfer(unsigned, const void*, const void*, void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[16];
static unsigned char a[512], b[512];
static void init() { for (unsigned i=0;i<512;++i) a[i]=b[i]=(unsigned char)(i*37u+11u); }
static int same() { for (unsigned i=0;i<512;++i) if (a[i]!=b[i]) return 0; return 1; }
static int run(unsigned src, unsigned count, unsigned dst) {
    init();
    void* expected=original_record56_range_transfer(0,a+src+count*56,a+src,a+dst);
    if (test_get_fs_head()!=fs_storage[0]) return 1;
    void* actual=record56_range_transfer(b+src,b+src+count*56,b+dst);
    return !same() || (unsigned char*)expected-a != (unsigned char*)actual-b;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678;
    if (test_install_fs(fs_storage)!=0) return 1;
    if (run(20,0,300) || run(20,1,200) || run(7,3,260) ||
        run(60,2,60) || run(80,2,81) || run(81,2,80) ||
        run(100,2,116) || run(116,2,100) || run(30,2,86)) return 2;
    init();
    void* p=original_record56_range_transfer(0,a+56,a,0);
    if (test_get_fs_head()!=fs_storage[0] || p!=(void*)56 ||
        record56_range_transfer(b,b+56,0)!=(void*)56 || !same()) return 3;
    p=original_record56_range_transfer(0,a,a,0);
    if (test_get_fs_head()!=fs_storage[0] || p!=0 || record56_range_transfer(b,b,0)!=0 || !same()) return 4;
    return 0;
}
