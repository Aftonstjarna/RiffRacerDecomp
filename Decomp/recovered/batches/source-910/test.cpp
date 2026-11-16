#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_simplex_solver_reduce_vertices(
    SimplexSolverVertices*, const uint8_t*);
extern "C" void test_write(const char*, unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);

struct Fixture {
    uint32_t before[4];
    SimplexSolverVertices solver;
    uint8_t untouched[128];
    uint32_t after[4];
};
static void copyBytes(void* d, const void* s, unsigned n) {
    uint8_t* dst = static_cast<uint8_t*>(d);
    const uint8_t* src = static_cast<const uint8_t*>(s);
    for (unsigned i=0; i<n; ++i) dst[i]=src[i];
}
static bool equalBytes(const void* a,const void* b,unsigned n) {
    const uint8_t* x=static_cast<const uint8_t*>(a);
    const uint8_t* y=static_cast<const uint8_t*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void initialize(Fixture& a, int count, unsigned seed) {
    uint8_t* bytes=reinterpret_cast<uint8_t*>(&a);
    for(unsigned i=0;i<sizeof(a);++i) {
        seed=seed*1664525u+1013904223u;
        bytes[i]=static_cast<uint8_t>(seed>>24);
    }
    a.solver.vertexCount=count;
    // Include representations that would expose accidental floating operations.
    a.solver.difference[0].lane[0]=0x7f800001u;
    a.solver.supportA[1].lane[3]=0x80000000u;
    a.solver.supportB[2].lane[1]=1;
}
static int runCase(int count, unsigned mask, int aliasOffset, unsigned seed) {
    Fixture recovered, original, before;
    initialize(recovered,count,seed);
    uint8_t external=static_cast<uint8_t>(mask);
    if(aliasOffset>=4) reinterpret_cast<uint8_t*>(&recovered.solver)[aliasOffset]=external;
    copyBytes(&original,&recovered,sizeof(original));
    copyBytes(&before,&recovered,sizeof(before));
    const uint8_t* rm=aliasOffset<0 ? &external : reinterpret_cast<uint8_t*>(&recovered.solver)+aliasOffset;
    const uint8_t* om=aliasOffset<0 ? &external : reinterpret_cast<uint8_t*>(&original.solver)+aliasOffset;
    unsigned mxcsr=test_get_mxcsr();
    recovered.solver.reduceVertices(rm);
    if(test_get_mxcsr()!=mxcsr) return 1;
    original_simplex_solver_reduce_vertices(&original.solver,om);
    if(test_get_mxcsr()!=mxcsr) return 2;
    if(!equalBytes(&original,&recovered,sizeof(original))) return 3;
    if(external!=static_cast<uint8_t>(mask)) return 4;
    // Independent write-set check: only count and removed destination slots
    // may change, including all inactive slots and surrounding fields.
    bool changed[4]={false,false,false,false};
    int expectedCount=count;
    const uint8_t* bm=aliasOffset<0 ? &external : reinterpret_cast<uint8_t*>(&before.solver)+aliasOffset;
    // This extra check uses stable external masks; alias behavior is checked
    // by full original comparison above.
    if(aliasOffset<0) {
        for(int i=3;i>=0;--i) if(expectedCount>=i+1 && !(*bm & (1u<<i))) {
            --expectedCount; changed[i]=true;
        }
        if(recovered.solver.vertexCount!=expectedCount) return 5;
        const uint8_t* old=reinterpret_cast<const uint8_t*>(&before);
        const uint8_t* now=reinterpret_cast<const uint8_t*>(&recovered);
        for(unsigned i=0;i<sizeof(Fixture);++i) {
            bool allowed=false;
            unsigned base=offsetof(Fixture,solver);
            if(i>=base && i<base+4) allowed=true;
            for(unsigned array=0;array<3;++array) for(unsigned v=0;v<4;++v) {
                unsigned start=base+4+array*80+v*16;
                if(changed[v] && i>=start && i<start+16) allowed=true;
            }
            if(!allowed && now[i]!=old[i]) return 6;
        }
    }
    return 0;
}
extern "C" int test_main() {
    const int counts[]={-2147483647-1,-1,0,1,2,3,4,5};
    unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<2;++mode) {
        test_set_mxcsr(mode ? 0x9fc0u : 0x1f80u);
        for(unsigned c=0;c<sizeof(counts)/sizeof(counts[0]);++c)
            for(unsigned mask=0;mask<256;++mask) {
                int result=runCase(counts[c],mask,-1,mask+c*997+mode);
                if(result) return 10+result;
            }
    }
    // Every byte in all arrays and following solver fields can be the mask.
    for(int count=0;count<=5;++count) for(int offset=0;offset<0x174;++offset)
        for(unsigned mask=0;mask<16;++mask) {
            int result=runCase(count,mask,offset,offset*257+mask);
            if(result) return 20+result;
        }
    // Non-positive count short circuits before dereferencing even a null mask.
    SimplexSolverVertices a;
    for(int count=-1;count<=0;++count) {
        a.vertexCount=count;
        a.reduceVertices(0);
        original_simplex_solver_reduce_vertices(&a,0);
        if(a.vertexCount!=count) return 30;
    }
    test_set_mxcsr(saved);
    const char ok[]="simplex reduce: all differential checks passed\n";
    test_write(ok,sizeof(ok)-1);
    return 0;
}
