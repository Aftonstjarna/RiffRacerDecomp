#include "impl.hpp"
extern "C" void test_write(const char*, unsigned);
static void fill(void* p, unsigned n, unsigned char value) {
    auto b=static_cast<unsigned char*>(p); for(unsigned i=0;i<n;++i)b[i]=value;
}
static bool same(const void* a,const void* b,unsigned n) {
    auto x=static_cast<const unsigned char*>(a);
    auto y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
struct Guarded { u32 before; WideString s; u32 after; };
static int run(bool alias, bool heap, u32 length, u32 count, u32 unused) {
    Guarded a,b; fill(&a,sizeof(a),0xa5); fill(&b,sizeof(b),0xa5);
    WideString source; fill(&source,sizeof(source),0x6d);
    u16 backing[16]; for(unsigned i=0;i<16;++i)backing[i]=u16(0x410+i);
    if(heap)source.storage.heap=backing;
    else for(unsigned i=0;i<8;++i)source.storage.inline_data[i]=u16(0x510+i);
    source.length=length; source.capacity=heap?15:7;
    WideString saved=source; u16 saved_backing[16];
    for(unsigned i=0;i<16;++i)saved_backing[i]=backing[i];
    if(alias) { a.s=source; b.s=source; }
    Guarded initial=a;
    auto ra=original_wide_prefix_construct(alias?&a.s:&source,&a.s,unused,count);
    auto rb=recovered_wide_prefix_construct(alias?&b.s:&source,&b.s,unused,count);
    if(ra!=&a.s || rb!=&b.s || !same(&a,&b,sizeof(a)))return 1;
    if(a.s.capacity!=7 || a.s.length!=0 || a.s.storage.inline_data[0]!=0)return 2;
    // All storage except its first WCHAR must survive, as must both guards.
    auto expected=initial;
    expected.s.capacity=7; expected.s.length=0; expected.s.storage.inline_data[0]=0;
    if(!same(&a,&expected,sizeof(a)))return 3;
    if(!same(&source,&saved,sizeof(source)) ||
       !same(backing,saved_backing,sizeof(backing)))return 4;
    return 0;
}
extern "C" int test_main() {
    const u32 counts[]={0,1,7,8,0x7fffffffU,0xffffffffU};
    const u32 ignored[]={0,7,0xffffffffU};
    for(u32 unused:ignored)for(u32 count:counts)for(unsigned heap=0;heap<2;++heap) {
        // Empty source: all maximum counts clip to zero without dereferencing data.
        int e=run(false,heap,0,count,unused); if(e)return e;
        // Nonempty source, explicit empty prefix, including heap-selected source.
        e=run(false,heap,heap?15:7,0,unused); if(e)return 10+e;
        // Initialization precedes reading source length in the self-alias case.
        e=run(true,heap,heap?15:7,count,unused); if(e)return 20+e;
    }
    test_write("wide-prefix tests passed\n",25);
    return 0;
}
