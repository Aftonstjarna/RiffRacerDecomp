#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((thiscall)) original_wide_append_char(
    WideString*, uint32_t, uint16_t);
extern "C" void test_write(const char*, unsigned);
// These are test-only sentinels, not implementations of the dependencies.
// All differential inputs have spare capacity and legal lengths.
static volatile unsigned unexpected_dependency;
void RIFF_THISCALL WideString::grow(uint32_t, uint32_t) {
    unexpected_dependency = 1;
    for (;;) {}
}
void wide_string_length_error(const char*) {
    unexpected_dependency = 2;
    for (;;) {}
}
static void fill(void* p, unsigned n, unsigned char value) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0;i<n;++i) b[i]=value;
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
struct Guarded { uint32_t before[2]; WideString s; uint32_t after[2]; };
static int one(uint32_t cap, uint32_t len, uint16_t ch, uint32_t unused) {
    Guarded a,b,expected;
    uint16_t ha[80],hb[80],he[80];
    fill(&a,sizeof a,0xa5);
    fill(ha,sizeof ha,0x6d); fill(hb,sizeof hb,0x6d); fill(he,sizeof he,0x6d);
    a.s.length=len; a.s.capacity=cap;
    if(cap>=8) a.s.storage.heap_text=ha+2;
    uint16_t* text=cap<8 ? a.s.storage.inline_text : ha+2;
    for(unsigned i=0;i<len;++i) text[i]=uint16_t(0x3400+i);
    text[len]=0;
    b=a; expected=a;
    if(cap>=8) {
        for(unsigned i=0;i<80;++i) hb[i]=he[i]=ha[i];
        b.s.storage.heap_text=hb+2;
        expected.s.storage.heap_text=ha+2;
        he[2+len]=ch; he[3+len]=0;
    } else {
        expected.s.storage.inline_text[len]=ch;
        expected.s.storage.inline_text[len+1]=0;
    }
    expected.s.length=len+1;
    if(a.s.append_char(unused,ch)!=&a.s) return 1;
    if(original_wide_append_char(&b.s,unused,ch)!=&b.s) return 2;
    if(!equal(&a,&expected,sizeof a)) return 3;
    if(cap>=8) {
        if(!equal(ha,he,sizeof ha)||!equal(hb,he,sizeof hb)) return 4;
        // Normalize only the independently allocated backing pointer.
        b.s.storage.heap_text=ha+2;
    }
    if(!equal(&a,&b,sizeof a)) return 5;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"x86 layout");
    static_assert(offsetof(WideString,length)==16,"length offset");
    static_assert(offsetof(WideString,capacity)==20,"capacity offset");
    const uint16_t chars[]={0,1,0x5c,0x7f,0xff,0x8000,0xd800,0xdfff,0xffff};
    const uint32_t caps[]={1,2,6,7,8,9,15,31,63};
    for(unsigned c=0;c<sizeof(caps)/sizeof(caps[0]);++c)
        for(unsigned len=0;len<caps[c];++len)
            for(unsigned v=0;v<sizeof(chars)/sizeof(chars[0]);++v) {
                int e=one(caps[c],len,chars[v],v&1 ? 0xffffffffu : 0x12345678u);
                if(e) return e;
            }
    if(unexpected_dependency) return 6;
    test_write("wide-append-char differential checks passed\n",43);
    return 0;
}
