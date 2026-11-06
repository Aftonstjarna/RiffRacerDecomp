#include "impl.hpp"
using riff::Record48;
using riff::RetainedHeader;
extern "C" Record48* __attribute__((thiscall)) original_record48_copy_retain(Record48*, const Record48*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(Record48) == 48, "original i386 layout");
static_assert(sizeof(RetainedHeader) == 8, "counter offset");
struct Resource { RetainedHeader header; uint32_t tail[3]; };
struct Arena { uint32_t before[4]; Record48 src; uint32_t middle[4]; Record48 dst; Resource resource[5]; uint32_t after[4]; };
static Arena arena;
static unsigned char initial[sizeof(Arena)], expected[sizeof(Arena)];
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* out = static_cast<unsigned char*>(d);
    const unsigned char* in = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) out[i]=in[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    const uint32_t counts[] = {0,1,0x7fffffffU,0xfffffffeU,0xffffffffU};
    for(unsigned mask=0;mask<16;++mask)
    for(unsigned duplicate=0;duplicate<2;++duplicate)
    for(unsigned self=0;self<2;++self)
    for(unsigned c=0;c<5;++c) {
        unsigned char* bytes=reinterpret_cast<unsigned char*>(&arena);
        for(unsigned i=0;i<sizeof(arena);++i) bytes[i]=static_cast<unsigned char>(i*37+mask);
        for(unsigned i=0;i<5;++i) arena.resource[i].header.references=counts[c];
        for(unsigned i=0;i<4;++i) {
            arena.src.retained[i]=(mask&(1U<<i)) ? &arena.resource[duplicate?0:i].header : 0;
            arena.dst.retained[i]=&arena.resource[4].header;
        }
        for(unsigned i=0;i<8;++i) arena.src.words[i]=(i&1)?0xffffffffU-i:0x80000000U+i;
        Record48* dest=self?&arena.src:&arena.dst;
        copy(initial,&arena,sizeof arena);
        if(dest->copyRetain(&arena.src)!=dest) return 1;
        for(unsigned r=0;r<5;++r) {
            uint32_t increments=0;
            for(unsigned i=0;i<4;++i) if((mask&(1U<<i)) && (duplicate?0:i)==r) ++increments;
            if(arena.resource[r].header.references!=counts[c]+increments) return 2;
        }
        if(!equal(dest->retained,arena.src.retained,sizeof(dest->retained)) ||
           !equal(dest->words,arena.src.words,sizeof(dest->words))) return 3;
        copy(expected,&arena,sizeof arena);
        copy(&arena,initial,sizeof arena);
        if(original_record48_copy_retain(dest,&arena.src)!=dest) return 4;
        // Same addresses are reused for both executions, allowing an exact
        // whole-arena comparison: guards, source, resource headers/tails,
        // prior destination resource and all raw record bits are included.
        if(!equal(expected,&arena,sizeof arena)) return 5;
    }
    test_write("record48: 640 cases passed\n",26);
    return 0;
}
