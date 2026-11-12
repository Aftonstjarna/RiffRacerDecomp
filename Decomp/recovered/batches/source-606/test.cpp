#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((stdcall)) original_narrow_path_slashes_normalize(riff::NarrowString*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(riff::NarrowString)==24, "i386 string size");
static_assert(offsetof(riff::NarrowString,length)==16, "length offset");
static_assert(offsetof(riff::NarrowString,capacity)==20, "capacity offset");
struct Fixture { unsigned char prefix[16]; riff::NarrowString string; unsigned char suffix[16]; };
static Fixture fixture;
static unsigned char heap[128], before_heap[128], original_heap[128];
static unsigned char before_object[sizeof(Fixture)], original_object[sizeof(Fixture)];
static void copy(unsigned char* d, const unsigned char* s, unsigned n) {
    for(unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool equal(const unsigned char* a,const unsigned char* b,unsigned n) {
    for(unsigned i=0;i<n;++i) if(a[i]!=b[i]) return false;
    return true;
}
static bool run(unsigned length, unsigned capacity, unsigned seed) {
    unsigned char* object=reinterpret_cast<unsigned char*>(&fixture);
    for(unsigned i=0;i<sizeof(Fixture);++i) object[i]=static_cast<unsigned char>(0xa5+i);
    for(unsigned i=0;i<128;++i) heap[i]=static_cast<unsigned char>(0x80+i);
    fixture.string.length=length;
    fixture.string.capacity=capacity;
    if(capacity>=16) fixture.string.storage.heap_data=reinterpret_cast<char*>(heap+16);
    unsigned char* data=reinterpret_cast<unsigned char*>(fixture.string.data());
    for(unsigned i=0;i<length;++i) {
        // All byte values, embedded NULs, repeated slashes, and mixed paths.
        data[i]=seed<256 ? static_cast<unsigned char>(seed) :
            static_cast<unsigned char>(i%5==0 ? 0 : i%3==0 ? '\\' : i%3==1 ? '/' : 'x');
    }
    // A backslash immediately outside the logical range must remain intact.
    data[length]='\\';
    copy(before_object,object,sizeof(Fixture)); copy(before_heap,heap,128);
    original_narrow_path_slashes_normalize(&fixture.string);
    copy(original_object,object,sizeof(Fixture)); copy(original_heap,heap,128);
    // Verify oracle side effects against the instruction-derived specification.
    const unsigned offset=16; // inline storage begins after the object guard
    for(unsigned i=0;i<sizeof(Fixture);++i) {
        unsigned char expected=before_object[i];
        if(capacity<16 && i>=offset && i<offset+length && expected=='\\') expected='/';
        if(object[i]!=expected) return false;
    }
    for(unsigned i=0;i<128;++i) {
        unsigned char expected=before_heap[i];
        if(capacity>=16 && i>=16 && i<16+length && expected=='\\') expected='/';
        if(heap[i]!=expected) return false;
    }
    copy(object,before_object,sizeof(Fixture)); copy(heap,before_heap,128);
    riff::normalize_path_slashes(&fixture.string);
    if(!equal(object,original_object,sizeof(Fixture)) || !equal(heap,original_heap,128)) return false;
    riff::normalize_path_slashes(&fixture.string); // Idempotence, including guards.
    return equal(object,original_object,sizeof(Fixture)) && equal(heap,original_heap,128);
}
extern "C" int test_main() {
    const unsigned caps[]={0,15,16,31,64,0x80000000u,0xffffffffu};
    for(unsigned c=0;c<sizeof(caps)/sizeof(caps[0]);++c) {
        unsigned max_length=caps[c]<16 ? caps[c] : (caps[c]<64 ? caps[c] : 64);
        for(unsigned n=0;n<=max_length;++n)
            for(unsigned seed=0;seed<=256;++seed)
                if(!run(n,caps[c],seed)) { test_write("FAIL\n",5); return 1; }
    }
    test_write("PASS\n",5); return 0;
}
