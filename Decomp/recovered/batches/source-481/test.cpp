#include "impl.hpp"
extern "C" const unsigned char* __attribute__((cdecl)) original_pe_section_lookup(const void*, uint32_t);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
namespace {
const unsigned capacity = 0x11000 + 65535u * 40u;
unsigned char image[capacity], saved[capacity];
unsigned table;
uint32_t fs_storage[8];
void put16(unsigned at, uint16_t v) { image[at] = static_cast<unsigned char>(v); image[at+1] = static_cast<unsigned char>(v >> 8); }
void put32(unsigned at, uint32_t v) { for (unsigned j=0;j<4;++j) image[at+j] = static_cast<unsigned char>(v >> (8*j)); }
void setup(unsigned nt, uint16_t opt, uint16_t count) {
    for (unsigned j=0;j<capacity;++j) image[j] = static_cast<unsigned char>(j*37u+11u);
    put32(0x3c,nt); put16(nt+6,count); put16(nt+0x14,opt);
    table=nt+24+opt;
}
void section(unsigned i, uint32_t start, uint32_t size) {
    put32(table+i*40+8,size); put32(table+i*40+12,start);
}
void snapshot() { for(unsigned j=0;j<capacity;++j) saved[j]=image[j]; }
bool check(uint32_t rva, int expected) {
    const unsigned char* want = expected < 0 ? 0 : image+table+static_cast<unsigned>(expected)*40;
    const unsigned char* a=original_pe_section_lookup(image,rva);
    if(test_get_fs_head()!=0x12345678u) return false;
    for(unsigned j=0;j<capacity;++j) if(image[j]!=saved[j]) return false;
    const unsigned char* b=pe_section_lookup(image,rva);
    if(a!=want || b!=a) return false;
    for(unsigned j=0;j<capacity;++j) if(image[j]!=saved[j]) return false;
    return true;
}
uint32_t seed=0x58ad1234u;
uint32_t random32() { seed=seed*1664525u+1013904223u; return seed; }
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678u;
    if(test_install_fs(fs_storage)!=0) return 5;
    setup(0x80,224,0); snapshot();
    if(!check(0,-1)||!check(0xffffffffu,-1)) return 1;
    // Overlaps, unsorted sections, zero size, overflow, and raw-size disagreement.
    setup(0x81,3,6);
    section(0,0x1000,0x100); section(1,0x1080,0x200);
    section(2,0,1); section(3,0x500,0);
    section(4,0xfffffff0u,0x30); section(5,0xfffffff0u,0xf);
    put32(table+16,0x80000000u); snapshot();
    const uint32_t inputs[]={0,1,0x4ff,0x500,0xfff,0x1000,0x107f,0x1080,0x10ff,0x1100,0x127f,0x1280,0xffffffefu,0xfffffff0u,0xfffffffeu,0xffffffffu};
    const int expected[]={2,-1,-1,-1,-1,0,0,0,0,1,1,-1,-1,5,5,-1};
    for(unsigned i=0;i<sizeof(inputs)/sizeof(inputs[0]);++i) if(!check(inputs[i],expected[i])) return 2;
    setup(0x100,65535,65535);
    for(unsigned i=0;i<65535;++i) section(i,0,0);
    section(65534,0x80000000u,1); snapshot();
    if(!check(0x80000000u,65534)||!check(0x80000001u,-1)) return 3;
    // Randomized ranges with explicit expected first-hit calculation.
    setup(0x98,240,32);
    uint32_t starts[32],sizes[32];
    for(unsigned i=0;i<32;++i) { starts[i]=random32(); sizes[i]=random32(); section(i,starts[i],sizes[i]); }
    snapshot();
    for(unsigned i=0;i<160;++i) {
        uint32_t r=i<32?starts[i]:random32(); int match=-1;
        for(unsigned j=0;j<32;++j) if(r>=starts[j] && r<static_cast<uint32_t>(starts[j]+sizes[j])) { match=static_cast<int>(j); break; }
        if(!check(r,match)) return 4;
    }
    test_write("pe-section-lookup passed\n",25);
    return 0;
}
