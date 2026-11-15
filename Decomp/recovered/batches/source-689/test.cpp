#include "impl.hpp"
// Placement construction establishes the source object's lifetime in the arena.
void* operator new(__SIZE_TYPE__, void* p) noexcept { return p; }
extern "C" void __attribute__((thiscall)) original_transform64_serialize_copy(const Transform64*, void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned char oracle[256], recovered[256], before[256];
static unsigned fs_storage[16];
static uint32_t rng = 0x12345678u;
static unsigned char next_byte() {
    rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5;
    return static_cast<unsigned char>(rng);
}
static int run(unsigned source, unsigned destination, unsigned pattern) {
    Transform64* a = new (oracle + source) Transform64;
    Transform64* b = new (recovered + source) Transform64;
    for (unsigned i=0;i<256;++i) {
        unsigned char x = pattern == 0 ? static_cast<unsigned char>(i) :
            pattern == 1 ? 0 : pattern == 2 ? 255 : next_byte();
        oracle[i]=recovered[i]=before[i]=x;
    }
    // Include signed zero, infinities, quiet/signaling NaN representations.
    if (pattern == 4) {
        const uint32_t values[8]={0,0x80000000u,0x7f800000u,0xff800000u,
            0x7fc12345u,0x7f812345u,1,0xffffffffu};
        for(unsigned i=0;i<64;++i) {
            unsigned char v=static_cast<unsigned char>(values[(i/4)%8] >> ((i%4)*8));
            oracle[source+i]=recovered[source+i]=before[source+i]=v;
        }
    }
    unsigned head=test_get_fs_head();
    original_transform64_serialize_copy(a, oracle+destination);
    if(test_get_fs_head()!=head) return 1;
    b->serialize_copy(recovered+destination);
    for(unsigned i=0;i<256;++i) {
        if(oracle[i]!=recovered[i]) return 2;
        if((i<destination || i>=destination+64) && oracle[i]!=before[i]) return 3;
    }
    // Independent expected forward-word semantics, including overlap.
    for(unsigned i=0;i<64;i+=4) {
        unsigned char v[4];
        for(unsigned j=0;j<4;++j) v[j]=before[source+i+j];
        for(unsigned j=0;j<4;++j) before[destination+i+j]=v[j];
    }
    for(unsigned i=0;i<256;++i) if(oracle[i]!=before[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0) return 10;
    for(unsigned p=0;p<5;++p) {
        // Every overlap displacement, self-copy, adjacent and separated ranges.
        for(unsigned d=1;d<=191;++d) {
            int r=run(80,d,p); if(r) return 20+r;
        }
        // Source alignments independent of destination alignment.
        for(unsigned s=1;s<8;++s) {
            int r=run(s,160+s%4,p); if(r) return 30+r;
        }
    }
    test_write("transform64 copy passed\n",24);
    return 0;
}
