#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_device_defaults(riff::DeviceState*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);

struct Guarded {
    uint32_t before[16];
    riff::DeviceState device;
    uint32_t after[32]; // includes caller-owned +0xa74, which reset must not clear
};
static Guarded candidate, oracle;
static unsigned char initial[sizeof(Guarded)];

// Independently audited write footprint, including the 16-element arrays.
static bool written(unsigned byteOffset) {
    const unsigned ranges[][2] = {
        {0x4f8,0x504}, {0x514,0x520}, {0x528,0x530},
        {0x534,0x554}, {0x564,0x578}, {0x59c,0x5a0},
        {0x5ac,0x5d0}, {0x6dc,0x704}, {0x708,0x71c},
        {0x720,0x730}, {0x738,0x76c}, {0x770,0x780},
        {0x784,0x7a0}, {0x7a4,0x7ec}, {0x7f4,0x9a4},
        {0x9ac,0xa2c}, {0xa64,0xa74}
    };
    for (unsigned i = 0; i < sizeof(ranges)/sizeof(ranges[0]); ++i)
        if (byteOffset >= ranges[i][0] && byteOffset < ranges[i][1]) return true;
    return false;
}
static int compare() {
    const unsigned char* a = reinterpret_cast<const unsigned char*>(&candidate);
    const unsigned char* b = reinterpret_cast<const unsigned char*>(&oracle);
    for (unsigned i = 0; i < sizeof(Guarded); ++i) {
        if (a[i] != b[i]) return 1;
        if ((i < 64 || i >= 64 + sizeof(riff::DeviceState) || !written(i - 64))
            && (a[i] != initial[i] || b[i] != initial[i])) return 2;
    }
    return 0;
}
extern "C" int test_main() {
    const unsigned saved = test_get_mxcsr();
    for (unsigned trial = 0; trial < 68; ++trial) {
        unsigned state = 0x91e10da5u ^ (trial * 0x9e3779b9u);
        unsigned char* a = reinterpret_cast<unsigned char*>(&candidate);
        unsigned char* b = reinterpret_cast<unsigned char*>(&oracle);
        for (unsigned i = 0; i < sizeof(Guarded); ++i) {
            state ^= state << 13; state ^= state >> 17; state ^= state << 5;
            const unsigned char value = trial == 0 ? 0 : trial == 1 ? 255 :
                trial == 2 ? 0x55 : trial == 3 ? 0xaa : static_cast<unsigned char>(state);
            a[i] = b[i] = initial[i] = value;
        }
        const unsigned mode = 0x1f80u | ((trial & 3u) << 13) |
            ((trial & 4u) ? 0x8040u : 0u);
        test_set_mxcsr(mode);
        candidate.device.resetDefaults();
        if (test_get_mxcsr() != mode) { test_set_mxcsr(saved); return 3; }
        original_device_defaults(&oracle.device);
        if (test_get_mxcsr() != mode) { test_set_mxcsr(saved); return 4; }
        int error = compare();
        if (error) { test_set_mxcsr(saved); return error; }
        // Idempotence, without reinitializing the surrounding bytes.
        candidate.device.resetDefaults();
        original_device_defaults(&oracle.device);
        error = compare();
        if (error) { test_set_mxcsr(saved); return error + 4; }
        // Explicit anchors for float encodings, sentinels and loop boundaries.
        if (candidate.device.words[0x570/4] != 0x3f800000u ||
            candidate.device.words[0x744/4] != 0x42800000u ||
            candidate.device.words[0xa64/4] != 0xffffffffu ||
            candidate.device.words[0x860/4] != 1 ||
            candidate.device.words[0xa28/4] != 0) {
            test_set_mxcsr(saved); return 7;
        }
    }
    test_set_mxcsr(saved);
    test_write("device-defaults: all checks passed\n", 35);
    return 0;
}
