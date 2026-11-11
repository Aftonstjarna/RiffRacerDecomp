#include "impl.hpp"
extern "C" riff::FourRecord20* __attribute__((thiscall))
    original_four_record20_initialize(riff::FourRecord20*);
extern "C" void test_write(const char*, unsigned);
struct Guarded {
    uint32_t before[4];
    riff::FourRecord20 object;
    uint32_t after[4];
};
static unsigned char pattern(unsigned seed, unsigned index) {
    if (seed < 256) return static_cast<unsigned char>(seed);
    return static_cast<unsigned char>((seed * 37 + index * 73) ^ (index >> 1));
}
extern "C" int test_main() {
    for (unsigned seed = 0; seed < 512; ++seed) {
        Guarded recovered, original;
        unsigned char* a = reinterpret_cast<unsigned char*>(&recovered);
        unsigned char* b = reinterpret_cast<unsigned char*>(&original);
        for (unsigned i = 0; i < sizeof(Guarded); ++i)
            a[i] = b[i] = pattern(seed, i);
        for (unsigned repeat = 0; repeat != 2; ++repeat) {
            if (recovered.object.initialize() != &recovered.object) return 1;
            if (original_four_record20_initialize(&original.object) != &original.object) return 2;
            for (unsigned i = 0; i < sizeof(Guarded); ++i) {
                unsigned char expected = pattern(seed, i);
                if (i >= offsetof(Guarded, object) && i < offsetof(Guarded, after)) {
                    unsigned offset = (i - offsetof(Guarded, object)) % 20;
                    if (offset >= 4 && offset < 16) expected = 0;
                    if (offset == 16) expected = 1;
                }
                if (a[i] != b[i] || a[i] != expected) return 3;
            }
        }
    }
    const char message[] = "four-record20-initialize: passed 512 patterns, repeat, guards and preserved bytes\n";
    test_write(message, sizeof(message) - 1);
    return 0;
}
