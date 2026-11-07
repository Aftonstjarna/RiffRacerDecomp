#include "impl.hpp"
extern "C" riff::Record68* __attribute__((thiscall)) original_record68_copy_construct(
    riff::Record68*, const riff::Record68*);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
namespace {
struct Arena { uint32_t before[4]; riff::Record68 records[4]; uint32_t after[4]; };
void fill(Arena& a, unsigned seed, unsigned kind) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&a);
    for (unsigned i=0;i<sizeof(a);++i) {
        seed=seed*1664525u+1013904223u;
        p[i]=static_cast<unsigned char>(kind==0 ? 0 : kind==1 ? 255 : kind==2 ? i : seed>>24);
    }
}
bool equal(const Arena& a,const Arena& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
}
extern "C" int test_main() {
    unsigned fs[8]={0x13579bdfu,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    for(unsigned kind=0;kind<4;++kind) for(unsigned seed=0;seed<32;++seed)
    for(unsigned src=0;src<4;++src) for(unsigned dst=0;dst<4;++dst) {
        Arena a,b,before;
        fill(a,seed,kind); fill(b,seed,kind); fill(before,seed,kind);
        if(original_record68_copy_construct(&b.records[dst],&b.records[src])!=&b.records[dst]) return 2;
        if(test_get_fs_head()!=fs[0] || fs[0]!=0x13579bdfu) return 3;
        if(a.records[dst].copy_construct(a.records[src])!=&a.records[dst]) return 4;
        if(!equal(a,b)) return 5;
        // Independent byte specification checks every byte outside destination,
        // including the source, adjacent records and both guard regions.
        const unsigned char* actual=reinterpret_cast<const unsigned char*>(&a);
        const unsigned char* saved=reinterpret_cast<const unsigned char*>(&before);
        unsigned offset=sizeof(a.before)+dst*68;
        unsigned source=sizeof(a.before)+src*68;
        for(unsigned i=0;i<sizeof(a);++i) {
            unsigned from=(i>=offset && i<offset+68)?source+i-offset:i;
            if(actual[i]!=saved[from]) return 6;
        }
    }
    test_write("record68 copy differential tests passed\n",40);
    return 0;
}
