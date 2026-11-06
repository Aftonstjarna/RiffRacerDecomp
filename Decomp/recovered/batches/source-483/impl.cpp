#include "impl.hpp"
namespace {
uint16_t read16(const unsigned char* p) {
    return static_cast<uint16_t>(p[0] | (static_cast<uint16_t>(p[1]) << 8));
}
uint32_t read32(const unsigned char* p) {
    return static_cast<uint32_t>(read16(p)) |
           (static_cast<uint32_t>(read16(p + 2)) << 16);
}
}
// The original cdecl helper is used at 0x8f9abf with base 0x400000;
// the caller cleans its argument and branches on EAX. No object or imports.
// This is a signature probe, not a safe parser: no length, machine, section,
// optional-header-size, or e_lfanew-range validation is performed.
extern "C" int RIFF_CDECL pe32_image_validate(const void* image) {
    const unsigned char* base = static_cast<const unsigned char*>(image);
    if (read16(base) != 0x5a4d) return 0;
    // Integer address addition preserves the original modulo-2^32 addition
    // on the original 32-bit target, including offsets pointing before base.
    const uintptr_t ntAddress = reinterpret_cast<uintptr_t>(base) + read32(base + 0x3c);
    const unsigned char* nt = reinterpret_cast<const unsigned char*>(ntAddress);
    if (read32(nt) != 0x00004550) return 0;
    return read16(nt + 0x18) == 0x010b ? 1 : 0;
}
