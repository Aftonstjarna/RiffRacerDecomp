#include "impl.hpp"
extern "C" int __attribute__((cdecl)) original_byte_range_compare(const void*, const void*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static unsigned char a[100], b[100], saved_a[100], saved_b[100];
static int check(const void* x, const void* y, uint32_t n, int expected) {
    for (unsigned i=0;i<100;++i) { saved_a[i]=a[i]; saved_b[i]=b[i]; }
    const int original = original_byte_range_compare(x,y,n);
    const int recovered = byte_range_compare(x,y,n);
    if (original != expected || recovered != original) return 1;
    for (unsigned i=0;i<100;++i)
        if (a[i]!=saved_a[i] || b[i]!=saved_b[i]) return 2;
    return 0;
}
extern "C" int test_main() {
    if (check(0,0,0,0)) return 1;
    // Exhaust all unsigned single-byte pairs, including high-bit values.
    for (unsigned x=0;x<256;++x) for (unsigned y=0;y<256;++y) {
        a[0]=static_cast<unsigned char>(x); b[0]=static_cast<unsigned char>(y);
        if (check(a,b,1,x==y?0:(x<y?-1:1))) return 2;
    }
    for (unsigned ao=0;ao<4;++ao) for (unsigned bo=0;bo<4;++bo)
    for (unsigned n=0;n<=80;++n) {
        for (unsigned i=0;i<100;++i) { a[i]=0xa5; b[i]=0x5a; }
        for (unsigned i=0;i<n;++i) a[ao+i]=b[bo+i]=static_cast<unsigned char>(i*73);
        if (check(a+ao,b+bo,n,0) || check(a+ao,a+ao,n,0)) return 3;
        for (unsigned pos=0;pos<n;++pos) {
            unsigned char old=a[ao+pos];
            a[ao+pos]=0; b[bo+pos]=255;
            if (check(a+ao,b+bo,n,-1) || check(b+bo,a+ao,n,1)) return 4;
            // Opposite later mismatch must not affect first-mismatch order.
            if (pos+1<n) {
                unsigned char next=a[ao+pos+1];
                a[ao+pos+1]=255; b[bo+pos+1]=0;
                if (check(a+ao,b+bo,n,-1)) return 5;
                a[ao+pos+1]=b[bo+pos+1]=next;
            }
            a[ao+pos]=b[bo+pos]=old;
        }
    }
    // Overlap is safe because neither routine writes.
    for (unsigned i=0;i<100;++i) a[i]=static_cast<unsigned char>(i);
    if (check(a,a+1,80,-1) || check(a+1,a,80,1)) return 6;
    test_write("byte-range-compare: passed\n",27);
    return 0;
}
