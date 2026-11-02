#include "impl.hpp"
extern "C" void test_write(const char*, unsigned);
static void copy(void* d, const void* s, unsigned n) {
    auto* a = static_cast<unsigned char*>(d);
    auto* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0; i<n; ++i) a[i]=b[i];
}
static bool equal(const void* x,const void* y,unsigned n) {
    auto* a=static_cast<const unsigned char*>(x);
    auto* b=static_cast<const unsigned char*>(y);
    for(unsigned i=0;i<n;++i) if(a[i]!=b[i]) return false;
    return true;
}
static void fill(void* p,unsigned n) {
    auto* a=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i) a[i]=static_cast<unsigned char>(0x81+i*13);
}
static void* jump_state[5];
static volatile unsigned errors;
static volatile unsigned oracle;
static volatile unsigned bad_message;
extern "C" [[noreturn]] void recovered_wide_out_of_range(const char* s) {
    const char expected[]="invalid string position";
    if(oracle) { if(reinterpret_cast<unsigned>(s)!=0x99995c) bad_message=1; }
    else if(!equal(s,expected,sizeof expected)) bad_message=1;
    ++errors;
    __builtin_longjmp(jump_state,1);
}
struct Fixture { unsigned before[4]; WideString s; unsigned after[4]; WideUnit heap[40]; };
static Fixture initial, actual, expected;
static int check(unsigned cap,unsigned len,unsigned n,bool reference) {
    fill(&initial,sizeof initial);
    initial.s.capacity=cap; initial.s.length=len;
    initial.s.storage.heap=actual.heap;
    copy(&actual,&initial,sizeof actual);
    copy(&expected,&initial,sizeof expected);
    const bool invalid=n>len;
    if(!invalid) {
        expected.s.length=n;
        if(cap<8) expected.s.storage.inline_data[n]=0;
        else expected.heap[n]=0;
    }
    // The submission harness does not supply the Windows CRT import slot.
    // Invalid original calls require that external dependency; test the
    // recovered rejection here, and compare original code on all valid calls.
    if(invalid && reference) return 0;
    unsigned old_errors=errors;
    oracle=reference;
    if(__builtin_setjmp(jump_state)==0) {
        WideString* result=reference ? original_wide_truncate(&actual.s,n)
                                    : recovered_wide_truncate(&actual.s,n);
        if(invalid || result!=&actual.s) return 1;
    } else if(!invalid) return 2;
    if(errors!=old_errors+unsigned(invalid) || bad_message) return 3;
    // Whole fixture comparison checks terminator-only writes, pointer, capacity,
    // trailing characters, unused union bytes, and both surrounding canaries.
    if(!equal(&actual,&expected,sizeof actual)) return 4;
    return 0;
}
extern "C" int test_main() {
    const unsigned caps[]={0,1,7,8,9,31,0xffffffffu};
    unsigned cases=0;
    for(unsigned cap:caps) {
        unsigned max=cap<8 ? cap : 31;
        for(unsigned len=0;len<=max;++len) {
            for(unsigned n=0;n<=len+1;++n) {
                for(unsigned ref=0;ref<2;++ref) {
                    int r=check(cap,len,n,ref); if(r) return r;
                    ++cases;
                }
            }
            for(unsigned ref=0;ref<2;++ref) {
                int r=check(cap,len,0xffffffffu,ref); if(r) return r;
            }
        }
    }
    if(!cases) return 5;
    test_write("wide-truncate checks passed\n",28);
    return 0;
}
