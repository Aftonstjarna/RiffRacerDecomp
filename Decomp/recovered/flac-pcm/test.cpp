#include "impl.hpp"
extern "C" unsigned original_flac_channel_zero(const short*,unsigned,float*);
extern "C" void test_write(const char*,unsigned);
static short input[2048], saved[2048];
static float expected[1026], actual[1026];
static bool equal_bytes(const void* a,const void* b,unsigned n) {
    auto x=static_cast<const unsigned char*>(a),y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
static bool check(unsigned bytes) {
    for(unsigned i=0;i<2048;++i)saved[i]=input[i];
    for(unsigned i=0;i<1026;++i)expected[i]=actual[i]=123.25f;
    const unsigned a=original_flac_channel_zero(input,bytes,expected+1);
    const unsigned b=riff::recovered::flac_channel_zero(input,bytes,actual+1);
    return a==b && equal_bytes(actual,expected,sizeof actual) && equal_bytes(input,saved,sizeof input);
}
extern "C" int test_main() {
    if(original_flac_channel_zero(nullptr,0,nullptr)!=0 ||
       riff::recovered::flac_channel_zero(nullptr,0,nullptr)!=0)return 1;
    // Exercise every signed-16-bit channel-zero value. The other channel is
    // deliberately different, detecting accidental averaging/channel swaps.
    for(unsigned block=0;block<64;++block) {
        for(unsigned i=0;i<1024;++i) {
            input[2*i]=static_cast<short>(int(block*1024+i)-32768);
            input[2*i+1]=static_cast<short>(32767-int((i*97+block)%65536));
        }
        if(!check(4096))return 2;
    }
    // Every possible short block length, including odd bytes/word counts.
    for(unsigned i=0;i<2048;++i)input[i]=static_cast<short>(int((i*37)%65536)-32768);
    for(unsigned bytes=0;bytes<=4096;++bytes)if(!check(bytes))return 3;
    static const char message[]="PASS: 65536 channel values and 4097 byte lengths; oracle outputs, counts, input and guards agree\n";
    test_write(message,sizeof(message)-1);return 0;
}
