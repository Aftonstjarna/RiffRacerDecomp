#include "impl.hpp"
void* operator new(size_t, void* storage) noexcept { return storage; }
extern "C" WorkerState* __attribute__((thiscall)) original_worker_state_construct(void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);

static uint8_t expectedByte(unsigned offset) {
    if (offset < 0x60) {
        const uint8_t bits[4] = {0x9a, 0x99, 0x19, 0x3f};
        return bits[offset % 4];
    }
    if (offset >= 0x120 && offset < 0x180 && offset % 4 == 0) return 2;
    return 0;
}
extern "C" int test_main() {
    uint32_t fsStorage[8] = {0xabcdef01u, 0, 0, 0, 0, 0, 0, 0};
    if (test_install_fs(fsStorage) != 0) return 1;
    const unsigned savedMxcsr = test_get_mxcsr();
    alignas(4) uint8_t original[0x234 + 64];
    alignas(4) uint8_t recovered[0x234 + 64];
    // All byte poison values, three aligned placements, four rounding modes.
    for (unsigned seed = 0; seed < 256; ++seed) {
        for (unsigned placement = 0; placement < 3; ++placement) {
            unsigned start = 4 + placement * 12;
            unsigned control = (savedMxcsr & ~0x6000u) | ((seed % 4) << 13);
            test_set_mxcsr(control);
            for (unsigned i = 0; i < sizeof(original); ++i) {
                original[i] = recovered[i] = static_cast<uint8_t>(seed + i * 37);
            }
            WorkerState* result = original_worker_state_construct(original + start);
            if (test_get_fs_head() != fsStorage[0]) return 2;
            if (reinterpret_cast<void*>(result) != original + start) return 3;
            if (test_get_mxcsr() != control) return 4;
            WorkerState* built = new (recovered + start) WorkerState;
            if (reinterpret_cast<void*>(built) != recovered + start) return 5;
            if (test_get_mxcsr() != control) return 6;
            for (unsigned i = 0; i < sizeof(original); ++i) {
                uint8_t expected = (i >= start && i < start + sizeof(WorkerState))
                    ? expectedByte(i - start) : static_cast<uint8_t>(seed + i * 37);
                if (original[i] != recovered[i] || original[i] != expected) return 7;
            }
            // Repeat on initialized state: construction has no previous-state dependency.
            original_worker_state_construct(original + start);
            if (test_get_fs_head() != fsStorage[0]) return 8;
            new (recovered + start) WorkerState;
            for (unsigned i = 0; i < sizeof(original); ++i)
                if (original[i] != recovered[i]) return 9;
        }
    }
    test_set_mxcsr(savedMxcsr);
    test_write("worker-state-construct: passed\n", 31);
    return 0;
}
