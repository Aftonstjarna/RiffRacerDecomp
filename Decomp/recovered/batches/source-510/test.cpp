#include "impl.hpp"
// EAX is unused, EDX=begin, ECX=result; remaining args are caller-popped.
extern "C" uint8_t** __attribute__((regparm(3))) original_byte_range_transform_callback(
    unsigned unused, const uint8_t* begin, uint8_t** result,
    const uint8_t* end, uint8_t* destination, riff::ByteTransform callback);
extern "C" void test_write(const char*, unsigned);
static unsigned calls, mode;
static int arguments[512];
static uint8_t** watched;
static uint8_t* initial;
static unsigned premature;
static uint8_t* mutableBytes;
static int RIFF_CDECL callback(int x) {
    if (*watched != initial) ++premature;
    arguments[calls++] = x;
    if (mode == 2 && calls < 20) mutableBytes[calls] ^= 0x81;
    if (mode == 1) return x >= 'A' && x <= 'Z' ? x + 32 : x;
    return x * 1009 + static_cast<int>(calls) * 257 - 70000;
}
struct Result { unsigned before; uint8_t* value; unsigned after; };
static int run(unsigned length, unsigned start, unsigned end, unsigned dest,
               unsigned which, bool nullCallback) {
    uint8_t a[600], b[600];
    for (unsigned i=0;i<600;++i) a[i]=b[i]=static_cast<uint8_t>(i*73+128);
    // length selects the initialized input pattern, not the range bounds.
    if (length == 1) for(unsigned i=0;i<256;++i) a[i]=b[i]=static_cast<uint8_t>(i);
    Result ra={0x12345678, a+590, 0x98765432};
    Result rb={0x12345678, b+590, 0x98765432};
    int log[512]; unsigned n;
    calls=premature=0; mode=which; watched=&ra.value; initial=ra.value; mutableBytes=a+start;
    uint8_t** returned=original_byte_range_transform_callback(0,a+start,&ra.value,a+end,a+dest,nullCallback?0:callback);
    if(returned!=&ra.value || premature) return 1;
    n=calls; for(unsigned i=0;i<n;++i) log[i]=arguments[i];
    calls=premature=0; watched=&rb.value; initial=rb.value; mutableBytes=b+start;
    returned=riff::transformBytes(&rb.value,b+start,b+end,b+dest,nullCallback?0:callback);
    if(returned!=&rb.value || premature || calls!=n) return 2;
    if(ra.value-a!=rb.value-b || ra.value!=a+dest+(end>=start?end-start:0)) return 3;
    if(ra.before!=rb.before || ra.after!=rb.after || ra.before!=0x12345678 || ra.after!=0x98765432) return 4;
    for(unsigned i=0;i<600;++i) if(a[i]!=b[i]) return 5;
    for(unsigned i=0;i<n;++i) if(log[i]!=arguments[i]) return 6;
    if(n!=(end>=start?end-start:0)) return 7;
    if(length==1) for(unsigned i=0;i<n;++i) if(log[i]!=(i<128?static_cast<int>(i):static_cast<int>(i)-256)) return 8;
    return 0;
}
extern "C" int test_main() {
    if(run(1,0,256,300,0,false)) return 10;
    for(unsigned m=0;m<3;++m) {
        if(run(0,30,30,90,m,true)) return 11;
        if(run(0,90,30,50,m,true)) return 12;
        if(run(0,30,31,90,m,false)) return 13;
        if(run(0,30,130,30,m,false)) return 14;
        if(run(0,30,130,31,m,false)) return 15;
        if(run(0,31,131,30,m,false)) return 16;
        if(run(0,0,256,300,m,false)) return 17;
    }
    uint8_t* out= reinterpret_cast<uint8_t*>(1);
    if(original_byte_range_transform_callback(0,0,&out,0,0,0)!=&out || out) return 18;
    out=reinterpret_cast<uint8_t*>(1);
    if(riff::transformBytes(&out,0,0,0,0)!=&out || out) return 19;
    test_write("byte transform tests passed\n",28);
    return 0;
}
