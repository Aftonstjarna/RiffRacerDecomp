#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_collision_workspace_link_free_records(riff::CollisionWorkspace*);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
using riff::CollisionWorkspace;
using riff::CollisionRecord;
struct Arena { uint32_t before[8]; CollisionWorkspace workspace; CollisionRecord external[2]; uint32_t after[8]; };
static Arena arena;
static unsigned char input[sizeof(Arena)], expected[sizeof(Arena)];
static void copy(void* to, const void* from, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(to);
    const unsigned char* s = static_cast<const unsigned char*>(from);
    for (unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    fs_storage[0]=0xffffffffU;
    if(test_install_fs(fs_storage)!=0) return 7;
    const uint32_t counts[] = {0, 1, 0xffffff7fU, 0xffffff80U, 0xffffffffU, 0x12345678U};
    for(unsigned seed=0;seed<3;++seed) for(unsigned head=0;head<6;++head)
    for(unsigned c=0;c<6;++c) for(unsigned repeats=1;repeats<=2;++repeats) {
        unsigned char* bytes=reinterpret_cast<unsigned char*>(&arena);
        for(unsigned i=0;i<sizeof arena;++i) bytes[i]=static_cast<unsigned char>(i*37+seed*91+17);
        CollisionWorkspace& w=arena.workspace;
        w.free_count=counts[c];
        w.free_head = head==0 ? 0 : head==1 ? &arena.external[0] :
                      head==2 ? &w.records[0] : head==3 ? &w.records[64] :
                      head==4 ? &w.records[127] : &arena.external[1];
        copy(input,&arena,sizeof arena);
        for(unsigned k=0;k<repeats;++k) {
            original_collision_workspace_link_free_records(&w);
            if(test_get_fs_head()!=fs_storage[0]) return 8;
        }
        copy(expected,&arena,sizeof arena);
        copy(&arena,input,sizeof arena);
        for(unsigned k=0;k<repeats;++k) w.linkFreeRecords();
        // Same addresses for both executions: compare all pointers and all bytes,
        // including opaque payloads, padding, external heads, and guard regions.
        if(!equal(&arena,expected,sizeof arena)) return 1;
        if(w.mode!=9 || w.free_count!=uint32_t(counts[c]+128U*repeats) || w.free_head!=&w.records[0]) return 2;
        if(w.cleared_38 || w.cleared_263c) return 3;
        for(unsigned i=0;i<4;++i) if(w.cleared_28[i]) return 4;
        if(head<=1 && repeats==1) {
            for(unsigned i=0;i<128;++i) {
                if(w.records[i].previous!=(i ? &w.records[i-1] : 0)) return 5;
                CollisionRecord* next=i<127 ? &w.records[i+1] : head==1 ? &arena.external[0] : 0;
                if(w.records[i].next!=next) return 6;
            }
        }
    }
    test_write("collision workspace: 648 differential cases passed\n",51);
    return 0;
}
