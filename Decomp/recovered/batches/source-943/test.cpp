#include "impl.hpp"
extern "C" uint32_t __attribute__((cdecl)) original_audio_stream_query_position(AudioStream*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);

struct GuardedStream {
    uint32_t before[4];
    AudioStream stream;
    uint32_t after[4];
};
static GuardedStream recovered, original, expected;
static uint32_t fsBacking[16];
static void copyBytes(void* dst, const void* src, unsigned count) {
    uint8_t* d = static_cast<uint8_t*>(dst);
    const uint8_t* s = static_cast<const uint8_t*>(src);
    for (unsigned i=0; i<count; ++i) d[i]=s[i];
}
static bool equalBytes(const void* a, const void* b, unsigned count) {
    const uint8_t* x=static_cast<const uint8_t*>(a);
    const uint8_t* y=static_cast<const uint8_t*>(b);
    for (unsigned i=0; i<count; ++i) if (x[i]!=y[i]) return false;
    return true;
}
static int compareCall() {
    const uint32_t result = (expected.stream.flags & 8)
        ? expected.stream.bufferBasePosition + expected.stream.bufferOffset
        : expected.stream.cachedPosition;
    expected.stream.cachedPosition=result;
    uint32_t a=audio_stream_query_position(&recovered.stream);
    uint32_t b=original_audio_stream_query_position(&original.stream);
    if (test_get_fs_head()!=fsBacking[0]) return 1;
    if (a!=b || a!=result) return 2;
    // Includes all unknown bytes and both surrounding guards, not just outputs.
    if (!equalBytes(&recovered, &expected, sizeof(expected))) return 3;
    if (!equalBytes(&original, &expected, sizeof(expected))) return 4;
    return 0;
}
extern "C" int test_main() {
    fsBacking[0]=0x13579bdfu;
    if (test_install_fs(fsBacking)!=0) return 10;
    const uint32_t pairs[][2] = {
        {0,0}, {1,2}, {0xffffffffu,0}, {0,0xffffffffu},
        {0xffffffffu,1}, {1,0xffffffffu}, {0xffffffffu,0xffffffffu},
        {0x7fffffffu,1}, {0x80000000u,0x80000000u},
        {0x12345678u,0x87654321u}, {0xffff0000u,0x10001u}
    };
    for (unsigned flags=0; flags<256; ++flags) {
        for (unsigned p=0; p<sizeof(pairs)/sizeof(pairs[0]); ++p) {
            uint8_t* bytes=reinterpret_cast<uint8_t*>(&expected);
            for (unsigned i=0; i<sizeof(expected); ++i)
                bytes[i]=static_cast<uint8_t>(i*37u+flags*13u+p);
            expected.stream.flags=static_cast<uint8_t>(flags);
            expected.stream.cachedPosition=0xdeadbeefu ^ (p*0x1234567u);
            expected.stream.bufferBasePosition=pairs[p][0];
            expected.stream.bufferOffset=pairs[p][1];
            copyBytes(&recovered,&expected,sizeof(expected));
            copyBytes(&original,&expected,sizeof(expected));
            int rc=compareCall(); if (rc) return 20+rc;
            rc=compareCall(); if (rc) return 30+rc; // repeated query
            // Change inputs and toggle refresh: exposes stale-cache semantics.
            expected.stream.flags^=8;
            expected.stream.bufferOffset^=0x87654321u;
            recovered.stream.flags=original.stream.flags=expected.stream.flags;
            recovered.stream.bufferOffset=original.stream.bufferOffset=expected.stream.bufferOffset;
            rc=compareCall(); if (rc) return 40+rc;
        }
    }
    test_write("audio-stream-query-position: passed\n",36);
    return 0;
}
