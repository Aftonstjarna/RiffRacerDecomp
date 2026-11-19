#include "impl.hpp"
extern "C" uint32_t* __attribute__((thiscall)) original_input_pointer_get(InputPointer*, uint32_t*);

struct Fixture { InputPointer input; uint32_t tail[4]; };
static void init(Fixture& f, unsigned flag, uint32_t x, uint32_t y) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&f);
    for (unsigned i=0; i<sizeof(f); ++i) p[i] = static_cast<unsigned char>(i*37u+11u);
    f.input.pointer_words[0]=x; f.input.pointer_words[1]=y;
    f.input.suppress_pointer=static_cast<uint8_t>(flag);
}
static bool equal(const Fixture& a, const Fixture& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0; i<sizeof(a); ++i) if (x[i]!=y[i]) return false;
    return true;
}
static bool run(unsigned flag, uint32_t x, uint32_t y, unsigned dest) {
    Fixture a,b; init(a,flag,x,y); init(b,flag,x,y);
    uint32_t external_a[4]={0x12345678,0xabcdef01,0x87654321,0xfedcba98};
    uint32_t external_b[4]={0x12345678,0xabcdef01,0x87654321,0xfedcba98};
    // dest 0 external; 1 and 2 overlap the source words in both directions.
    uint32_t* pa=dest==0 ? &external_a[1] : (dest==1 ? &a.input.pointer_words[0] : &a.input.pointer_words[1]);
    uint32_t* pb=dest==0 ? &external_b[1] : (dest==1 ? &b.input.pointer_words[0] : &b.input.pointer_words[1]);
    if (a.input.get_pointer(pa)!=pa || original_input_pointer_get(&b.input,pb)!=pb) return false;
    if (!equal(a,b)) return false;
    for (unsigned i=0;i<4;++i) if (external_a[i]!=external_b[i]) return false;
    if (dest==0 && (external_a[0]!=0x12345678 || external_a[3]!=0xfedcba98 ||
        external_a[1]!=(flag ? 0u : x) || external_a[2]!=(flag ? 0u : y))) return false;
    return true;
}
extern "C" int test_main() {
    for (unsigned flag=0;flag<256;++flag) {
        if (!run(flag,0x12345678,0xabcdef01,0) || !run(flag,0xffffffff,0x80000000,1) ||
            !run(flag,0x01234567,0x89abcdef,2)) return 1;
    }
    if (!run(0,0,0,0) || !run(0,0xffffffff,0,0)) return 2;
    return 0;
}
