#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_page_header_stream_id_le32(const PageHeaderView*);
extern "C" void test_write(const char*, unsigned);
struct Fixture {
    PageHeaderView view;
    uint32_t untouched[7];
};
static int check(uint32_t value, unsigned alignment, unsigned salt) {
    uint8_t data[80], before[80];
    for (unsigned i=0; i<80; ++i) data[i]=uint8_t(i*37+salt);
    uint8_t* header=data+alignment;
    for (unsigned i=0; i<4; ++i) header[14+i]=uint8_t(value>>(8*i));
    for (unsigned i=0; i<80; ++i) before[i]=data[i];
    Fixture f;
    f.view.header=header;
    for (unsigned i=0; i<7; ++i) f.untouched[i]=0x12345678u+i+salt;
    const uint32_t actual=f.view.stream_id_le32();
    const uint32_t original=original_page_header_stream_id_le32(&f.view);
    if (actual!=value || original!=value || actual!=original) return 1;
    if (f.view.header!=header) return 2;
    for (unsigned i=0; i<7; ++i)
        if (f.untouched[i]!=0x12345678u+i+salt) return 3;
    for (unsigned i=0; i<80; ++i) if (data[i]!=before[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    const uint32_t edges[]={0,1,0xffffffffu,0x80000000u,0x7fffffffu,
        0x12345678u,0x80ff01feu,0xff000000u,0x000000ffu};
    for (unsigned a=0; a<8; ++a) {
        for (unsigned i=0; i<sizeof(edges)/sizeof(edges[0]); ++i)
            if (check(edges[i],a,i)) return 1;
        // Every possible byte at every position, with both zero and one backgrounds.
        for (unsigned pos=0; pos<4; ++pos)
            for (unsigned b=0; b<256; ++b) {
                const uint32_t shift=pos*8;
                if (check(uint32_t(b)<<shift,a,b)) return 2;
                if (check((0xffffffffu & ~(0xffu<<shift)) | (uint32_t(b)<<shift),a,b)) return 3;
            }
    }
    uint32_t state=0x87654321u;
    for (unsigned i=0; i<4096; ++i) {
        state=state*1664525u+1013904223u;
        if (check(state,i%8,i)) return 4;
    }
    test_write("page-header-stream-id-le32: passed\n", sizeof("page-header-stream-id-le32: passed\n")-1);
    return 0;
}
