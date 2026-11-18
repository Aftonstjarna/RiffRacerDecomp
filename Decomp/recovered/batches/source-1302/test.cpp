#include "impl.hpp"
#include <stdint.h>
extern "C" Record40* __attribute__((fastcall)) original_record40_range_copy(const Record40*, const Record40*, Record40*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

static uint32_t fs_storage[16];
static Record40 a[8], b[8];
static int compare() {
    for (unsigned i=0;i<8;++i)
        for (unsigned j=0;j<10;++j)
            if (a[i].words[j]!=b[i].words[j]) return 1;
    return 0;
}
static void reset() {
    for (unsigned i=0;i<8;++i)
        for (unsigned j=0;j<10;++j)
            a[i].words[j]=b[i].words[j]=0x12345678u+i*101+j*7;
}
static int run(unsigned src, unsigned count, unsigned dst, unsigned head) {
    reset();
    Record40* x=record40_range_copy(a+src,a+src+count,a+dst);
    Record40* y=original_record40_range_copy(b+src,b+src+count,b+dst);
    if (test_get_fs_head()!=head) return 1;
    return x != a+dst+count || y != b+dst+count || compare();
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if (test_install_fs(fs_storage)!=0) return 1;
    unsigned head=test_get_fs_head();
    if (head!=fs_storage[0]) return 2;
    if (run(0,0,3,head) || run(0,1,4,head) || run(0,3,4,head) ||
        run(0,4,0,head) || run(0,4,1,head) || run(1,4,0,head)) return 3;
    // A one-word displacement makes the individual load/store order observable.
    reset();
    Record40* shifted_a=reinterpret_cast<Record40*>(&a[0].words[1]);
    Record40* shifted_b=reinterpret_cast<Record40*>(&b[0].words[1]);
    Record40* overlap_a=record40_range_copy(a,a+2,shifted_a);
    Record40* overlap_b=original_record40_range_copy(b,b+2,shifted_b);
    if (test_get_fs_head()!=head || overlap_a!=shifted_a+2 ||
        overlap_b!=shifted_b+2 || compare()) return 6;
    reset();
    Record40* x=record40_range_copy(a,a+1,0);
    Record40* y=original_record40_range_copy(b,b+1,0);
    if (test_get_fs_head()!=head || reinterpret_cast<uintptr_t>(x)!=40 ||
        reinterpret_cast<uintptr_t>(y)!=40 || compare()) return 4;
    x=record40_range_copy(a,a,0);
    y=original_record40_range_copy(b,b,0);
    if (test_get_fs_head()!=head || x || y || compare()) return 5;
    return 0;
}
