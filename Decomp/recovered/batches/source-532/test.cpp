#include "impl.hpp"
extern "C" Matrix3* __attribute__((thiscall)) original_matrix3_construct_refs(
    Matrix3*, const uint32_t*, const uint32_t*, const uint32_t*,
    const uint32_t*, const uint32_t*, const uint32_t*,
    const uint32_t*, const uint32_t*, const uint32_t*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);

struct Guarded {
    uint32_t before[4];
    Matrix3 matrix;
    uint32_t after[4];
};
static void init(Guarded& x, unsigned seed) {
    for (unsigned j=0;j<4;++j) {
        x.before[j] = 0xdead0000u + j;
        x.after[j] = 0xbeef0000u + j;
    }
    for (unsigned j=0;j<12;++j) x.matrix.words[j]=seed ^ (0x1020304u * (j+1));
}
static bool equal(const Guarded& a, const Guarded& b) {
    for (unsigned j=0;j<4;++j)
        if (a.before[j]!=b.before[j] || a.after[j]!=b.after[j]) return false;
    for (unsigned j=0;j<12;++j)
        if (a.matrix.words[j]!=b.matrix.words[j]) return false;
    return true;
}
// map 0..11 aliases destination; 12..20 selects external input.
static int run_case(const unsigned* map, unsigned seed, unsigned mode) {
    Guarded a,b;
    init(a,seed); init(b,seed);
    const uint32_t edge[9]={0,0x80000000u,0x3f800000u,0xbf800000u,
        0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,0x00000001u};
    uint32_t inputs[9];
    for (unsigned j=0;j<9;++j) inputs[j]= mode==0 ? edge[j] :
        mode==1 ? 0 : (seed ^ (0x9e3779b9u*(j+1)));
    const uint32_t *pa[9], *pb[9];
    for (unsigned j=0;j<9;++j) {
        pa[j]=map[j]<12 ? &a.matrix.words[map[j]] : &inputs[map[j]-12];
        pb[j]=map[j]<12 ? &b.matrix.words[map[j]] : &inputs[map[j]-12];
    }
    const unsigned csr=test_get_mxcsr();
    Matrix3* ra=a.matrix.construct_refs(*pa[0],*pa[1],*pa[2],*pa[3],*pa[4],*pa[5],*pa[6],*pa[7],*pa[8]);
    if (ra!=&a.matrix || test_get_mxcsr()!=csr) return 1;
    Matrix3* rb=original_matrix3_construct_refs(&b.matrix,pb[0],pb[1],pb[2],pb[3],pb[4],pb[5],pb[6],pb[7],pb[8]);
    if (rb!=&b.matrix || test_get_mxcsr()!=csr || !equal(a,b)) return 2;
    for (unsigned j=0;j<9;++j) {
        const uint32_t expected= mode==0 ? edge[j] : mode==1 ? 0 : (seed ^ (0x9e3779b9u*(j+1)));
        if (inputs[j]!=expected) return 3;
    }
    for (unsigned j=0;j<4;++j)
        if (a.before[j]!=0xdead0000u+j || a.after[j]!=0xbeef0000u+j) return 6;
    for (unsigned j=3;j<12;j+=4) if (a.matrix.words[j]!=0) return 4;
    // Explicit copy expectations for the nonaliasing case.
    if (map[0]==12 && map[1]==13 && map[2]==14 && map[3]==15 &&
        map[4]==16 && map[5]==17 && map[6]==18 && map[7]==19 && map[8]==20)
        for (unsigned j=0;j<9;++j) if (a.matrix.words[j+j/3]!=inputs[j]) return 5;
    return 0;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    // Both ordinary and flush/denormals-are-zero modes; copies must not change flags.
    for (unsigned mode=0;mode<2;++mode) {
        test_set_mxcsr(mode ? 0x9fc0u : 0x1f80u);
        unsigned map[9];
        for (unsigned j=0;j<9;++j) map[j]=12+j;
        for (unsigned m=0;m<3;++m) if (run_case(map,0x12345678u,m)) return 10;
        // Every individual input aliases every word, with other inputs external.
        for (unsigned arg=0;arg<9;++arg) for (unsigned word=0;word<12;++word) {
            for (unsigned j=0;j<9;++j) map[j]=12+j;
            map[arg]=word;
            if (run_case(map,0xa5a5a5a5u,0)) return 11;
        }
        // All arguments reference the same word, including padding.
        for (unsigned word=0;word<12;++word) {
            for (unsigned j=0;j<9;++j) map[j]=word;
            if (run_case(map,0xffffffffu,2)) return 12;
        }
        // Mixed chains exercise dependencies across row boundaries.
        unsigned rng=0x7bad1234u;
        for (unsigned n=0;n<1024;++n) {
            for (unsigned j=0;j<9;++j) { rng=rng*1664525u+1013904223u; map[j]=(rng>>16)%21; }
            if (run_case(map,rng,2)) return 13;
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
