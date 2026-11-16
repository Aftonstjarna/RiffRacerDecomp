#include "impl.hpp"
extern "C" int32_t __attribute__((cdecl)) original_audio_stream_read_exact(AudioStream*, void*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Guarded { uint32_t before[4]; AudioStream stream; uint32_t after[8]; };
static Guarded a,b,expected;
static uint8_t da[32],db[32],de[32];
static uint32_t fs[16];
static AudioBackend table, replacement;
static AudioStream* wantedStream;
static void* wantedDestination;
static uint32_t wantedCount, returnBits, calls, failures;
static bool mutate;
static void fill(void* p,unsigned n) { uint8_t* d=(uint8_t*)p; for(unsigned i=0;i<n;++i)d[i]=(uint8_t)(i*37+19); }
static void copy(void* p,const void* q,unsigned n) { uint8_t* d=(uint8_t*)p; const uint8_t* s=(const uint8_t*)q; for(unsigned i=0;i<n;++i)d[i]=s[i]; }
static bool equal(const void* p,const void* q,unsigned n) { const uint8_t* a=(const uint8_t*)p; const uint8_t* b=(const uint8_t*)q; for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false; return true; }
static int32_t RIFF_CDECL callback(AudioStream* s,void* d,uint32_t n) {
    ++calls;
    if(s!=wantedStream || d!=wantedDestination || n!=wantedCount)++failures;
    if(mutate) {
        s->unknown0[17]^=0x5a;
        s->unknown0[0x6d3b]=0xe7;
        s->backend=&replacement;
        if(d) { ((uint8_t*)d)[0]=0xa9; ((uint8_t*)d)[7]^=0xc3; }
    }
    return (int32_t)returnBits;
}
extern "C" int test_main() {
    fs[0]=0x13579bdf;
    if(test_install_fs(fs)!=0)return 1;
    table.unknown0[0]=0x12345678; table.unknown0[1]=0xabcdef01; table.read=callback;
    replacement=table;
    const uint32_t counts[]={0,1,7,31,0x7fffffff,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<7;++i)for(unsigned j=0;j<7;++j)for(unsigned mode=0;mode<4;++mode) {
        wantedCount=counts[i];
        const uint32_t results[]={wantedCount,wantedCount-1,wantedCount+1,0,0xfffffff6u,0xffffffffu,0x80000000u};
        returnBits=results[j]; mutate=(mode&1)!=0;
        fill(&expected,sizeof(expected)); expected.stream.backend=&table;
        copy(&a,&expected,sizeof(a)); copy(&b,&expected,sizeof(b));
        fill(de,sizeof(de)); copy(da,de,sizeof(da)); copy(db,de,sizeof(db));
        if(mutate) { expected.stream.unknown0[17]^=0x5a; expected.stream.unknown0[0x6d3b]=0xe7; expected.stream.backend=&replacement; if(!(mode&2)){de[0]=0xa9;de[7]^=0xc3;} }
        calls=failures=0; wantedStream=&a.stream; wantedDestination=(mode&2)?0:da;
        int32_t ra=audio_stream_read_exact(wantedStream,wantedDestination,wantedCount);
        if(calls!=1||failures)return 2;
        calls=failures=0; wantedStream=&b.stream; wantedDestination=(mode&2)?0:db;
        int32_t rb=original_audio_stream_read_exact(wantedStream,wantedDestination,wantedCount);
        if(test_get_fs_head()!=fs[0])return 3;
        if(calls!=1||failures)return 4;
        uint32_t answer=returnBits==wantedCount?returnBits:0xfffffff6u;
        if((uint32_t)ra!=answer || ra!=rb)return 5;
        if(!equal(&a,&expected,sizeof(a))||!equal(&b,&expected,sizeof(b)))return 6;
        if(!equal(da,de,sizeof(da))||!equal(db,de,sizeof(db)))return 7;
        if(table.read!=callback || table.unknown0[0]!=0x12345678 || table.unknown0[1]!=0xabcdef01)return 8;
    }
    return 0;
}
