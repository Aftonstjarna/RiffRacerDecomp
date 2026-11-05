#include "impl.hpp"
using recovered::Record44;
// GCC regparm(3) assigns EAX, EDX, ECX in that order and leaves stack
// cleanup to the caller. The unused EAX argument models this nonstandard
// original register ABI without code wrappers or misdeclaring fastcall (ret 4).
extern "C" Record44* __attribute__((regparm(3))) original_record44_copy_range(
    unsigned unused_eax, const Record44* end, const Record44* begin, Record44* destination);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];
static Record44 actual[14], expected[14], before[14];
static void fill(Record44* data, unsigned seed) {
    unsigned char* p = reinterpret_cast<unsigned char*>(data);
    for (unsigned i=0; i<sizeof(actual); ++i) p[i]=static_cast<unsigned char>((i*71+seed) ^ (i>>2));
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int run(unsigned source, unsigned destination, unsigned count, unsigned seed) {
    fill(actual,seed); fill(expected,seed); fill(before,seed);
    Record44* r=original_record44_copy_range(0,expected+source+count,expected+source,expected+destination);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    if(r!=expected+destination+count) return 2;
    if(recovered::copy_range(actual+source,actual+source+count,actual+destination)!=actual+destination+count) return 3;
    if(!equal(actual,expected,sizeof(actual))) return 4;
    // All bytes outside the destination, and all destination padding, survive.
    const unsigned char* a=reinterpret_cast<const unsigned char*>(actual);
    const unsigned char* b=reinterpret_cast<const unsigned char*>(before);
    for(unsigned i=0;i<sizeof(actual);++i) {
        bool touched=i>=destination*44 && i<(destination+count)*44;
        unsigned offset=i%44;
        if((!touched || (offset>=25 && offset<=27)) && a[i]!=b[i]) return 5;
    }
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdf;
    if(test_install_fs(fs_storage)!=0) return 10;
    if(original_record44_copy_range(0,0,0,0)!=0) return 11;
    if(test_get_fs_head()!=fs_storage[0]) return 12;
    if(recovered::copy_range(0,0,0)!=0) return 13;
    for(unsigned seed=0;seed<256;seed+=17) {
        // Includes empty, single, disjoint, identical and both overlap directions.
        const unsigned cases[][3]={{0,8,0},{0,8,1},{0,7,6},{1,1,8},{1,0,9},{0,1,9},{2,4,7},{4,2,7},{14,14,0}};
        for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);++i) {
            int error=run(cases[i][0],cases[i][1],cases[i][2],seed);
            if(error) return 20+error;
        }
    }
    return 0;
}
