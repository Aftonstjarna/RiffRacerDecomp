#include "impl.hpp"
#include <stdint.h>

extern "C" Matrix3Identity* __attribute__((thiscall)) original_matrix3_identity_construct(Matrix3Identity*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);

struct Fixture { uint32_t before[4]; Matrix3Identity matrix; uint32_t after[4]; };
static unsigned char fs_storage[4096] __attribute__((aligned(16)));

extern "C" int test_main() {
    *reinterpret_cast<uint32_t*>(fs_storage) = 0x12345678u;
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned fs_head = test_get_fs_head();
    const unsigned old_mxcsr = test_get_mxcsr();
    for (unsigned trial = 0; trial < 6; ++trial) {
        Fixture a, b;
        unsigned char* pa = reinterpret_cast<unsigned char*>(&a);
        unsigned char* pb = reinterpret_cast<unsigned char*>(&b);
        for (unsigned i = 0; i < sizeof(a); ++i) {
            unsigned char value = static_cast<unsigned char>(trial == 0 ? 0 : trial == 1 ? 255 : (i * 53u + trial * 71u));
            pa[i] = pb[i] = value;
        }
        // Exercise differing floating-point environment flags and rounding modes.
        const unsigned mode = (old_mxcsr & ~0x603fu) | ((trial & 3u) << 13) | (trial & 0x3fu);
        test_set_mxcsr(mode);
        Matrix3Identity* expected = original_matrix3_identity_construct(&a.matrix);
        if (test_get_fs_head() != fs_head || expected != &a.matrix || test_get_mxcsr() != mode) return 2;
        Matrix3Identity* actual = b.matrix.initialize_identity();
        if (actual != &b.matrix || test_get_mxcsr() != mode) return 3;
        for (unsigned i = 0; i < sizeof(a); ++i) if (pa[i] != pb[i]) return 4;
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&b.matrix);
        for (unsigned i = 0; i < 12; ++i) {
            const uint32_t word = static_cast<uint32_t>(p[4*i]) | (static_cast<uint32_t>(p[4*i+1]) << 8) | (static_cast<uint32_t>(p[4*i+2]) << 16) | (static_cast<uint32_t>(p[4*i+3]) << 24);
            if (word != ((i == 0 || i == 4 || i == 8) ? 0x3f800000u : 0u)) return 5;
        }
    }
    test_set_mxcsr(old_mxcsr);
    return 0;
}
