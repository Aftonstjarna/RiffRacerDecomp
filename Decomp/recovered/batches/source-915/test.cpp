#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_remove_active_locals(Compiler*, int32_t);
static_assert(sizeof(Local)==12, "local stride");
static_assert(offsetof(Symbols,locals)==0x18, "locals");
static_assert(offsetof(Function,position)==0x18, "position");
static_assert(offsetof(Function,active_count)==0x32, "active count");
static_assert(offsetof(Function,active_indices)==0xac, "indices");
static_assert(offsetof(Compiler,function)==0x1c, "function");
extern "C" void* memset(void* p,int v,unsigned n) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i)b[i]=(unsigned char)v; return p; }
extern "C" void* memcpy(void* p,const void* q,unsigned n) { unsigned char* b=(unsigned char*)p; const unsigned char* a=(const unsigned char*)q; for(unsigned i=0;i<n;++i)b[i]=a[i]; return p; }
static Local locals_a[65536], locals_b[65536];
static Function a,b;
static Symbols sa,sb;
static Compiler ca,cb;
static bool same(const void* x,const void* y,unsigned n) { const unsigned char* p=(const unsigned char*)x; const unsigned char* q=(const unsigned char*)y; for(unsigned i=0;i<n;++i)if(p[i]!=q[i])return false; return true; }
static int run(unsigned count,int target,unsigned pattern,uint32_t position) {
    memset(&a,0xa5,sizeof(a)); memset(&sa,0x63,sizeof(sa)); memset(&ca,0x97,sizeof(ca));
    for(unsigned i=0;i<65536;++i) { locals_a[i].name=i^0x98765432u; locals_a[i].flags=i*17; locals_a[i].end_position=0xdeadbeef; }
    a.active_count=(uint8_t)count; a.position=position;
    for(unsigned i=0;i<256;++i)a.active_indices[i]=(uint16_t)(pattern==0 ? i : pattern==1 ? 65535-i : i%3);
    memcpy(locals_b,locals_a,sizeof(locals_a)); b=a; sb=sa; cb=ca;
    sa.locals=locals_a; sb.locals=locals_b; a.symbols=&sa; b.symbols=&sb; ca.function=&a; cb.function=&b;
    original_script_remove_active_locals(&ca,target);
    cb.remove_active_locals(target);
    if(!same(locals_a,locals_b,sizeof(locals_a)))return 1;
    const unsigned expected=target<(int)count ? (unsigned)target : count;
    if(a.active_count!=expected || b.active_count!=expected)return 2;
    for(unsigned i=0;i<65536;++i) {
        bool touched=false;
        for(unsigned j=expected;j<count;++j)if(a.active_indices[j]==i)touched=true;
        if(locals_a[i].name!=(i^0x98765432u) || locals_a[i].flags!=i*17 || locals_a[i].end_position!=(touched?position:0xdeadbeef))return 3;
    }
    // Normalize only relocated pointer fields before comparing every byte.
    a.symbols=0; b.symbols=0; sa.locals=0; sb.locals=0; ca.function=0; cb.function=0;
    if(!same(&a,&b,sizeof(a)) || !same(&sa,&sb,sizeof(sa)) || !same(&ca,&cb,sizeof(ca)))return 4;
    const unsigned char* bytes=(const unsigned char*)&a;
    for(unsigned i=4;i<0xac;++i)if(!(i>=0x18 && i<0x1c) && i!=0x32 && bytes[i]!=0xa5)return 5;
    for(unsigned i=0;i<256;++i)if(a.active_indices[i]!=(uint16_t)(pattern==0?i:pattern==1?65535-i:i%3))return 6;
    if(a.position!=position)return 7;
    return 0;
}
extern "C" int test_main() {
    const unsigned counts[]={0,1,2,127,128,254,255};
    for(unsigned c=0;c<7;++c)for(unsigned p=0;p<3;++p) {
        const int targets[]={0,1,(int)counts[c],(int)counts[c]+1,255,256,2147483647};
        for(unsigned t=0;t<7;++t) { int r=run(counts[c],targets[t],p,(t&1)?0xffffffffu:0); if(r)return r; }
    }
    return 0;
}
