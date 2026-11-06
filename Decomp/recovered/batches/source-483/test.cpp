#include "impl.hpp"
extern "C" int __attribute__((cdecl)) original_pe32_image_validate(const void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned char arena[1024], before[1024];
static unsigned fsStorage[8];
static void put16(unsigned char* p, unsigned v) { p[0]=static_cast<unsigned char>(v); p[1]=static_cast<unsigned char>(v>>8); }
static void put32(unsigned char* p, unsigned v) { put16(p,v); put16(p+2,v>>16); }
static int check(unsigned char* base, int expected) {
    for (unsigned i=0;i<sizeof(arena);++i) before[i]=arena[i];
    int a=original_pe32_image_validate(base);
    if (test_get_fs_head()!=fsStorage[0]) return 1;
    if (a!=expected || pe32_image_validate(base)!=a) return 2;
    for (unsigned i=0;i<sizeof(arena);++i) if(arena[i]!=before[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    fsStorage[0]=0x12345678;
    if(test_install_fs(fsStorage)!=0) return 10;
    // Include unaligned bases/NT headers, negative wrapped offsets, and an
    // NT header at the last readable part of the fixture.
    const unsigned bases[]={128,129,512};
    const unsigned nts[]={1,64,257,998};
    for(unsigned b=0;b<3;++b) for(unsigned n=0;n<4;++n) {
        for(unsigned i=0;i<sizeof(arena);++i) arena[i]=static_cast<unsigned char>(i*73+19);
        unsigned char* base=arena+bases[b];
        unsigned char* nt=arena+nts[n];
        put16(base,0x5a4d); put32(base+0x3c,static_cast<unsigned>(nts[n]-bases[b]));
        put32(nt,0x4550); put16(nt+0x18,0x10b);
        if(check(base,1)) return 20;
        const unsigned magics[]={0,0x20b,0x107,0xffff,0x10a,0x110b};
        for(unsigned m=0;m<6;++m) { put16(nt+0x18,magics[m]); if(check(base,0)) return 21; }
        put16(nt+0x18,0x10b);
        for(unsigned bit=0;bit<32;++bit) { put32(nt,0x4550u^(1u<<bit)); if(check(base,0)) return 22; }
        put32(nt,0x4550);
        for(unsigned bit=0;bit<16;++bit) { put16(base,0x5a4du^(1u<<bit)); if(check(base,0)) return 23; }
    }
    // A rejected DOS signature must not follow an unusable e_lfanew.
    put16(arena,0); put32(arena+0x3c,0x7fffffff);
    if(check(arena,0)) return 24;
    test_write("pe32-image-validate: passed\n",28);
    return 0;
}
