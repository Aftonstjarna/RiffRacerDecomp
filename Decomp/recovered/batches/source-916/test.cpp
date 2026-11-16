#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_buffer_pack_high_three_bytes(riff::ByteBuffer*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static_assert(sizeof(riff::ByteBuffer) == 12, "i386 object size");
static_assert(offsetof(riff::ByteBuffer, size) == 8, "size offset");
static unsigned fsStorage[8];
static unsigned char recovered[8256], oracle[8256], expected[8256];
static unsigned char initial(unsigned i, unsigned seed) {
    return static_cast<unsigned char>((i * 73u + (i >> 2) * 19u + seed * 131u) ^ (i >> 5));
}
static int check(unsigned length, unsigned offset, unsigned seed, bool twice) {
    for (unsigned i = 0; i < sizeof(oracle); ++i)
        recovered[i] = oracle[i] = expected[i] = initial(i, seed);
    riff::ByteBuffer a = {recovered + offset, 0xa5937c21u ^ seed, length};
    riff::ByteBuffer b = {oracle + offset, a.unknown04, length};
    for (unsigned pass = 0; pass < (twice ? 2u : 1u); ++pass) {
        const unsigned packed = (length / 4u) * 3u;
        for (unsigned group = 0; group < length / 4u; ++group)
            for (unsigned byte = 0; byte < 3; ++byte)
                expected[offset + group * 3u + byte] = expected[offset + group * 4u + byte + 1u];
        a.packHighThreeBytes();
        original_buffer_pack_high_three_bytes(&b);
        if (test_get_fs_head() != fsStorage[0]) return 1;
        if (a.size != packed || b.size != packed) return 2;
        if (a.data != recovered + offset || b.data != oracle + offset ||
            a.unknown04 != (0xa5937c21u ^ seed) || b.unknown04 != a.unknown04) return 3;
        for (unsigned i = 0; i < sizeof(oracle); ++i)
            if (oracle[i] != expected[i] || recovered[i] != oracle[i]) return 4;
        length = packed;
    }
    return 0;
}
extern "C" int test_main() {
    fsStorage[0] = 0x13579bdfu;
    if (test_install_fs(fsStorage) != 0) return 10;
    for (unsigned n = 0; n <= 1027; ++n) {
        int error = check(n, 16u + (n % 4u), n, true);
        if (error) return 20 + error;
    }
    for (unsigned n = 4093; n <= 4100; ++n) {
        int error = check(n, 19, n + 7, true);
        if (error) return 30 + error;
    }
    // No complete group: the original never dereferences data.
    for (unsigned n = 0; n < 4; ++n) {
        riff::ByteBuffer a = {0, 0xffffffffu, n}, b = a;
        a.packHighThreeBytes();
        original_buffer_pack_high_three_bytes(&b);
        if (test_get_fs_head() != fsStorage[0]) return 40;
        if (a.data || b.data || a.size || b.size ||
            a.unknown04 != 0xffffffffu || b.unknown04 != a.unknown04) return 41;
    }
    return 0;
}
