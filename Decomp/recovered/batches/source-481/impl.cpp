#include "impl.hpp"
namespace {
uint16_t read16(const unsigned char* p) {
    return static_cast<uint16_t>(p[0] | (static_cast<uint16_t>(p[1]) << 8));
}
uint32_t read32(const unsigned char* p) {
    return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8)
        | (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
}
}
// Game.exe VA 0x8f9a30, RVA 0x4f9a30, 67 bytes. Free cdecl function,
// not a member: two stack arguments, caller cleanup, pointer result in EAX.
// Direct caller at 0x8f9ad9 subtracts image base from its address argument,
// then uses section Characteristics (+0x24) to check IMAGE_SCN_MEM_WRITE.
extern "C" const unsigned char* RIFF_CDECL pe_section_lookup(
    const void* image, uint32_t relative_virtual_address) {
    const unsigned char* base = static_cast<const unsigned char*>(image);
    const unsigned char* nt = base + read32(base + 0x3c);
    const uint32_t count = read16(nt + 6);
    const unsigned char* section = nt + 0x18 + read16(nt + 0x14);
    for (uint32_t i = 0; i < count; ++i, section += 0x28) {
        const uint32_t start = read32(section + 0x0c);
        // Deliberately wrap the addition, just as the original ADD does.
        // Using RVA-start < size would change behavior for overflowing ranges.
        const uint32_t end = start + read32(section + 8);
        if (relative_virtual_address >= start && relative_virtual_address < end)
            return section;
    }
    return 0;
}
