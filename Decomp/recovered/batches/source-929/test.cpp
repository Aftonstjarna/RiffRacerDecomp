#include "impl.hpp"
extern "C" int32_t __attribute__((cdecl)) original_audio_buffer_adjust_position(AudioBufferPosition*, int32_t);
extern "C" void test_write(const char*, unsigned);
static AudioBufferPosition recovered, oracle, before;
static uint32_t rng = 0x12345678u;
static uint32_t nextBits() { rng ^= rng << 13; rng ^= rng >> 17; rng ^= rng << 5; return rng; }
static int32_t signedBits(uint32_t v) { return v < 0x80000000u ? static_cast<int32_t>(v) : -1-static_cast<int32_t>(~v); }
static int run(uint32_t end, uint32_t pos, uint32_t saved, uint32_t base, int32_t amount,
               bool explicitExpected = false, int32_t expectedResult = 0, uint32_t expectedPosition = 0) {
    recovered.bufferedEnd=end; recovered.position=pos;
    recovered.checkpoint=saved; recovered.basePosition=base;
    oracle = recovered; before = recovered;
    int32_t a=audio_buffer_adjust_position(&recovered,amount);
    int32_t b=original_audio_buffer_adjust_position(&oracle,amount);
    if(a!=b) return 1;
    if(explicitExpected && (a!=expectedResult || recovered.position!=expectedPosition)) return 2;
    const uint8_t* x=reinterpret_cast<const uint8_t*>(&recovered);
    const uint8_t* y=reinterpret_cast<const uint8_t*>(&oracle);
    const uint8_t* z=reinterpret_cast<const uint8_t*>(&before);
    for(unsigned i=0;i<sizeof(recovered);++i) {
        if(x[i]!=y[i]) return 3;
        if((i<0x6d88 || i>=0x6d8c) && x[i]!=z[i]) return 4;
    }
    return 0;
}
extern "C" int test_main() {
    for(unsigned i=0;i<sizeof(recovered.unknown);++i) recovered.unknown[i]=static_cast<uint8_t>(i*37u+11u);
    if(run(100,20,7,0,5,true,0,15)) return 10;
    if(run(100,20,7,0,21,true,-1,20)) return 11;
    if(run(100,20,7,0,20,true,0,0)) return 12;
    if(run(100,20,7,0,-80,true,0,100)) return 13;
    if(run(100,20,7,0,-81,true,-1,7)) return 14;
    if(run(100,20,7,0,(-2147483647-1),true,-1,20)) return 15;
    if(run(100,20,7,0x7fffffffu,-1,true,-1,21)) return 16;
    if(run(0x80000000u,0x7fffffffu,7,0,-1,true,-1,0x80000000u)) return 17;
    if(run(0,0xffffffffu,7,0,-1,true,0,0)) return 18;
    if(run(100,0xffffffffu,7,0,0,true,-1,0xffffffffu)) return 19;
    const uint32_t edge[]={0,1,2,20,100,0x7ffffffeu,0x7fffffffu,0x80000000u,0x80000001u,0xfffffffeu,0xffffffffu};
    for(unsigned e=0;e<11;++e) for(unsigned p=0;p<11;++p) for(unsigned a=0;a<11;++a)
        if(run(edge[e],edge[p],edge[(e+p)%11],edge[(p+a)%11],signedBits(edge[a]))) return 20;
    for(unsigned n=0;n<2000;++n) {
        uint32_t e=nextBits(),p=nextBits(),c=nextBits(),b=nextBits(),a=nextBits();
        if(run(e,p,c,b,signedBits(a))) return 21;
    }
    test_write("audio-buffer-adjust-position: passed\n",37);
    return 0;
}
extern "C" void* memcpy(void* dst, const void* src, unsigned size) {
    uint8_t* d=static_cast<uint8_t*>(dst);
    const uint8_t* s=static_cast<const uint8_t*>(src);
    for(unsigned i=0;i<size;++i) d[i]=s[i];
    return dst;
}
