#include "impl.hpp"
#include <stddef.h>
#include <stdint.h>
extern "C" void __attribute__((thiscall)) original_matrix3_identity_initialize(Matrix3*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

struct Guarded {
    uint32_t before[4];
    Matrix3 value;
    uint32_t after[4];
};
static_assert(offsetof(Guarded, value) == 16, "guard layout");
static_assert(offsetof(Guarded, after) == 64, "guard layout");
static_assert(offsetof(Matrix3, trailing) == 36, "field layout");
static unsigned char* bytes(void* p) { return static_cast<unsigned char*>(p); }
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i = 0; i < n; ++i) if (x[i] != y[i]) return false;
    return true;
}
extern "C" int test_main() {
    uint32_t fs_storage[8] = {0x13579bdfu};
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned saved_mxcsr = test_get_mxcsr();
    int result = 0;
    // All rounding modes, DAZ/FTZ settings and clear/set sticky flags.
    for (unsigned mode = 0; mode < 32 && !result; ++mode) {
        const unsigned control = 0x1f80u | ((mode & 3u) << 13)
            | ((mode & 4u) ? 0x40u : 0u) | ((mode & 8u) ? 0x8000u : 0u)
            | ((mode & 16u) ? 0x3fu : 0u);
        for (unsigned pattern = 0; pattern < 20 && !result; ++pattern) {
            Guarded expected, recovered, oracle;
            // Includes all-zero/all-ones, arbitrary float bit patterns (NaNs,
            // infinities, signed zeros and subnormals), and varying guards.
            const uint32_t special[] = {0u, 0xffffffffu, 0x80000000u,
                0x7f800000u, 0xff800000u, 0x7fc12345u, 0x7f800001u, 1u};
            for (unsigned i = 0; i < sizeof(Guarded); ++i) {
                const uint32_t word = pattern < 8 ? special[pattern]
                    : (0x9e3779b9u * (pattern + i / 4 + 1));
                bytes(&expected)[i] = static_cast<unsigned char>(word >> (8 * (i % 4)));
                bytes(&recovered)[i] = bytes(&expected)[i];
                bytes(&oracle)[i] = bytes(&expected)[i];
            }
            for (unsigned i = 0; i < 48; ++i) bytes(&expected.value)[i] = 0;
            const unsigned diagonal[] = {0, 16, 32};
            for (unsigned i = 0; i < 3; ++i) {
                bytes(&expected.value)[diagonal[i] + 2] = 0x80;
                bytes(&expected.value)[diagonal[i] + 3] = 0x3f;
            }
            test_set_mxcsr(control);
            for (unsigned repeat = 0; repeat < 2; ++repeat) {
                original_matrix3_identity_initialize(&oracle.value);
                if (test_get_fs_head() != fs_storage[0]) { result = 2; break; }
                if (test_get_mxcsr() != control) { result = 3; break; }
                recovered.value.initialize_identity();
                if (test_get_mxcsr() != control) { result = 4; break; }
                if (!equal(&oracle, &expected, sizeof(Guarded))) { result = 5; break; }
                if (!equal(&recovered, &oracle, sizeof(Guarded))) { result = 6; break; }
            }
        }
    }
    test_set_mxcsr(saved_mxcsr);
    return result;
}
