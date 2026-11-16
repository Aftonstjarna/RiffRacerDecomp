#include "impl.hpp"
extern "C" int32_t __attribute__((fastcall)) original_audio_resample_phase_at_count(const AudioResampleState*, int32_t);
extern "C" void test_write(const char*, unsigned);
static AudioResampleState state;
static unsigned char saved[sizeof(state)];
static uint32_t rng = 0x9e3779b9u;
static uint32_t next() { rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng; }
static int check(uint32_t a, uint32_t b, int32_t count) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&state);
    for (unsigned i=0; i<sizeof(state); ++i) bytes[i] = static_cast<unsigned char>(i*37u+11u);
    state.phaseFactor=a; state.phaseScale=b;
    for (unsigned i=0; i<sizeof(state); ++i) saved[i]=bytes[i];
    const int32_t want=original_audio_resample_phase_at_count(&state,count);
    for (unsigned i=0; i<sizeof(state); ++i) if (saved[i]!=bytes[i]) return 1;
    const int32_t got=state.phaseAtCount(count);
    if (got!=want || got < -32767 || got > 32767) return 2;
    for (unsigned i=0; i<sizeof(state); ++i) if (saved[i]!=bytes[i]) return 3;
    if (count<=0 && got!=16384) return 4;
    return 0;
}
extern "C" int test_main() {
    const uint32_t values[]={0,1,2,0x3fff,0x4000,0x7fff,0x8000,0x8001,
        0x7fffbfff,0x7fffc000,0x7fffffff,0x80000000u,0x80000001u,0xffff8000u,0xffffffffu};
    const int32_t counts[]={(-2147483647-1),-65536,-1,0,1,2,3,7,32,257,4096};
    for (unsigned a=0;a<sizeof(values)/sizeof(values[0]);++a)
        for(unsigned b=0;b<sizeof(values)/sizeof(values[0]);++b)
            for(unsigned c=0;c<sizeof(counts)/sizeof(counts[0]);++c)
                if(check(values[a],values[b],counts[c])) return 1;
    for(unsigned i=0;i<2000;++i) {
        const uint32_t a=next(), b=next();
        if(check(a,b,static_cast<int32_t>(next()%1024))) return 2;
    }
    test_write("phase comparisons passed\n",25);
    return 0;
}
