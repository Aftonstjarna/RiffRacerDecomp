#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_substring(WideString*,const WideString*,uint32_t,uint32_t);
extern "C" WideString* __attribute__((thiscall)) original_wide_truncate(WideString*,uint32_t);
extern "C" WideString* __attribute__((thiscall)) original_wide_erase(WideString*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
WideString* RIFF_THISCALL WideString::truncate(uint32_t n) { return original_wide_truncate(this,n); }
WideString* RIFF_THISCALL WideString::erase(uint32_t p,uint32_t n) { return original_wide_erase(this,p,n); }
// Unsupported dependencies are never silently simulated in oracle runs.
void RIFF_THISCALL WideString::grow(uint32_t,uint32_t) { __builtin_trap(); }
void wide_out_of_range(const char*) { __builtin_trap(); }
void wide_length_error(const char*) { __builtin_trap(); }
void* wide_copy(void* d,const void* s,uint32_t n) {
    unsigned char* x=static_cast<unsigned char*>(d);
    const unsigned char* y=static_cast<const unsigned char*>(s);
    for(uint32_t i=0;i<n;++i)x[i]=y[i];
    return d;
}
extern "C" void* memcpy(void* d,const void* s,size_t n) { return wide_copy(d,s,n); }
extern "C" void* memset(void* d,int v,size_t n) {
    unsigned char* p=static_cast<unsigned char*>(d);
    for(size_t i=0;i<n;++i)p[i]=static_cast<unsigned char>(v);
    return d;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
struct Fixture { uint32_t before[2]; WideString s; uint32_t after[2]; uint16_t heap[40]; };
static uint16_t* data(Fixture& f) { return f.s.capacity<8?f.s.storage.local:f.s.storage.heap; }
static void init(Fixture& f,uint32_t cap,uint32_t len) {
    memset(&f,0xa5,sizeof f);f.s.capacity=cap;f.s.length=len;
    if(cap>=8)f.s.storage.heap=f.heap+2;
    uint16_t* p=data(f);
    for(uint32_t i=0;i<len;++i)p[i]=i%4==0?0:i%4==1?0xd800:i%4==2?0xffff:uint16_t(0x41+i);
    p[len]=0;
}
static void clone(Fixture& d,const Fixture& s) {
    memcpy(&d,&s,sizeof d);if(d.s.capacity>=8)d.s.storage.heap=d.heap+2;
}
static bool equivalent(Fixture& a,Fixture& b) {
    uint16_t* saved=b.s.storage.heap;
    if(b.s.capacity>=8)b.s.storage.heap=a.s.storage.heap;
    bool result=equal(&a,&b,sizeof a);
    if(b.s.capacity>=8)b.s.storage.heap=saved;
    return result;
}
static int oracle_case(uint32_t cap,uint32_t len,uint32_t pos,uint32_t n,bool self,uint32_t sourcecap) {
    Fixture a,b,e,source,snapshot;
    init(a,cap,len);clone(b,a);clone(e,a);
    init(source,sourcecap,sourcecap);clone(snapshot,source);
    const uint32_t source_length=self?len:sourcecap;
    uint32_t selected=source_length-pos;if(n<selected)selected=n;
    // Oracle matrix only uses no-shift self ranges or empty distinct ranges.
    if(self)data(e)[pos+selected]=0;
    e.s.length=selected;data(e)[selected]=0;
    if(a.s.assign_substring(self?&a.s:&source.s,pos,n)!=&a.s)return 1;
    if(original_wide_assign_substring(&b.s,self?&b.s:&source.s,pos,n)!=&b.s)return 2;
    if(!equivalent(a,b)||!equivalent(a,e))return 3;
    if(!equivalent(source,snapshot))return 4;
    return 0;
}
// Additional expected-value checks for the recovered distinct-source copy.
// These do not claim execution of the unavailable original memcpy import.
static int copy_case(uint32_t dstcap,uint32_t srccap,uint32_t len,uint32_t pos,uint32_t n) {
    Fixture d,e,s,saved;init(d,dstcap,dstcap);clone(e,d);init(s,srccap,len);clone(saved,s);
    uint32_t selected=len-pos;if(n<selected)selected=n;
    if(selected>dstcap)return 0;
    for(uint32_t i=0;i<selected;++i)data(e)[i]=data(s)[pos+i];
    data(e)[selected]=0;e.s.length=selected;
    if(d.s.assign_substring(&s.s,pos,n)!=&d.s)return 5;
    if(!equivalent(d,e)||!equivalent(s,saved))return 6;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"x86 layout");
    static_assert(offsetof(WideString,length)==16,"length offset");
    static_assert(offsetof(WideString,capacity)==20,"capacity offset");
    const uint32_t caps[]={0,1,7,8,15,31};
    const uint32_t counts[]={0,1,2,7,8,31,0x7ffffffeu,0x7fffffffu,0xffffffffu};
    for(unsigned c=0;c<6;++c)for(uint32_t len=0;len<=caps[c];++len) {
        for(unsigned k=0;k<9;++k) {
            int r=oracle_case(caps[c],len,0,counts[k],true,0);if(r)return r;
            r=oracle_case(caps[c],len,len,counts[k],true,0);if(r)return 10+r;
        }
        for(uint32_t pos=0;pos<=len;++pos) {
            int r=oracle_case(caps[c],len,pos,0,true,0);if(r)return 20+r;
        }
        for(unsigned s=0;s<6;++s)for(uint32_t pos=0;pos<=caps[s];++pos) {
            int r=oracle_case(caps[c],len,pos,0,false,caps[s]);if(r)return 30+r;
        }
        for(unsigned s=0;s<6;++s)for(unsigned k=0;k<9;++k) {
            int r=oracle_case(caps[c],len,caps[s],counts[k],false,caps[s]);if(r)return 40+r;
        }
    }
    for(unsigned d=0;d<6;++d)for(unsigned s=0;s<6;++s)
        for(uint32_t len=0;len<=caps[s];++len)for(uint32_t pos=0;pos<=len;++pos)
            for(unsigned k=0;k<9;++k) {int r=copy_case(caps[d],caps[s],len,pos,counts[k]);if(r)return 50+r;}
    const char message[]="wide-assign-substring checks passed\n";
    test_write(message,sizeof(message)-1);return 0;
}
