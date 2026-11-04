#include "impl.hpp"
using namespace riff;
extern "C" void original_message_pump();
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" { uint32_t oracle_import[384] __attribute__((section(".oracle_import"),used,aligned(4))) = {}; }
static unsigned failures, count, polls, handled, phase, mutation;
static Message* active;
static uint32_t logdata[1024];
static unsigned logsize;
static void check(bool ok) { if (!ok) ++failures; }
static void record(uint32_t value) { if(logsize < 1024) logdata[logsize++] = value; else ++failures; }
static void setslots(Peek p, Dispatch d, Translate t) {
    imports.peek=p; imports.dispatch=d; imports.translate=t;
    oracle_import[0x55c/4]=reinterpret_cast<uintptr_t>(p);
    oracle_import[0x57c/4]=reinterpret_cast<uintptr_t>(d);
    oracle_import[0x59c/4]=reinterpret_cast<uintptr_t>(t);
}
static int32_t RIFF_STDCALL badpeek(Message*,uint32_t,uint32_t,uint32_t,uint32_t) { ++failures; return 0; }
static int32_t RIFF_STDCALL baddispatch(const Message*) { ++failures; return 0; }
static int32_t RIFF_STDCALL badtranslate(const Message*) { ++failures; return 0; }
static int32_t RIFF_STDCALL dispatch2(const Message*);
static int32_t RIFF_STDCALL translate2(const Message*);
static int32_t RIFF_STDCALL peek(Message* m,uint32_t window,uint32_t low,uint32_t high,uint32_t flags) {
    check(window==0 && low==0 && high==0 && flags==1);
    check(phase==0); record(1); ++polls;
    if (!active) active=m;
    check(active==m);
    if (polls==1 && mutation) setslots(badpeek,dispatch2,translate2);
    if (handled==count) return 0;
    uint32_t* words=reinterpret_cast<uint32_t*>(m);
    for(unsigned i=0;i<7;++i) words[i]=0x81234567u + handled*31u+i;
    m->message=handled==0 ? 0x12u : (handled==1 ? 0u : 0x400u+handled);
    phase=1;
    return handled%2 ? -1 : 2; // BOOL means nonzero, not exactly one.
}
static int32_t translate_common(const Message* m,unsigned v) {
    check(phase==1 && m==active); phase=2;
    record(2+v); const uint32_t* words=reinterpret_cast<const uint32_t*>(m);
    for(unsigned i=0;i<7;++i) record(words[i]);
    // Deliberate callback mutation verifies use of the same live MSG buffer.
    const_cast<Message*>(m)->wparam ^= 0xffffffffu;
    if(mutation) setslots(badpeek,baddispatch,badtranslate);
    return handled%2 ? -7 : 0;
}
static int32_t dispatch_common(const Message* m,unsigned v) {
    check(phase==2 && m==active); phase=0; record(4+v);
    const uint32_t* words=reinterpret_cast<const uint32_t*>(m);
    for(unsigned i=0;i<7;++i) record(words[i]);
    ++handled; return -123;
}
static int32_t RIFF_STDCALL translate1(const Message* m) {return translate_common(m,0);}
static int32_t RIFF_STDCALL dispatch1(const Message* m) {return dispatch_common(m,0);}
static int32_t RIFF_STDCALL translate2(const Message* m) {return translate_common(m,1);}
static int32_t RIFF_STDCALL dispatch2(const Message* m) {return dispatch_common(m,1);}
static void run(bool original,unsigned n,unsigned mutate) {
    count=n; mutation=mutate; polls=handled=phase=logsize=0; active=0;
    for(unsigned i=0;i<384;++i) oracle_import[i]=0xa5000000u+i;
    setslots(peek,dispatch1,translate1);
    if(original) original_message_pump(); else message_pump();
    check(polls==n+1 && handled==n && phase==0);
    for(unsigned i=0;i<384;++i) {
        if(i!=0x55c/4 && i!=0x57c/4 && i!=0x59c/4) check(oracle_import[i]==0xa5000000u+i);
    }
}
extern "C" int test_main() {
    uint32_t fs_storage[8]={0x13579bdfu};
    if(test_install_fs(fs_storage)!=0) return 1;
    unsigned head=test_get_fs_head();
    check(head==fs_storage[0]); check(sizeof(Message)==28);
    const unsigned counts[]={0,1,2,17};
    for(unsigned c=0;c<4;++c) for(unsigned mutate=0;mutate<2;++mutate) {
        run(true,counts[c],mutate); check(test_get_fs_head()==head);
        uint32_t saved[1024]; unsigned size=logsize;
        for(unsigned i=0;i<size;++i) saved[i]=logdata[i];
        run(false,counts[c],mutate); check(test_get_fs_head()==head);
        check(size==logsize);
        for(unsigned i=0;i<size;++i) check(saved[i]==logdata[i]);
    }
    return failures ? 1 : 0;
}
extern "C" void* memcpy(void* dst,const void* src,unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i) { d[i]=s[i]; }
    return dst;
}
extern "C" void* memset(void* dst,int v,unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    for(unsigned i=0;i<n;++i) { d[i]=static_cast<unsigned char>(v); }
    return dst;
}
