#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_append_pointer(WideString*,const uint16_t*,uint32_t);
extern "C" WideString* __attribute__((thiscall)) original_wide_append_substring(WideString*,const WideString*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
// Controlled dependency doubles. They exercise the target's dispatch and
// post-reserve reloads; they do not claim recovery of allocation or the CRT.
static uint16_t relocated[128];
static unsigned calls,sets,copies,requested,mode;
static bool dependencies_mapped;
extern "C" bool __attribute__((thiscall,section(".reserve"))) reserve_double(WideString* s,uint32_t n,bool trim) {
    ++calls; requested=n;
    if(trim) return false;
    if(mode==1) return false;
    if(mode==2) {
        for(unsigned i=0;i<128;++i) relocated[i]=0xcccc;
        for(unsigned i=0;i<=s->length;++i) relocated[i]=s->data()[i];
        s->storage.heap=relocated; s->capacity=127;
    }
    return true;
}
extern "C" void __attribute__((thiscall,section(".setlength"))) set_double(WideString* s,uint32_t n) {
    ++sets; s->length=n; s->data()[n]=0;
}
extern "C" void* __attribute__((section(".copy"))) copy_double(void* d,const void* s,uint32_t n) {
    ++copies;
    unsigned char* dst=(unsigned char*)d; const unsigned char* src=(const unsigned char*)s;
    for(unsigned i=0;i<n;++i) dst[i]=src[i];
    return d;
}
bool RIFF_THIS WideString::reserve(uint32_t n,bool t) { return reserve_double(this,n,t); }
void RIFF_THIS WideString::set_length(uint32_t n) { set_double(this,n); }
WideString* RIFF_THIS WideString::append_substring(const WideString* s,uint32_t p,uint32_t n) { if(dependencies_mapped) return original_wide_append_substring(this,s,p,n);
    // Test-only dependency model when fixed original helper slots are absent.
    if(n>s->length-p) n=s->length-p;
    unsigned old=length;
    if(n && reserve(old+n,false)) {
        copy_double(data()+length,(s->capacity<8?s->storage.text:s->storage.heap)+p,n*2);
        set_length(old+n);
    }
    return this; }
void* riff_copy(void* d,const void* s,uint32_t n) { return copy_double(d,s,n); }
static void* escape_state[5];
static unsigned error_seen;
extern "C" void error_double(const char*) { ++error_seen; __builtin_longjmp(escape_state,1); }
extern "C" {
__attribute__((section(".erroriat"))) void (*error_import)(const char*)=error_double;
}
void riff_length_error(const char* p) { error_double(p); }
static int overflow_case(unsigned len,unsigned count) {
    WideString s;
    // No dereference: null source, overflow rejected before reserve/copy.
    for(unsigned i=0;i<sizeof s;++i) ((unsigned char*)&s)[i]=0xa5;
    s.length=len; s.capacity=7;
    WideString before=s;
    for(unsigned run=0;run<(dependencies_mapped?2u:1u);++run) {
        error_seen=0;
        if(!__builtin_setjmp(escape_state)) {
            if(run) original_wide_append_pointer(&s,0,count);
            else s.append_pointer(0,count);
            return 7;
        }
        if(error_seen!=1) return 8;
        for(unsigned i=0;i<sizeof s;++i)
            if(((unsigned char*)&s)[i]!=((unsigned char*)&before)[i]) return 9;
    }
    return 0;
}
struct Guard { uint32_t pre[2]; WideString s; uint32_t post[2]; };
static void fill(void* p,unsigned n) { for(unsigned i=0;i<n;++i) ((unsigned char*)p)[i]=0xa5; }
static bool equal(const void* a,const void* b,unsigned n) { for(unsigned i=0;i<n;++i) if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i]) return false; return true; }
static int one(unsigned cap,unsigned len,unsigned count,int offset,unsigned m) {
    Guard g[2]; uint16_t heap[2][128], external[128], result[2][128];
    unsigned trace[2][4];
    for(unsigned i=0;i<128;++i) external[i]=uint16_t(i*91); // includes embedded NUL
    for(unsigned run=0;run<2;++run) {
        fill(&g[run],sizeof(Guard)); fill(heap[run],sizeof(heap[run]));
        WideString& s=g[run].s; s.length=len; s.capacity=cap;
        if(cap>=8) s.storage.heap=heap[run];
        for(unsigned i=0;i<len;++i) s.data()[i]=uint16_t(0xd800+i);
        s.data()[len]=0;
        const uint16_t* p=offset==-2 ? 0 : offset==-1 ? external : (const uint16_t*)((const unsigned char*)s.data()+offset);
        calls=sets=copies=requested=0; mode=m;
        if(run && !dependencies_mapped && count) return 0;
        if(!run && !dependencies_mapped) {
            WideString* ret=s.append_pointer(p,count);
            unsigned n=count;
            if(offset>=0 && unsigned(offset)<len*2 && n>len-unsigned(offset)/2) n=len-unsigned(offset)/2;
            if(ret!=&s || s.length!=len+(m==1?0:n) || calls!=(n!=0) || sets!=((n!=0)&&(m!=1))) return 6;
            if(g[run].pre[0]!=0xa5a5a5a5 || g[run].post[1]!=0xa5a5a5a5) return 5;
            if(count) return 0;
        }
        WideString* ret=run ? original_wide_append_pointer(&s,p,count) : (dependencies_mapped ? s.append_pointer(p,count) : &s);
        if(ret!=&s) return 1;
        trace[run][0]=calls; trace[run][1]=sets; trace[run][2]=copies; trace[run][3]=requested;
        for(unsigned i=0;i<128;++i) result[run][i]=(m==2 && calls) ? relocated[i] : heap[run][i];
        if(s.capacity>=8) s.storage.heap=0; // normalize backing addresses only
    }
    if(!equal(g,g+1,sizeof(Guard))) return 2;
    if(!equal(result[0],result[1],sizeof(result[0]))) return 3;
    if(!equal(trace[0],trace[1],sizeof(trace[0]))) return 4;
    // Independently check guards and observable length/helper activity.
    if(g[0].pre[0]!=0xa5a5a5a5 || g[0].post[1]!=0xa5a5a5a5) return 5;
    unsigned n=count;
    if(offset>=0 && unsigned(offset)<len*2 && n>len-unsigned(offset)/2) n=len-unsigned(offset)/2;
    unsigned expected=len+((m==1)?0:n);
    if(g[0].s.length!=expected || calls!=(n!=0) || sets!=((n!=0)&&(m!=1))) return 6;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"layout");
    static_assert(offsetof(WideString,length)==16,"length");
    dependencies_mapped = reinterpret_cast<uintptr_t>(&reserve_double)==0x44fc30u &&
        reinterpret_cast<uintptr_t>(&set_double)==0x44fab0u &&
        reinterpret_cast<uintptr_t>(&copy_double)==0x8f8d66u &&
        reinterpret_cast<uintptr_t>(&error_import)==0x92d168u;
    if(!dependencies_mapped) test_write("LIMIT: dependency slots unmapped; nonzero cases check C++ only\n",sizeof("LIMIT: dependency slots unmapped; nonzero cases check C++ only\n")-1);
    const unsigned caps[]={7,8,31};
    for(unsigned c=0;c<3;++c) for(unsigned len=0;len<=6;++len)
    for(unsigned m=0;m<3;++m) for(unsigned n=0;n<5;++n) {
        if(m==0 && len+n>caps[c]) continue;
        int e=one(caps[c],len,n,-1,m); if(e) return e;
        if(!n) { e=one(caps[c],len,0,-2,m); if(e) return e; }
        for(unsigned byte=0;byte<=2*len;++byte) {
            // Terminator pointer with nonzero count is legal here: backed by
            // initialized spare storage; no reallocation of that external path.
            if(byte==2*len && m==2 && n) continue;
            e=one(caps[c],len,n,int(byte),m); if(e) return e;
        }
    }
    const unsigned lengths[]={0u,1u,0x7ffffffeu,0xfffffffeu,0xffffffffu};
    for(unsigned i=0;i<5;++i) {
        int e=overflow_case(lengths[i],0xffffffffu-lengths[i]); if(e) return e;
        e=overflow_case(lengths[i],0xffffffffu); if(e) return e;
    }
    test_write("wide-append-pointer checks passed\n",34);
    return 0;
}
