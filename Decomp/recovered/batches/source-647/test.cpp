#include "impl.hpp"
extern "C" PolyhedralConvexAabb* __attribute__((thiscall))
 original_polyhedral_convex_aabb_construct(PolyhedralConvexAabb*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
struct Guarded { uint32_t before[4]; PolyhedralConvexAabb object; uint32_t after[4]; };
static void expected_word(unsigned char* p, unsigned offset, uint32_t value) {
    for (unsigned j=0;j<4;++j) p[offset+j]=static_cast<unsigned char>(value>>(8*j));
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<4;++mode) {
        unsigned control=(saved & ~0x603fu) | (mode<<13);
        test_set_mxcsr(control);
        for(unsigned seed=0;seed<256;++seed) {
            Guarded a,b;
            unsigned char expected[sizeof(Guarded)];
            unsigned char* x=reinterpret_cast<unsigned char*>(&a);
            unsigned char* y=reinterpret_cast<unsigned char*>(&b);
            for(unsigned i=0;i<sizeof(a);++i) {
                unsigned char v=static_cast<unsigned char>(seed==0?0:seed==1?255:(seed*73+i*29));
                x[i]=y[i]=expected[i]=v;
            }
            unsigned char* e=expected+offsetof(Guarded,object);
            expected_word(e,0,0x9fb030); expected_word(e,4,0x23); expected_word(e,8,0);
            for(unsigned j=0;j<3;++j) {
                expected_word(e,0xc+j*4,0x3f800000);
                expected_word(e,0x34+j*4,0x3f800000);
                expected_word(e,0x44+j*4,0xbf800000);
            }
            expected_word(e,0x18,0); expected_word(e,0x2c,0x3d23d70a);
            expected_word(e,0x40,0); expected_word(e,0x50,0); e[0x54]=0;
            for(unsigned repeat=0;repeat<2;++repeat) {
                if(a.object.initialize()!=&a.object) return 1;
                if(original_polyhedral_convex_aabb_construct(&b.object)!=&b.object) return 2;
                if(test_get_mxcsr()!=control) return 3;
                for(unsigned i=0;i<sizeof(a);++i)
                    if(x[i]!=y[i] || x[i]!=expected[i]) return 4;
            }
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
