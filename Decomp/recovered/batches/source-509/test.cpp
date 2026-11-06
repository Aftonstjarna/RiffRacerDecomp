#include "impl.hpp"
extern "C" int __attribute__((thiscall)) original_narrow_compare_range(
    const riff::NarrowString*, uint32_t, uint32_t, const unsigned char*, uint32_t);
extern "C" void test_write(const char*, unsigned);
// Unreachable for these valid-position tests. Exception dispatch is unavailable
// in the freestanding harness; do not substitute a returning fake exception.
namespace riff { RIFF_NORETURN void narrow_out_of_range(const char*) { for (;;) {} } }
static unsigned char heap[96], right_data[96];
static unsigned char object_before[24], heap_before[96], right_before[96];
static int check(riff::NarrowString& s, uint32_t pos, uint32_t n,
                 const unsigned char* right, uint32_t rn) {
    const unsigned char* raw=reinterpret_cast<const unsigned char*>(&s);
    for(unsigned i=0;i<24;++i) object_before[i]=raw[i];
    for(unsigned i=0;i<96;++i) { heap_before[i]=heap[i]; right_before[i]=right_data[i]; }
    const unsigned char* left=s.capacity<16?s.storage.small:s.storage.heap;
    uint32_t selected=s.length-pos;
    if(n<selected) selected=n;
    uint32_t common=selected<rn?selected:rn;
    int expected=selected==rn?0:(selected<rn?-1:1);
    for(uint32_t i=0;i<common;++i) if(left[pos+i]!=right[i]) {
        expected=left[pos+i]<right[i]?-1:1; break;
    }
    int a=original_narrow_compare_range(&s,pos,n,right,rn);
    if(a!=expected) return 1;
    for(unsigned i=0;i<24;++i) if(raw[i]!=object_before[i]) return 2;
    for(unsigned i=0;i<96;++i)
        if(heap[i]!=heap_before[i] || right_data[i]!=right_before[i]) return 3;
    int b=s.compare(pos,n,right,rn);
    if(a!=b) return 4;
    for(unsigned i=0;i<24;++i) if(raw[i]!=object_before[i]) return 5;
    for(unsigned i=0;i<96;++i)
        if(heap[i]!=heap_before[i] || right_data[i]!=right_before[i]) return 6;
    return 0;
}
extern "C" int test_main() {
    riff::NarrowString s;
    const uint32_t caps[]={0,15,16,31,0xffffffffu};
    const uint32_t counts[]={0,1,3,4,7,15,16,31,64,0xffffffffu};
    for(unsigned mode=0;mode<5;++mode) {
        unsigned maxlen=caps[mode]<16?15:64;
        for(unsigned len=0;len<=maxlen;++len) {
            unsigned char* raw=reinterpret_cast<unsigned char*>(&s);
            for(unsigned i=0;i<24;++i) raw[i]=static_cast<unsigned char>(0xa0+i);
            s.capacity=caps[mode]; s.length=len;
            if(s.capacity>=16) s.storage.heap=heap+1;
            unsigned char* data=s.capacity<16?s.storage.small:heap+1;
            for(unsigned i=0;i<96;++i) { heap[i]=0x5a; right_data[i]=0xa5; }
            for(unsigned i=0;i<len;++i) data[i]=static_cast<unsigned char>(i*73);
            for(unsigned pos=0;pos<=len;++pos) {
                for(unsigned c=0;c<10;++c) for(unsigned rn=0;rn<=65;++rn) {
                    for(unsigned i=0;i<rn;++i)
                        right_data[i+1]=i<len-pos?data[pos+i]:static_cast<unsigned char>(i*31);
                    if(check(s,pos,counts[c],right_data+1,rn)) return 10;
                    if(rn && len>pos && counts[c]) {
                        unsigned at=(rn<len-pos?rn:len-pos)-1;
                        if(at>=counts[c]) at=counts[c]-1;
                        unsigned char old=right_data[at+1];
                        right_data[at+1]=static_cast<unsigned char>(old^0x80);
                        if(check(s,pos,counts[c],right_data+1,rn)) return 11;
                        right_data[at+1]=old;
                    }
                }
                if(check(s,pos,0xffffffffu,data+pos,len-pos)) return 12;
                if(check(s,pos,0,0,0)) return 13;
            }
        }
    }
    // Exhaust unsigned byte ordering (including NUL and bytes >= 128).
    s.capacity=15; s.length=1;
    for(unsigned a=0;a<256;++a) for(unsigned b=0;b<256;++b) {
        s.storage.small[0]=static_cast<unsigned char>(a);
        right_data[0]=static_cast<unsigned char>(b);
        if(check(s,0,1,right_data,1)) return 14;
    }
    test_write("narrow-compare-range: passed\n",29);
    return 0;
}
