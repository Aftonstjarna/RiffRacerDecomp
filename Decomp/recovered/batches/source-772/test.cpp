#include "impl.hpp"
// Custom ABI, NOT MS fastcall: unused EAX, EDX=last, ECX=first,
// destination on stack and caller cleanup. No thiscall member is involved.
extern "C" unsigned char* original_record520_range_copy_construct(unsigned,
    const unsigned char*, const unsigned char*, unsigned char*)
    __attribute__((regparm(3)));
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];
static unsigned char actual[4096], expected[4096], before[4096];
static int run(unsigned src, unsigned dst, unsigned count) {
    for (unsigned i=0; i<4096; ++i) {
        unsigned char v=static_cast<unsigned char>((i*37u)^(i>>3)^0xa5u);
        actual[i]=expected[i]=before[i]=v;
    }
    unsigned char* a=riff::construct_record520_range(actual+src,
        actual+src+count*520, actual+dst);
    unsigned char* b=original_record520_range_copy_construct(0,
        expected+src+count*520, expected+src, expected+dst);
    if (test_get_fs_head()!=fs_storage[0]) return 1;
    if (a!=actual+dst+count*520 || b!=expected+dst+count*520) return 2;
    for (unsigned i=0; i<4096; ++i) {
        if (actual[i]!=expected[i]) return 3;
        if ((i<dst || i>=dst+count*520) && actual[i]!=before[i]) return 4;
    }
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678u;
    if (test_install_fs(fs_storage)!=0) return 1;
    if (riff::construct_record520_range(0,0,0)!=0) return 2;
    if (original_record520_range_copy_construct(0,0,0,0)!=0) return 3;
    if (test_get_fs_head()!=fs_storage[0]) return 4;
    // Single null destination skips all source access, including invalid source.
    const unsigned char* p=reinterpret_cast<const unsigned char*>(0x12340000u);
    const unsigned char* q=reinterpret_cast<const unsigned char*>(0x12340208u);
    if (riff::construct_record520_range(p,q,0)!=reinterpret_cast<unsigned char*>(520)) return 5;
    if (original_record520_range_copy_construct(0,q,p,0)!=reinterpret_cast<unsigned char*>(520)) return 6;
    if (test_get_fs_head()!=fs_storage[0]) return 7;
    const unsigned cases[][3]={
        {16,2200,0},{16,2200,1},{16,2200,3},{17,2203,2},
        {16,16,3},{16,536,3},{536,16,3},{32,33,3},
        {32,34,3},{32,35,3},{32,36,3},{35,32,3}};
    for (unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i) {
        int r=run(cases[i][0],cases[i][1],cases[i][2]);
        if (r) return 10+int(i)*5+r;
    }
    return 0;
}
