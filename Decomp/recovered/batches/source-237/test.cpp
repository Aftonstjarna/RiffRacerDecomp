#include "impl.hpp"
extern "C" uint32_t __attribute__((stdcall)) original_worker_dispatch(void*);
extern "C" void test_write(const char*, unsigned);
static riff::Worker* observed;
static unsigned calls;
static unsigned wrong_slot;
class Probe : public riff::Worker {
public:
    uint32_t words[12];
    virtual Probe* RIFF_THISCALL deleting_wrapper(uint32_t) { ++wrong_slot; return this; }
    virtual bool RIFF_THISCALL start(bool) { ++wrong_slot; return false; }
    virtual uint32_t RIFF_THISCALL run() {
        observed = this;
        ++calls;
        ++words[3];
        words[6] ^= words[1];
        return words[0];
    }
};
class OtherProbe : public Probe {
public:
    virtual uint32_t RIFF_THISCALL run() {
        observed = this;
        ++calls;
        words[8] = words[2];
        return ~words[0];
    }
};
static bool equal_bytes(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0; i<n; ++i) if (x[i]!=y[i]) return false;
    return true;
}
template<class T> static bool check(uint32_t value, uint32_t counter) {
    T original, recovered;
    for (unsigned i=0; i<12; ++i) {
        original.words[i]=recovered.words[i]=0xa5010203u+i*0x1020304u;
    }
    original.words[0]=recovered.words[0]=value;
    original.words[3]=recovered.words[3]=counter;
    calls=wrong_slot=0;
    uint32_t a=original_worker_dispatch(&original);
    if (observed!=&original || calls!=1 || wrong_slot) return false;
    uint32_t b=riff::worker_dispatch(&recovered);
    if (observed!=&recovered || calls!=2 || wrong_slot || a!=b) return false;
    if (!equal_bytes(&original,&recovered,sizeof(T))) return false;
    // Repeat to check cumulative mutations and balanced stdcall stack cleanup.
    for (unsigned i=0; i<64; ++i) {
        a=original_worker_dispatch(&original);
        b=riff::worker_dispatch(&recovered);
        if (a!=b || observed!=&recovered || calls!=4+2*i || wrong_slot) return false;
        if (!equal_bytes(&original,&recovered,sizeof(T))) return false;
    }
    return true;
}
extern "C" int test_main() {
    const uint32_t values[]={0,1,0x7fffffffu,0x80000000u,0xffffffffu,0x13579bdfu};
    for (unsigned i=0; i<sizeof(values)/sizeof(values[0]); ++i) {
        if (!check<Probe>(values[i],0xffffffffu)) return 1;
        if (!check<OtherProbe>(values[i],0)) return 2;
    }
    test_write("worker-dispatch: passed\n",24);
    return 0;
}
