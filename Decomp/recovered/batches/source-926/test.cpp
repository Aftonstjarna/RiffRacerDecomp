#include "impl.hpp"
// Only ECX carries an argument. GCC's i386 thiscall attribute supplies that
// register convention without fabricating or dereferencing an object.
extern "C" int __attribute__((thiscall)) original_audio_frame_header_plausible(uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static uint32_t fs_storage[8];
static volatile uint32_t sentinels[4] = {0x12345678u, 0xdeadbeefu, 0, 0xffffffffu};
static int compare(uint32_t header, int expected)
{
    volatile uint32_t local[3] = {0x76543210u, header, 0xabcdef01u};
    int actual = original_audio_frame_header_plausible(header);
    if (test_get_fs_head() != 0x13579bdfu) return 1;
    int recovered = riff::audio_frame_header_plausible(header);
    if (actual != expected || recovered != actual) return 2;
    if (local[0] != 0x76543210u || local[1] != header || local[2] != 0xabcdef01u) return 3;
    if (sentinels[0] != 0x12345678u || sentinels[1] != 0xdeadbeefu ||
        sentinels[2] != 0 || sentinels[3] != 0xffffffffu) return 4;
    for (unsigned i = 1; i != 8; ++i)
        if (fs_storage[i] != 0xa5a50000u + i) return 5;
    return 0;
}
extern "C" int test_main()
{
    fs_storage[0] = 0x13579bdfu;
    for (unsigned i = 1; i != 8; ++i) fs_storage[i] = 0xa5a50000u + i;
    if (test_install_fs(fs_storage) != 0) return 10;
    // Exhaust every combination of the 19 inspected bits. Exercise ignored
    // bits both clear and all set for every combination, then mixed values.
    const uint32_t ignored = 0x001903ffu; // version, protection and low ten bits
    uint32_t random = 0x837219abu;
    for (uint32_t sync = 0; sync != 2048; ++sync)
        for (uint32_t layer = 0; layer != 4; ++layer)
            for (uint32_t bitrate = 0; bitrate != 16; ++bitrate)
                for (uint32_t rate = 0; rate != 4; ++rate) {
                    uint32_t h = (sync << 21) | (layer << 17) | (bitrate << 12) | (rate << 10);
                    int expected = sync == 2047 && layer != 0 && bitrate != 15 && rate != 3;
                    random = random * 1664525u + 1013904223u;
                    if (compare(h, expected) || compare(h | ignored, expected) ||
                        compare(h | (random & ignored), expected)) return 20;
                }
    // Exhaust all 13 ignored bits on an accepted header and one rejection
    // for each of the four independent checks.
    const uint32_t bases[5] = {0xffe20000u, 0xffc20000u, 0xffe00000u, 0xffe2f000u, 0xffe20c00u};
    for (uint32_t bits = 0; bits != 8192; ++bits) {
        uint32_t extra = (bits & 1023u) | ((bits & 1024u) << 6) | ((bits & 6144u) << 8);
        for (unsigned b = 0; b != 5; ++b)
            if (compare(bases[b] | extra, b == 0)) return 21;
    }
    test_write("audio header checks passed\n", 27);
    return 0;
}
