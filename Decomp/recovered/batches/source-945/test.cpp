#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_audio_unity_arrays_initialize(AudioUnityArrays*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
struct Fixture {
    uint32_t before[4];
    AudioUnityArrays object;
    unsigned char following[0x6fb0 - sizeof(AudioUnityArrays)];
    uint32_t after[4];
};
static Fixture recovered, oracle;
static uint32_t fs_storage[16];
static unsigned char initial[sizeof(Fixture)];
static bool check(const Fixture& f) {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&f);
    const size_t begin = offsetof(Fixture, object) + 0x2448;
    const size_t end = offsetof(Fixture, object) + 0x254c;
    for (size_t i = 0; i != sizeof(Fixture); ++i) {
        unsigned char expected = initial[i];
        if (i >= begin && i < begin + 4) expected = 0;
        if (i >= begin + 4 && i < end) {
            const unsigned shift = static_cast<unsigned>((i - begin - 4) % 4) * 8;
            expected = static_cast<unsigned char>(0x3f800000u >> shift);
        }
        if (bytes[i] != expected) return false;
    }
    return true;
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned saved = test_get_mxcsr();
    // Byte patterns include zeros, all ones, varying words and arbitrary float
    // encodings (NaNs, infinities and subnormals), all overwritten without reads.
    for (unsigned mode = 0; mode != 4; ++mode) {
        unsigned char* a = reinterpret_cast<unsigned char*>(&recovered);
        unsigned char* b = reinterpret_cast<unsigned char*>(&oracle);
        for (size_t i = 0; i != sizeof(Fixture); ++i) {
            unsigned char v = mode == 0 ? 0 : mode == 1 ? 255 :
                static_cast<unsigned char>((i * (mode == 2 ? 37 : 131) + 19) ^ (i >> 3));
            a[i] = b[i] = initial[i] = v;
        }
        const unsigned csr = (saved & ~0x603fu) | ((mode & 3) << 13) | 0x1f80u | (mode == 3 ? 0x3fu : 0);
        test_set_mxcsr(csr);
        for (unsigned repeat = 0; repeat != 2; ++repeat) {
            original_audio_unity_arrays_initialize(&oracle.object);
            if (test_get_fs_head() != fs_storage[0]) return 2;
            if (test_get_mxcsr() != csr) return 3;
            recovered.object.initialize();
            if (test_get_fs_head() != fs_storage[0]) return 4;
            if (test_get_mxcsr() != csr) return 5;
            if (!check(oracle) || !check(recovered)) return 6;
            for (size_t i = 0; i != sizeof(Fixture); ++i)
                if (a[i] != b[i]) return 7;
        }
    }
    test_set_mxcsr(saved);
    test_write("audio unity arrays: passed\n", 27);
    return 0;
}
