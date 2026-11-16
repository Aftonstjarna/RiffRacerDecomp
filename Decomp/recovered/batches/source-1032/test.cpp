#include "impl.hpp"
extern "C" uint32_t __attribute__((cdecl)) original_audio_stereo_callback_bridge(
    uint32_t, uint32_t, riff::Decoder*);
extern "C" void test_write(const char*, unsigned);
struct Fixture { uint32_t before; riff::Decoder decoder; unsigned char tail[64]; };
static Fixture fixture;
static uint32_t inputs[2], results[2], calls, failures, replace_callback;
static uint32_t buffer[2];
static uint32_t RIFF_CDECL alternate(uint32_t, uint32_t, riff::Decoder*, uint32_t);
static uint32_t invoke(uint32_t input, uint32_t channel, riff::Decoder* decoder,
                       uint32_t lane, bool alternate_used) {
    uint32_t index = calls++;
    if (index > 1) { ++failures; return 0; }
    if (decoder != &fixture.decoder || input != inputs[index] ||
        channel != index || lane != index ||
        alternate_used != (replace_callback != 0 && index == 1)) ++failures;
    // Observable writes belong to the callback, not to the bridge.
    decoder->unknown[17 + index] = static_cast<unsigned char>(0xd0 + index);
    buffer[index] = input ^ (0xa5a50000u + index);
    if (index == 0 && replace_callback) decoder->selected_callback = alternate;
    return results[index];
}
static uint32_t RIFF_CDECL primary(uint32_t a, uint32_t b, riff::Decoder* c, uint32_t d) {
    return invoke(a,b,c,d,false);
}
static uint32_t RIFF_CDECL alternate(uint32_t a, uint32_t b, riff::Decoder* c, uint32_t d) {
    return invoke(a,b,c,d,true);
}
static void run(bool original) {
    fixture.before = 0x1234abcd;
    for (unsigned i=0;i<sizeof(fixture.decoder.unknown);++i)
        fixture.decoder.unknown[i] = static_cast<unsigned char>(i*37u+11u);
    for (unsigned i=0;i<sizeof(fixture.tail);++i) fixture.tail[i]=0x79;
    fixture.decoder.selected_callback=primary;
    calls=0; buffer[0]=buffer[1]=0;
    uint32_t value = original
        ? original_audio_stereo_callback_bridge(inputs[0],inputs[1],&fixture.decoder)
        : riff::audio_stereo_callback_bridge(inputs[0],inputs[1],&fixture.decoder);
    if (value != results[0]+results[1] || calls != 2 || fixture.before != 0x1234abcd)
        ++failures;
    if (fixture.decoder.selected_callback != (replace_callback ? alternate : primary)) ++failures;
    for (unsigned i=0;i<sizeof(fixture.decoder.unknown);++i) {
        unsigned char expected = i==17 ? 0xd0 : i==18 ? 0xd1 : static_cast<unsigned char>(i*37u+11u);
        if (fixture.decoder.unknown[i]!=expected) ++failures;
    }
    for (unsigned i=0;i<sizeof(fixture.tail);++i) if(fixture.tail[i]!=0x79) ++failures;
    for (unsigned i=0;i<2;++i) if(buffer[i]!=(inputs[i]^(0xa5a50000u+i))) ++failures;
}
extern "C" int test_main() {
    static const uint32_t values[] = {0,1,2,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu,0x13579bdfu};
    for (unsigned mode=0;mode<2;++mode) {
        replace_callback=mode;
        for(unsigned a=0;a<8;++a) for(unsigned b=0;b<8;++b) {
            results[0]=values[a]; results[1]=values[b];
            inputs[0]=values[b]; inputs[1]=values[a];
            run(true); run(false);
        }
    }
    if(failures) { test_write("FAIL\n",5); return 1; }
    test_write("PASS: 256 bridge calls\n",23); return 0;
}
