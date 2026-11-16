#include "impl.hpp"
extern "C" int32_t __attribute__((cdecl)) original_audio_stream_shift_byte(riff::AudioStream*, uint32_t*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
extern "C" void test_write(const char*, unsigned);
using namespace riff;
static AudioStream stream;
static AudioBackend table;
static unsigned char before[sizeof(AudioStream)];
static int32_t result;
static unsigned char input;
static bool write_byte, mutate;
static uint32_t* active;
static uint32_t replacement;
static unsigned calls, bad;
static int32_t RIFF_CDECL read_callback(AudioStream* s, unsigned char* dst, int32_t count) {
    ++calls;
    if (s != &stream || count != 1 || !dst) ++bad;
    if (write_byte) *dst = input;
    if (mutate) {
        *active = replacement;
        s->unknown[27] ^= 0x5a;
    }
    return result;
}
static void prepare(uint32_t seed, uint32_t* value) {
    for (unsigned i=0; i<sizeof(stream.unknown); ++i)
        stream.unknown[i] = static_cast<unsigned char>(i*37+11);
    stream.backend = &table;
    *value=seed;
    calls=bad=0;
    active=value;
}
static bool run_case(uint32_t seed, bool alias) {
    uint32_t guarded[3] = {0x13579bdf,0,0x2468ace0};
    uint32_t* value = alias ? reinterpret_cast<uint32_t*>(stream.unknown+64) : &guarded[1];
    prepare(seed,value);
    int32_t a=original_audio_stream_shift_byte(&stream,value);
    if(calls!=1 || bad || test_get_fs_head()!=0xffffffffu) return false;
    uint32_t observed=*value;
    for(unsigned i=0;i<sizeof(stream);++i) before[i]=reinterpret_cast<unsigned char*>(&stream)[i];
    prepare(seed,value);
    int32_t b=audio_stream_shift_byte(&stream,value);
    const uint32_t base=mutate ? replacement : seed;
    const uint32_t expected=result==1 ? (base<<8)|input : base;
    if(a!=b || a!=(result==-10 ? -10 : result==1 ? 1 : 0) || observed!=expected || *value!=expected || calls!=1 || bad) return false;
    for(unsigned i=0;i<sizeof(stream);++i) {
        if(before[i]!=reinterpret_cast<unsigned char*>(&stream)[i]) return false;
        unsigned char expected_byte=static_cast<unsigned char>(i*37+11);
        if(i>=sizeof(stream.unknown)) continue; // backend pointer compared above
        if(alias && i>=64 && i<68) expected_byte=static_cast<unsigned char>(expected>>((i-64)*8));
        if(mutate && i==27) expected_byte^=0x5a;
        if(reinterpret_cast<unsigned char*>(&stream)[i]!=expected_byte) return false;
    }
    return stream.backend==&table && guarded[0]==0x13579bdf && guarded[2]==0x2468ace0;
}
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0) return 4;
    table.read=read_callback;
    const int32_t statuses[]={-10,-2147483647-1,-11,-1,0,1,2,255,2147483647};
    const uint32_t seeds[]={0,1,0xffffffffu,0x80000000u,0x12345678u,0xff000001u};
    replacement=0x89abcdefu;
    for(unsigned s=0;s<sizeof(statuses)/sizeof(statuses[0]);++s)
    for(unsigned byte=0;byte<256;++byte)
    for(unsigned n=0;n<sizeof(seeds)/sizeof(seeds[0]);++n)
    for(unsigned m=0;m<2;++m)
    for(unsigned alias=0;alias<2;++alias) {
        result=statuses[s]; input=static_cast<unsigned char>(byte); mutate=m!=0; write_byte=true;
        if(!run_case(seeds[n],alias!=0)) return 1;
    }
    // Failed reads need not initialize destination; accumulator is untouched.
    write_byte=false; mutate=false; result=-10;
    if(!run_case(0x12345678,false)) return 2;
    result=0;
    if(!run_case(0xffffffffu,false)) return 3;
    test_write("audio-stream-shift-byte: passed\n",32);
    return 0;
}
