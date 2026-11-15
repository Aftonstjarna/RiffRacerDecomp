#include "impl.hpp"
using namespace riff;
extern "C" Node* __attribute__((fastcall)) original_script_table_main_bucket(const Table*, const Value*);
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
// Data only: original external dispatch table, NOT instruction bytes.
// Full local differential linking places these sections at their evidenced VAs.
// A coordinator lacking these mappings can still execute the default path.
extern "C" {
uint32_t oracle_dispatch[4] __attribute__((section(".oracle_dispatch"),used,aligned(4))) = {
    0x4f0150, 0x4f016a, 0x4f0127, 0x4f0133
};
uint32_t oracle_zero __attribute__((section(".oracle_zero"),used,aligned(4))) = 0;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void fill(void* p,unsigned n,unsigned seed) {
    unsigned char* b=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i) b[i]=static_cast<unsigned char>(seed+i*37);
}
static Node storage[256];
static unsigned char storageBefore[sizeof(storage)];
static unsigned calls;
static int check(uint32_t tag,uint32_t bits,unsigned exponent,unsigned mode,bool mapped) {
    struct Guarded { uint32_t before; Table table; uint32_t after; } g;
    fill(&g,sizeof(g),13);
    g.table.hashLog2=static_cast<uint8_t>(exponent);
    g.table.nodes=storage;
    Value key;
    fill(&key,sizeof(key),71);
    key.tag=tag;
    key.payload.bits=bits;
    StringHeader string;
    fill(&string,sizeof(string),87);
    string.hash=bits;
    if(tag==4) key.payload.string=&string;
    Guarded saved=g;
    Value savedKey=key;
    StringHeader savedString=string;
    uint32_t mask=(uint32_t(1)<<(exponent&31))-1;
    uint32_t index;
    if(tag==1 || tag==4) index=bits&mask;
    else if(tag==3 && ((bits&0x7fffffffu)==0 ||
            ((mode&0x40) && (bits&0x7f800000u)==0))) index=0;
    else index=bits%(mask|1u);
    uintptr_t expected=reinterpret_cast<uintptr_t>(storage)+uint32_t(index*20u);
    test_set_mxcsr(mode);
    Node* got=g.table.mainBucket(&key);
    unsigned recoveredMxcsr=test_get_mxcsr();
    if(reinterpret_cast<uintptr_t>(got)!=expected) return 1;
    if(!equal(&g,&saved,sizeof(g)) || !equal(&key,&savedKey,sizeof(key)) ||
       !equal(&string,&savedString,sizeof(string))) return 2;
    // Missing fixed data is explicitly reported, never treated as a full
    // original-path test. Default tags do not consult either fixture.
    if(mapped || tag==0 || tag>4) {
        test_set_mxcsr(mode);
        Node* original=original_script_table_main_bucket(&g.table,&key);
        ++calls;
        if(test_get_mxcsr()!=recoveredMxcsr) return 6;
        if(original!=got) return 3;
        if(!equal(&g,&saved,sizeof(g)) || !equal(&key,&savedKey,sizeof(key)) ||
           !equal(&string,&savedString,sizeof(string))) return 4;
    }
    if(!equal(storage,storageBefore,sizeof(storage))) return 5;
    return 0;
}
extern "C" int test_main() {
    unsigned savedMxcsr=test_get_mxcsr();
    bool mapped=reinterpret_cast<uintptr_t>(oracle_dispatch)==0x4f018c &&
                reinterpret_cast<uintptr_t>(&oracle_zero)==0xa063ec;
    fill(storage,sizeof(storage),19);
    for(unsigned i=0;i<sizeof(storage);++i)
        storageBefore[i]=reinterpret_cast<unsigned char*>(storage)[i];
    const uint32_t tags[]={0,1,2,3,4,5,6,7,0x7fffffffu,0x80000000u,0xffffffffu};
    const uint32_t values[]={0,1,2,3,7,15,31,255,256,0x80000000u,0xffffffffu,
        0x3f800000u,0xbf800000u,0x3fc00000u,0x7f800000u,0xff800000u,
        0x7fc00000u,0x7f800001u,0xffc12345u,0x007fffffu,0x80000001u};
    // Every byte-sized exponent, including masked shift counts 0,31,32,255.
    // Large bucket addresses are compared as addresses, never dereferenced.
    for(unsigned m=0;m<2;++m)
      for(unsigned e=0;e<256;++e)
       for(unsigned t=0;t<sizeof(tags)/sizeof(tags[0]);++t)
        for(unsigned v=0;v<sizeof(values)/sizeof(values[0]);++v) {
            int result=check(tags[t],values[v],e,0x1f80u|(m?0x40u:0),mapped);
            if(result) {test_set_mxcsr(savedMxcsr);return 10+result;}
        }
    test_set_mxcsr(savedMxcsr);
    if(!calls) return 20;
    if(mapped) {
        const char s[]="script-table-main-bucket: full mapped differential tests passed\n";
        test_write(s,sizeof(s)-1);
    } else {
        const char s[]="script-table-main-bucket: default-tag original comparisons passed; tags 1..4 require dispatch/zero fixture mappings\n";
        test_write(s,sizeof(s)-1);
    }
    return 0;
}
