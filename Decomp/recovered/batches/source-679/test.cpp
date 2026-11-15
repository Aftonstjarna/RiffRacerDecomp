#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_append_substring(NarrowString*,const NarrowString*,uint32_t,uint32_t);
extern "C" bool __attribute__((thiscall)) original_narrow_prepare_capacity(NarrowString*,uint32_t,bool);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,size_t n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    const unsigned char* b=static_cast<const unsigned char*>(s);
    for(size_t i=0;i<n;++i) { a[i]=b[i]; }
    return d;
}
extern "C" void* memset(void* d,int v,size_t n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    for(size_t i=0;i<n;++i) { a[i]=static_cast<unsigned char>(v); }
    return d;
}
static unsigned head, preparations, expected_size;
static bool bad;
typedef void* (*Copy)(void*,const void*,size_t);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy;
void* narrow_copy(void* d,const void* s,uint32_t n) { return memcpy(d,s,n); }
void narrow_length_error(const char*) { __builtin_trap(); }
void narrow_position_error(const char*) { __builtin_trap(); }
bool RIFF_THISCALL NarrowString::prepare_capacity(uint32_t n,bool trim) {
    ++preparations;
    if(n!=expected_size || trim || n>capacity) { __builtin_trap(); }
    bool result=original_narrow_prepare_capacity(this,n,trim);
    if(test_get_fs_head()!=head) { bad=true; }
    return result;
}
struct Fixture { uint32_t before[2]; NarrowString s; uint32_t after[2]; char heap[80]; uint32_t end[2]; };
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) { if(x[i]!=y[i]) { return false; } }
    return true;
}
static char* data(NarrowString& s) { return s.capacity<16?s.storage.local:s.storage.heap; }
static void init(Fixture& f,unsigned length,bool heap,unsigned seed) {
    memset(&f,0xa5,sizeof f);
    f.s.length=length; f.s.capacity=heap?63:15;
    if(heap) { f.s.storage.heap=f.heap; }
    char* p=data(f.s);
    for(unsigned i=0;i<length;++i) { p[i]=static_cast<char>(i*37+seed); }
    p[length]=0;
}
static void expected(Fixture& f,const NarrowString& source,unsigned pos,unsigned count) {
    unsigned n=source.length-pos;
    if(n>count) { n=count; }
    if(n) {
        const char* p=source.capacity<16?source.storage.local:source.storage.heap;
        memcpy(data(f.s)+f.s.length,p+pos,n);
        f.s.length+=n;data(f.s)[f.s.length]=0;
    }
}
static int one(unsigned len,unsigned slen,unsigned pos,unsigned count,bool dh,bool sh,bool self) {
    Fixture a,b,sa,sb,ea,eb,saved_sa,saved_sb;
    init(a,len,dh,0x83);init(b,len,dh,0x83);
    init(sa,self?0:slen,sh,0x12);init(sb,self?0:slen,sh,0x12);
    memcpy(&ea,&a,sizeof a);memcpy(&eb,&b,sizeof b);
    memcpy(&saved_sa,&sa,sizeof sa);memcpy(&saved_sb,&sb,sizeof sb);
    const NarrowString* pa=self?&a.s:&sa.s;
    const NarrowString* pb=self?&b.s:&sb.s;
    unsigned n=pa->length-pos;if(n>count) { n=count; }
    // Expected fixture pointers deliberately still designate the live backing.
    // Compute bytes in temporary backing, then restore expected pointer values.
    if(dh) { ea.s.storage.heap=ea.heap;eb.s.storage.heap=eb.heap; }
    expected(ea,self?ea.s:sa.s,pos,count);
    expected(eb,self?eb.s:sb.s,pos,count);
    if(dh) { ea.s.storage.heap=a.heap;eb.s.storage.heap=b.heap; }
    unsigned prior=preparations;expected_size=len+n;
    if(a.s.append_substring(pa,pos,count)!=&a.s) { return 1; }
    if(bad || preparations!=prior+(n!=0)) { return 2; }
    if(original_narrow_append_substring(&b.s,pb,pos,count)!=&b.s) { return 3; }
    if(test_get_fs_head()!=head) { return 4; }
    if(!equal(&a,&ea,sizeof a)||!equal(&b,&eb,sizeof b)) { return 5; }
    if(!equal(&sa,&saved_sa,sizeof sa)||!equal(&sb,&saved_sb,sizeof sb)) { return 6; }
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"layout");
    static_assert(offsetof(NarrowString,length)==16,"length");
    static_assert(offsetof(NarrowString,capacity)==20,"capacity");
    static unsigned tls[16];tls[0]=0x12345678;
    if(test_install_fs(tls)!=0) { return 20; }
    head=tls[0];if(test_get_fs_head()!=head) { return 21; }
    const unsigned counts[]={0,1,3,15,0xffffffffu};
    for(unsigned dh=0;dh<2;++dh) {
        for(unsigned sh=0;sh<2;++sh) {
            for(unsigned len=0;len<=(dh?30u:15u);len+=3) {
                for(unsigned slen=0;slen<=(sh?30u:15u);slen+=3) {
                    for(unsigned pos=0;pos<=slen;++pos) {
                        for(unsigned c=0;c<5;++c) {
                            unsigned n=slen-pos;if(n>counts[c]) { n=counts[c]; }
                            if(len+n>(dh?63u:15u)) { continue; }
                            int e=one(len,slen,pos,counts[c],dh!=0,sh!=0,false);
                            if(e) { return e; }
                        }
                    }
                }
                for(unsigned pos=0;pos<=len;++pos) {
                    for(unsigned c=0;c<5;++c) {
                        unsigned n=len-pos;if(n>counts[c]) { n=counts[c]; }
                        if(len+n>(dh?63u:15u)) { continue; }
                        int e=one(len,len,pos,counts[c],dh!=0,sh!=0,true);
                        if(e) { return e; }
                    }
                }
            }
        }
    }
    int edge=one(60,3,0,0xffffffffu,true,false,false);
    if(edge) { return edge; }
    test_write("narrow append substring passed\n",sizeof("narrow append substring passed\n")-1);
    return 0;
}
