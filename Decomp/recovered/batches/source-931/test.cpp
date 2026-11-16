#include "impl.hpp"
extern "C" int32_t __attribute__((cdecl)) original_audio_input_read_dispatch(riff::AudioInput*, void*, int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
struct Context { uint32_t visits; uint32_t tag; };
static riff::AudioInput input;
static unsigned char before[sizeof(input)];
static unsigned char oracle_after[sizeof(input)];
static uint32_t fs_storage[16];
static Context primary, alternate;
static void* seen_context;
static void* seen_buffer;
static int32_t seen_count, result_value;
static unsigned calls, selected;
static bool mutate;
static int32_t callback(void* context, void* buffer, int32_t count, unsigned which) {
    ++calls; selected=which; seen_context=context; seen_buffer=buffer; seen_count=count;
    if (context) ++static_cast<Context*>(context)->visits;
    if (mutate) {
        input.flags ^= 0xffffffffu;
        input.unknown_0000[17] ^= 0x91;
        input.alternate_read=0;
        if (buffer) static_cast<unsigned char*>(buffer)[0] ^= 0x53;
    }
    return result_value;
}
static int32_t RIFF_CDECL default_callback(void* c, void* b, int32_t n) { return callback(c,b,n,1); }
static int32_t RIFF_CDECL alternate_callback(void* c, void* b, int32_t n) { return callback(c,b,n,2); }
static void copy(unsigned char* d, const unsigned char* s, unsigned n) { for(unsigned i=0;i<n;++i)d[i]=s[i]; }
static bool equal(const unsigned char* a,const unsigned char* b,unsigned n) { for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;return true; }
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0)return 1;
    const int32_t values[]={0,1,-1,17,(-2147483647-1),2147483647};
    unsigned cases=0;
    for(unsigned flags=0;flags<256;++flags)
    for(unsigned missing=0;missing<2;++missing)
    for(unsigned v=0;v<6;++v)
    for(unsigned mode=0;mode<4;++mode) {
        unsigned char* bytes=reinterpret_cast<unsigned char*>(&input);
        for(unsigned i=0;i<sizeof(input);++i)bytes[i]=static_cast<unsigned char>(i*37+flags);
        input.flags=0xa5c39000u|flags;
        input.default_context=(mode==3)?0:&primary;
        input.alternate_context=(mode==3)?0:&alternate;
        input.default_read=default_callback;
        input.alternate_read=missing?0:alternate_callback;
        // With alternate selected, even a null default callback is irrelevant.
        if(flags&0x40)input.default_read=0;
        copy(before,bytes,sizeof(input));
        unsigned char buffer[4]={0x12,0x34,0x56,0x78};
        void* argument=(mode==0)?0:buffer;
        mutate=(mode==2);
        result_value=values[(v+mode)%6];
        calls=0; selected=0; seen_context=0; seen_buffer=0; seen_count=0;
        primary.visits=7; alternate.visits=19;
        int32_t original=original_audio_input_read_dispatch(&input,argument,values[v]);
        if(test_get_fs_head()!=fs_storage[0])return 2;
        bool absent=(flags&0x40)&&missing;
        if(original!=(absent?-1:result_value))return 3;
        if(calls!=(absent?0u:1u))return 4;
        if(!absent && (selected!=((flags&0x40)?2u:1u) || seen_context!=((flags&0x40)?input.alternate_context:input.default_context) || seen_buffer!=argument || seen_count!=values[v]))return 5;
        copy(oracle_after,bytes,sizeof(input));
        unsigned char oracle_buffer[4];copy(oracle_buffer,buffer,4);
        unsigned p=primary.visits,a=alternate.visits;
        copy(bytes,before,sizeof(input));
        buffer[0]=0x12;buffer[1]=0x34;buffer[2]=0x56;buffer[3]=0x78;
        calls=0;selected=0;seen_context=0;seen_buffer=0;seen_count=0;
        primary.visits=7;alternate.visits=19;
        int32_t recovered=riff::audio_input_read_dispatch(&input,argument,values[v]);
        if(recovered!=original || calls!=(absent?0u:1u))return 6;
        if(!absent && (selected!=((flags&0x40)?2u:1u) || seen_context!=((flags&0x40)?input.alternate_context:input.default_context) || seen_buffer!=argument || seen_count!=values[v]))return 7;
        if(!equal(bytes,oracle_after,sizeof(input)) || !equal(buffer,oracle_buffer,4) || primary.visits!=p || alternate.visits!=a)return 8;
        if(!mutate || absent)if(!equal(bytes,before,sizeof(input)))return 9;
        ++cases;
    }
    if(cases!=12288)return 10;
    test_write("12288 dispatch comparisons passed\n",34);
    return 0;
}
