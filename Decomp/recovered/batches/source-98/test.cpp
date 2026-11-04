// Local full-oracle link: oracle.o first in .text at 0x536250;
// ld -m elf_i386 -e _start -z noexecstack -Ttext=0x536250
// --section-start=.copy=0x44e120 --section-start=.move=0x44e140
// --section-start=.setlength=0x44fab0 --section-start=.reserve=0x44fc30
// --section-start=.erroriat=0x92d168 oracle.o runtime.o impl.o test.o
// oracle.o is assembled unchanged from accepted wide_prepend.S; runtime.o
// is the supplied test_runtime.S. All other files compile with fixed flags.
// Without these placements only empty-prefix oracle paths are runnable.
#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_prepend(WideString*,uint32_t,const WideString*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
static unsigned mode, reserves, moves, copies, sets, request;
static uint16_t relocated[256];
static void fill(void* p,unsigned n) { for(unsigned i=0;i<n;++i) ((unsigned char*)p)[i]=0xa5; }
static bool eq(const void* a,const void* b,unsigned n) { for(unsigned i=0;i<n;++i) if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i]) return false; return true; }
static void transfer(uint16_t* d,const uint16_t* s,unsigned n,bool move) {
    if(move) ++moves; else ++copies;
    if(move && (uintptr_t)d>(uintptr_t)s) { while(n) { --n; d[n]=s[n]; } }
    else for(unsigned i=0;i<n;++i) d[i]=s[i];
}
// Test doubles, not recovered dependency implementations. Fixed sections allow
// local linker placement at the original helper addresses. Never silently claim
// nonempty oracle coverage when the coordinator does not map these sections.
extern "C" bool __attribute__((thiscall,section(".reserve"))) reserve_double(WideString* s,unsigned n,bool trim) {
    ++reserves; request=n;
    if(trim || mode==1) return false;
    if(mode==2) {
        fill(relocated,sizeof relocated);
        for(unsigned i=0;i<=s->length;++i) relocated[i]=s->data()[i];
        s->storage.heap=relocated; s->capacity=255;
    }
    return true;
}
extern "C" void __attribute__((thiscall,section(".setlength"))) set_double(WideString* s,unsigned n) { ++sets; s->length=n; s->data()[n]=0; }
// Original traits ABI uses ECX, EDX, then caller-cleaned stack count. A two
// register fastcall entry has no callee stack pop. Read its extra stack slot
// through GCC's frame intrinsic; no generated instruction bytes or asm.
extern "C" void __attribute__((fastcall,section(".copy"),optimize("O2"),noinline)) copy_double(uint16_t* d,const uint16_t* s) {
    unsigned n=((const unsigned*)__builtin_frame_address(0))[2]; transfer(d,s,n,false);
}
extern "C" void __attribute__((fastcall,section(".move"),optimize("O2"),noinline)) move_double(uint16_t* d,const uint16_t* s) {
    unsigned n=((const unsigned*)__builtin_frame_address(0))[2]; transfer(d,s,n,true);
}
bool RIFF_THIS WideString::reserve(uint32_t n,bool t) { return reserve_double(this,n,t); }
void RIFF_THIS WideString::set_length(uint32_t n) { set_double(this,n); }
void wide_copy(uint16_t* d,const uint16_t* s,uint32_t n) { transfer(d,s,n,false); }
void wide_move(uint16_t* d,const uint16_t* s,uint32_t n) { transfer(d,s,n,true); }
static void* escape[5]; static unsigned errors;
extern "C" void error_double(const char*) { ++errors; __builtin_longjmp(escape,1); }
extern "C" { __attribute__((section(".erroriat"))) void (*error_import)(const char*)=error_double; }
void wide_length_error(const char* p) { error_double(p); }
struct Guard { unsigned before[2]; WideString s; unsigned after[2]; };
static bool mapped;
static int one(unsigned cap,unsigned len,unsigned pcap,unsigned count,bool self,unsigned m) {
    Guard runs[2], sources[2]; uint16_t heaps[2][256], ph[2][256], contents[2][256];
    unsigned traces[2][5];
    for(unsigned r=0;r<2;++r) {
        fill(&runs[r],sizeof(Guard)); fill(&sources[r],sizeof(Guard));
        fill(heaps[r],sizeof heaps[r]); fill(ph[r],sizeof ph[r]);
        WideString& s=runs[r].s; WideString& p=sources[r].s;
        s.length=len; s.capacity=cap; if(cap>=8) s.storage.heap=heaps[r];
        p.length=count; p.capacity=pcap; if(pcap>=8) p.storage.heap=ph[r];
        for(unsigned i=0;i<len;++i) s.data()[i]=i%3==0?0:uint16_t(0xd800+i);
        s.data()[len]=0;
        for(unsigned i=0;i<count;++i) p.data()[i]=i%3==1?0:uint16_t(0xfff0+i);
        p.data()[count]=0;
        Guard before=runs[r], sourceBefore=sources[r];
        uint16_t sourceHeapBefore[256], heapBefore[256];
        for(unsigned i=0;i<256;++i) { sourceHeapBefore[i]=ph[r][i]; heapBefore[i]=heaps[r][i]; }
        uint16_t old[128], pref[128];
        unsigned n=self?len:count;
        for(unsigned i=0;i<len;++i) old[i]=s.data()[i];
        for(unsigned i=0;i<n;++i) pref[i]=self?old[i]:p.data()[i];
        mode=m; reserves=moves=copies=sets=request=0;
        if(r && !mapped && n) break;
        WideString* ret=r?original_wide_prepend(&s,0xdeadbeef,self?&s:&p,0xffffffff,0x12345678):s.prepend(0xdeadbeef,self?&s:&p,0xffffffff,0x12345678);
        if(ret!=&s || !eq(&sources[r],&sourceBefore,sizeof(Guard)) || !eq(ph[r],sourceHeapBefore,sizeof sourceHeapBefore)) return 1;
        if(!eq(runs[r].before,before.before,8)||!eq(runs[r].after,before.after,8)) return 2;
        bool success=n && m!=1;
        if(s.length!=len+(success?n:0) || reserves!=(n!=0) || sets!=success || moves!=(success?(self?2u:1u):0u) || copies!=(success&&!self)) return 3;
        if(n && request!=len+n) return 4;
        if(success) {
            for(unsigned i=0;i<n;++i) if(s.data()[i]!=pref[i]) return 5;
            for(unsigned i=0;i<len;++i) if(s.data()[n+i]!=old[i]) return 6;
            if(s.data()[n+len]) return 7;
        } else if(!eq(&runs[r],&before,sizeof(Guard))) return 8;
        // Independently construct all expected object and buffer bytes, including
        // unused union bytes, spare capacity, and old heap after relocation.
        Guard expected=before;
        uint16_t expectedText[256];
        if(success && m==2) {
            fill(expectedText,sizeof expectedText);
            expected.s.capacity=255;
            expected.s.storage.heap=relocated;
        } else {
            for(unsigned i=0;i<256;++i) expectedText[i]=heapBefore[i];
        }
        uint16_t* expectedData=expected.s.capacity<8?expected.s.storage.text:expectedText;
        if(success) {
            for(unsigned i=0;i<n;++i) expectedData[i]=pref[i];
            for(unsigned i=0;i<len;++i) expectedData[n+i]=old[i];
            expectedData[n+len]=0;
            expected.s.length=len+n;
        }
        if(!eq(&runs[r],&expected,sizeof expected)) return 14;
        if(s.capacity>=8 && !eq(s.data(),expectedText,sizeof expectedText)) return 15;
        if(success && m==2 && !eq(heaps[r],heapBefore,sizeof heapBefore)) return 16;
        fill(contents[r],sizeof contents[r]);
        if(s.capacity>=8) {
            for(unsigned i=0;i<256;++i) contents[r][i]=s.data()[i];
            s.storage.heap=0;
        }
        // Original input heap stays untouched when the double relocates it.
        if(success && m==2 && cap>=8) {
            for(unsigned i=0;i<len;++i) if(heaps[r][i]!=old[i]) return 9;
            if(heaps[r][len]) return 10;
        }
        traces[r][0]=reserves; traces[r][1]=moves; traces[r][2]=copies; traces[r][3]=sets; traces[r][4]=request;
    }
    if(mapped || !(self?len:count)) {
        if(!eq(runs,runs+1,sizeof(Guard)) || !eq(contents,contents+1,sizeof contents[0]) || !eq(traces,traces+1,sizeof traces[0])) return 11;
    }
    return 0;
}
static int overflow(unsigned len,unsigned n) {
    for(unsigned r=0;r<(mapped?2u:1u);++r) {
        WideString s,p; fill(&s,sizeof s); fill(&p,sizeof p); s.length=len; p.length=n;
        WideString before=s; reserves=errors=0;
        if(!__builtin_setjmp(escape)) {
            if(r) original_wide_prepend(&s,0,&p,0,0); else s.prepend(0,&p,0,0);
            return 12;
        }
        if(errors!=1 || reserves || !eq(&s,&before,sizeof s)) return 13;
    }
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"x86 layout");
    static_assert(offsetof(WideString,length)==16,"length offset");
    static_assert(offsetof(WideString,capacity)==20,"capacity offset");
    mapped=(uintptr_t)&reserve_double==0x44fc30 && (uintptr_t)&set_double==0x44fab0 && (uintptr_t)&copy_double==0x44e120 && (uintptr_t)&move_double==0x44e140 && (uintptr_t)&error_import==0x92d168;
    const unsigned caps[]={7,8,31};
    for(unsigned c=0;c<3;++c) for(unsigned pc=0;pc<3;++pc)
    for(unsigned l=0;l<=caps[c];++l) for(unsigned n=0;n<=caps[pc];++n)
    for(unsigned m=0;m<3;++m) {
        if(m==0 && l+n>caps[c]) continue;
        int e=one(caps[c],l,caps[pc],n,false,m); if(e) return e;
    }
    for(unsigned c=0;c<3;++c) for(unsigned l=0;l<=caps[c];++l) for(unsigned m=0;m<3;++m) {
        if(m==0 && 2*l>caps[c]) continue;
        int e=one(caps[c],l,7,0,true,m); if(e) return e;
    }
    const unsigned limits[][2]={{0xffffffffu,0},{0xfffffffeu,1},{0,0xffffffffu},{0x80000000u,0x7fffffffu},{1,0xffffffffu}};
    for(unsigned i=0;i<5;++i) { int e=overflow(limits[i][0],limits[i][1]); if(e) return e; }
    if(mapped) test_write("wide-prepend full differential checks passed\n",sizeof("wide-prepend full differential checks passed\n")-1);
    else test_write("LIMIT: fixed helper slots absent; oracle checks empty prefixes only; other checks C++ with doubles\n",sizeof("LIMIT: fixed helper slots absent; oracle checks empty prefixes only; other checks C++ with doubles\n")-1);
    return 0;
}
