#include "impl.hpp"
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// The original uses ECX, EDX, and a caller-cleaned stack argument. GCC's
// fastcall declaration places the arguments correctly but assumes callee cleanup.
// A separate O0 frame restores ESP on return from this test-only adapter.
extern "C" void* __attribute__((fastcall)) original_worker_record40_range_transfer(const void*, const void*, void*);
__attribute__((noinline)) static void* oracle(const void* a, const void* b, void* d) {
    return original_worker_record40_range_transfer(a,b,d);
}
static unsigned char a[512], b[512];
static int trial(unsigned src, unsigned count, unsigned dst) {
    for (unsigned i=0;i<512;++i) a[i]=b[i]=(unsigned char)(i*73+19);
    void* result = worker_record40_range_transfer(a+src,a+src+40*count,a+dst);
    unsigned fs = test_get_fs_head();
    void* expected = oracle(b+src,b+src+40*count,b+dst);
    if (test_get_fs_head()!=fs) return 1;
    if ((unsigned char*)result-a != (unsigned char*)expected-b) return 2;
    for (unsigned i=0;i<512;++i) if(a[i]!=b[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    unsigned fs_storage[4]={0x12345678,0,0,0};
    if(test_install_fs(fs_storage)!=0 || test_get_fs_head()!=fs_storage[0]) return 1;
    const unsigned cases[][3]={{40,0,200},{40,1,200},{41,3,250},{80,3,80}, {80,3,81},{80,3,84},{80,3,96},{80,3,120},{120,3,80},{80,3,79},{80,3,76}};
    for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i)
        if(trial(cases[i][0],cases[i][1],cases[i][2])) return 2+i;
    // Null destination skips the first record; one-record range avoids a later
    // write to address 40. Empty ranges never touch even invalid pointers.
    void* p=worker_record40_range_transfer(a,a+40,0);
    void* q=oracle(b,b+40,0);
    if(p!=q || (uintptr_t)p!=40 || test_get_fs_head()!=fs_storage[0]) return 20;
    p=worker_record40_range_transfer(0,0,(void*)7);
    q=oracle(0,0,(void*)7);
    if(p!=q || (uintptr_t)p!=7 || test_get_fs_head()!=fs_storage[0]) return 21;
    return 0;
}
