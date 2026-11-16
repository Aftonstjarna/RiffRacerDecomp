#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_audio_metadata_state_initialize(AudioMetadataState*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
struct GuardedState {
    unsigned char before[16];
    AudioMetadataState state;
    unsigned char after[16];
};
static int run_case(unsigned seed, unsigned mode) {
    GuardedState actual, oracle;
    unsigned char expected[sizeof(GuardedState)];
    unsigned char* a = reinterpret_cast<unsigned char*>(&actual);
    unsigned char* o = reinterpret_cast<unsigned char*>(&oracle);
    for (unsigned i = 0; i < sizeof(actual); ++i) {
        seed = seed * 1664525u + 1013904223u;
        unsigned char v = mode == 0 ? static_cast<unsigned char>(seed >> 24)
                                   : static_cast<unsigned char>(mode - 1);
        a[i] = o[i] = expected[i] = v;
    }
    for (unsigned i = 0; i < 32; ++i)
        if (i != 7) expected[16 + i] = 0;
    original_audio_metadata_state_initialize(&oracle.state);
    if (test_get_fs_head() != 0x13579bdfu) return 1;
    actual.state.initialize();
    for (unsigned i = 0; i < sizeof(actual); ++i)
        if (a[i] != o[i] || a[i] != expected[i]) return 2;
    // Reinitialization must preserve the same byte and surrounding canaries.
    original_audio_metadata_state_initialize(&oracle.state);
    if (test_get_fs_head() != 0x13579bdfu) return 3;
    actual.state.initialize();
    for (unsigned i = 0; i < sizeof(actual); ++i)
        if (a[i] != o[i] || a[i] != expected[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    unsigned fs_storage[8] = {0x13579bdfu, 0, 0, 0, 0, 0, 0, 0};
    if (test_install_fs(fs_storage) != 0) return 10;
    if (test_get_fs_head() != fs_storage[0]) return 11;
    for (unsigned mode = 1; mode <= 256; ++mode)
        if (run_case(0, mode)) return 12;
    for (unsigned seed = 0; seed < 1024; ++seed)
        if (run_case(seed, 0)) return 13;
    static const char message[] = "audio metadata initialization: passed\n";
    test_write(message, sizeof(message) - 1);
    return 0;
}
