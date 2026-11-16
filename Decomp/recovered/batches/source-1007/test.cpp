#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_audio_decoder_metadata_clear(riff::AudioDecoder*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Guarded { unsigned char before[16]; riff::AudioDecoder object; unsigned char after[16]; };
static Guarded recovered, reference;
static unsigned fs_storage[8];
static unsigned char pattern(unsigned i, unsigned mode) {
    if (mode == 0) return 0;
    if (mode == 1) return 255;
    if (mode == 2) return 0x55;
    if (mode == 3) return 0xaa;
    return static_cast<unsigned char>((i * 73u + (i >> 8) * 19u + mode * 37u) ^ (mode + (i >> 3)));
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 1;
    for (unsigned mode = 0; mode != 260; ++mode) {
        unsigned char* a = reinterpret_cast<unsigned char*>(&recovered);
        unsigned char* b = reinterpret_cast<unsigned char*>(&reference);
        for (unsigned i = 0; i != sizeof(Guarded); ++i) a[i] = b[i] = pattern(i, mode);
        // Also supplies arbitrary non-null pointer-like words: no dereference is allowed.
        recovered.object.clear_metadata();
        original_audio_decoder_metadata_clear(&reference.object);
        if (test_get_fs_head() != fs_storage[0]) return 2;
        for (unsigned i = 0; i != sizeof(Guarded); ++i) {
            const unsigned object_offset = offsetof(Guarded, object);
            const bool cleared = i == object_offset + 0x6f70 ||
                (i >= object_offset + 0x6f74 && i < object_offset + 0x6fac);
            const unsigned char expected = cleared ? 0 : pattern(i, mode);
            if (a[i] != b[i]) return 3;
            if (a[i] != expected) return 4;
        }
        recovered.object.clear_metadata();
        original_audio_decoder_metadata_clear(&reference.object);
        if (test_get_fs_head() != fs_storage[0]) return 5;
        for (unsigned i = 0; i != sizeof(Guarded); ++i) if (a[i] != b[i]) return 6;
    }
    return 0;
}
