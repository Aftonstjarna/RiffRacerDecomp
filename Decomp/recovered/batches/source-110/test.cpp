#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_range(WideString*,const uint16_t*,uint32_t);
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_substring(WideString*,const WideString*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
// Delegate the unrecovered helper to the accepted original; no replacement
// substring semantics are counted as recovered implementation.
WideString* RIFF_THISCALL WideString::assign_substring(const WideString* s,uint32_t p,uint32_t n) {
    return original_wide_assign_substring(this,s,p,n);
}
static unsigned unexpected;
void RIFF_THISCALL WideString::grow(uint32_t,uint32_t) { ++unexpected; }
void wide_length_error(const char*) { ++unexpected; }
void* wide_copy(void* d,const void* s,uint32_t n) {
    unsigned char* x=static_cast<unsigned char*>(d);
    const unsigned char* y=static_cast<const unsigned char*>(s);
    for(uint32_t i=0;i<n;++i)x[i]=y[i];
    return d;
}
static void fill(void* d,unsigned n,unsigned char v) {
    unsigned char* p=static_cast<unsigned char*>(d); for(unsigned i=0;i<n;++i)p[i]=v;
}
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
struct Guard { uint32_t pre[2]; WideString s; uint32_t post[2]; };
// kind 0=null, 1=external, 2=base, 3=terminator, 4=interior.
static int run(uint32_t cap,uint32_t len,unsigned kind,uint32_t pos,uint32_t n) {
    Guard a,b; uint16_t ha[40],hb[40]; uint16_t ext[8]={0,0xd800,0xffff,0x41,0,0xdc00,9,8};
    fill(&a,sizeof a,0xa5); fill(ha,sizeof ha,0x6d);
    a.s.capacity=cap; a.s.length=len;
    if(cap>=8)a.s.storage.heap=ha+2;
    uint16_t* da=cap<8?a.s.storage.local:ha+2;
    for(unsigned i=0;i<len;++i)da[i]=uint16_t(0x8100+i);
    da[len]=0; b=a;
    for(unsigned i=0;i<40;++i)hb[i]=ha[i];
    if(cap>=8)b.s.storage.heap=hb+2;
    uint16_t* db=cap<8?b.s.storage.local:hb+2;
    const uint16_t* sa=kind==0?0:kind==1?ext:kind==2?da:kind==3?da+len:da+pos;
    const uint16_t* sb=kind==0?0:kind==1?ext:kind==2?db:kind==3?db+len:db+pos;
    Guard expected=a; uint16_t he[40]; for(unsigned i=0;i<40;++i)he[i]=ha[i];
    uint32_t result=n;
    if(kind==2 && len)result=n<len?n:len;
    if(kind==4)result=0; // Only count zero exercised for nonzero positions.
    uint16_t* de=cap<8?expected.s.storage.local:he+2;
    // Self helper first truncates at position+result, leaving that NUL even
    // when the subsequent erase empties the string.
    if(kind==4)de[pos]=0;
    de[result]=0; expected.s.length=result;
    if(a.s.assign_range(sa,n)!=&a.s)return 1;
    if(original_wide_assign_range(&b.s,sb,n)!=&b.s)return 2;
    if(!same(&a,&expected,sizeof a)||!same(ha,he,sizeof ha))return 3;
    if(!same(ha,hb,sizeof ha))return 4;
    if(cap>=8)b.s.storage.heap=ha+2;
    if(!same(&a,&b,sizeof a))return 5;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"layout");
    static_assert(offsetof(WideString,length)==16,"length");
    static_assert(offsetof(WideString,capacity)==20,"capacity");
    const uint32_t caps[]={0,1,7,8,15,31};
    const uint32_t counts[]={0,1,2,7,8,31,0x7ffffffeu,0x7fffffffu,0xffffffffu};
    for(unsigned c=0;c<6;++c)for(unsigned len=0;len<=caps[c];++len) {
        for(unsigned kind=0;kind<4;++kind) {int e=run(caps[c],len,kind,0,0);if(e)return e;}
        if(len)for(unsigned k=0;k<9;++k) {int e=run(caps[c],len,2,0,counts[k]);if(e)return 10+e;}
        for(unsigned pos=1;pos<len;++pos) {int e=run(caps[c],len,4,pos,0);if(e)return 20+e;}
    }
    // Nonempty external copy: C++ expected-value check only. The original
    // requires an unavailable memcpy import on this path.
    WideString s; fill(&s,sizeof s,0x55); s.capacity=7;s.length=6;
    uint16_t input[4]={0xd800,0,0xffff,0xdc00};
    if(s.assign_range(input,4)!=&s||s.length!=4||s.capacity!=7)return 31;
    for(unsigned i=0;i<4;++i)if(s.storage.local[i]!=input[i])return 32;
    if(s.storage.local[4]!=0||s.storage.local[5]!=0x5555)return 33;
    if(unexpected)return 34;
    test_write("wide-assign-range checks passed\n",32);
    return 0;
}
