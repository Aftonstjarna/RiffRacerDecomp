#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" NarrowNode* __attribute__((thiscall)) original_narrow_tree_lower_bound(const NarrowTree*, const NarrowString*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(NarrowString)==24,"string layout");
static_assert(offsetof(NarrowNode,key)==16,"key offset");
static_assert(offsetof(NarrowNode,sentinel)==13,"sentinel offset");
static_assert(sizeof(NarrowNode)==40,"node layout");
struct Fixture {
    NarrowTree tree;
    uint32_t tree_tail[3];
    NarrowNode nodes[10];
    unsigned char heaps[10][80];
    NarrowString query;
    unsigned char query_heap[80];
};
static Fixture f;
static unsigned char saved[sizeof(Fixture)];
static unsigned calls;
static uint32_t fs_storage[8];
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static void fill(void* p, unsigned n, unsigned char c) {
    unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i)b[i]=c;
}
static void string_set(NarrowString& s, unsigned char* heap, const unsigned char* bytes, unsigned n, bool external) {
    fill(&s,sizeof(s),0xa7);
    s.length=n; s.capacity=external ? 79 : 15;
    unsigned char* dst=external ? heap : s.storage.local;
    if(external)s.storage.heap=heap;
    for(unsigned i=0;i<n;++i)dst[i]=bytes[i];
    dst[n]=0;
}
static void init() {
    fill(&f,sizeof(f),0x5b);
    f.tree.head=&f.nodes[0];
    for(unsigned i=0;i<10;++i){
        f.nodes[i].left=f.nodes[i].right=f.nodes[i].parent=&f.nodes[0];
        f.nodes[i].sentinel=i==0 ? 0x81 : 0;
    }
}
static bool check(NarrowNode* expected, const NarrowString* q) {
    const unsigned char* bytes=(const unsigned char*)&f;
    for(unsigned i=0;i<sizeof(f);++i)saved[i]=bytes[i];
    NarrowNode* original=original_narrow_tree_lower_bound(&f.tree,q);
    if(test_get_fs_head()!=fs_storage[0])return false;
    for(unsigned i=0;i<sizeof(f);++i)if(saved[i]!=bytes[i])return false;
    NarrowNode* recovered=f.tree.lower_bound(q);
    for(unsigned i=0;i<sizeof(f);++i)if(saved[i]!=bytes[i])return false;
    ++calls;
    return original==expected && recovered==original;
}
static int cmp(const unsigned char* a,unsigned na,const unsigned char* b,unsigned nb){
    unsigned n=na<nb?na:nb;
    for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return a[i]<b[i]?-1:1;
    return na<nb?-1:na!=nb;
}
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0)return 7;
    if(test_get_fs_head()!=fs_storage[0])return 8;
    init();
    if(!check(f.tree.head,0))return 1;
    // One-node searches cover chunk boundaries, prefix ties, byte positions,
    // high-bit values, embedded NULs, and every storage-mode pairing.
    unsigned char key[65], query[65];
    for(unsigned mode=0;mode<4;++mode)
    for(unsigned n=0;n<=32;++n)
    for(unsigned m=0;m<=32;++m){
        if((!(mode&1)&&n>15)||(!(mode&2)&&m>15))continue;
        for(unsigned variant=0;variant<36;++variant){
            for(unsigned j=0;j<65;++j) key[j]=query[j]=(unsigned char)((j*71)&255);
            if(variant<33)query[variant]^=0x80;
            if(variant==33){key[0]=0xff;query[0]=0x7f;}
            if(variant==34){key[0]=0;query[0]=0x80;}
            init(); f.nodes[0].parent=&f.nodes[1];
            string_set(f.nodes[1].key,f.heaps[1],key,n,mode&1);
            string_set(f.query,f.query_heap,query,m,mode&2);
            NarrowNode* expected=cmp(key,n,query,m)<0?f.tree.head:&f.nodes[1];
            if(!check(expected,&f.query))return 2;
        }
    }
    // Ordered keys with duplicates: balanced, all-left, and all-right trees.
    const unsigned char values[7]={0,1,1,64,127,128,255};
    for(unsigned shape=0;shape<3;++shape){
        init();
        for(unsigned i=1;i<=7;++i)string_set(f.nodes[i].key,f.heaps[i],&values[i-1],1,i&1);
        if(shape==0){
            f.nodes[0].parent=&f.nodes[4];
            f.nodes[4].left=&f.nodes[2];f.nodes[4].right=&f.nodes[6];
            f.nodes[2].left=&f.nodes[1];f.nodes[2].right=&f.nodes[3];
            f.nodes[6].left=&f.nodes[5];f.nodes[6].right=&f.nodes[7];
        }else if(shape==1){
            f.nodes[0].parent=&f.nodes[7];
            for(unsigned i=7;i>1;--i)f.nodes[i].left=&f.nodes[i-1];
        }else{
            f.nodes[0].parent=&f.nodes[1];
            for(unsigned i=1;i<7;++i)f.nodes[i].right=&f.nodes[i+1];
        }
        for(unsigned v=0;v<256;++v)for(unsigned external=0;external<2;++external){
            unsigned char b=(unsigned char)v;
            string_set(f.query,f.query_heap,&b,1,external!=0);
            unsigned i=0;while(i<7&&values[i]<v)++i;
            if(!check(i==7?f.tree.head:&f.nodes[i+1],&f.query))return 3;
        }
        string_set(f.query,f.query_heap,values,0,false);
        if(!check(&f.nodes[1],&f.query))return 4;
        const unsigned char beyond[2]={255,0};
        string_set(f.query,f.query_heap,beyond,2,false);
        if(!check(f.tree.head,&f.query))return 5;
    }
    if(calls<80000)return 6;
    test_write("lower-bound differential checks passed\n",39);
    return 0;
}
