#include "impl.hpp"
extern "C" riff::Matrix64* __attribute__((fastcall)) original_affine48_to_matrix64(riff::Matrix64*, const void*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*,unsigned);
uint32_t cookie __attribute__((section(".oracle_cookie"),used,aligned(4)))=0x13579bdf;
extern "C" void* memcpy(void* d,const void* s,unsigned n) {unsigned char* a=(unsigned char*)d;const unsigned char* b=(const unsigned char*)s;for(unsigned i=0;i<n;++i)a[i]=b[i];return d;}
extern "C" void* memset(void* d,int v,unsigned n) {unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)v;return d;}
static uint32_t randomState=0x872319ab;
static uint32_t randomBits(){randomState^=randomState<<13;randomState^=randomState>>17;randomState^=randomState<<5;return randomState;}
static const uint32_t special[]={0,0x80000000,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7fc12345,0x7f812345,1,0x80000001,0x007fffff,0x00800000,0x7f7fffff,0xff7fffff};
static int check(unsigned src,unsigned dst,unsigned mode) {
    // Whole-buffer comparisons cover guards, untouched source, and alias effects.
    uint32_t a[96],b[96],before[96];
    for(unsigned i=0;i<96;++i) a[i]=mode<14?special[(i+mode)%14]:randomBits();
    memcpy(b,a,sizeof(a));memcpy(before,a,sizeof(a));
    riff::Matrix64* da=(riff::Matrix64*)(a+dst);
    riff::Matrix64* db=(riff::Matrix64*)(b+dst);
    unsigned csr=test_get_mxcsr();
    if(original_affine48_to_matrix64(da,a+src)!=da)return 1;
    if(test_get_mxcsr()!=csr)return 2;
    if(db->fromAffine(b+src)!=db)return 3;
    if(test_get_mxcsr()!=csr)return 4;
    for(unsigned i=0;i<96;++i) {
        if(a[i]!=b[i])return 5;
        if((i<dst||i>=dst+16)&&a[i]!=before[i])return 6;
    }
    if(dst+16<=src || src+12<=dst) {
        for(unsigned r=0;r<3;++r)for(unsigned c=0;c<3;++c)
            if(a[dst+4*r+c]!=before[src+3*c+r])return 7;
        for(unsigned i=0;i<3;++i)if(a[dst+12+i]!=before[src+9+i])return 8;
    }
    for(unsigned r=0;r<4;++r)if(a[dst+4*r+3]!=0)return 9;
    return 0;
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    // All rounding modes and FTZ/DAZ combinations; move-only behavior preserves
    // bits and status flags regardless of floating point control settings.
    for(unsigned env=0;env<16;++env) {
        test_set_mxcsr(0x1f80 | ((env&3)<<13) | ((env&4)?0x8000:0) | ((env&8)?0x40:0));
        for(unsigned mode=0;mode<30;++mode) {
            for(unsigned dst=8;dst<=44;++dst) {
                int result=check(24,dst,mode);
                if(result){test_set_mxcsr(saved);return result;}
            }
        }
    }
    test_set_mxcsr(saved);
    test_write("affine48-to-matrix64: passed\n",28);
    return 0;
}
