#include "impl.hpp"
namespace riff {
// Game.exe 0x4270e0..0x427105, thiscall, callee pops one pointer;
// AL is the Boolean result (upper EAX bits are not a result).
// Original loads proxy+4 first, and skips the second pair if it rejects.
// Valid object/proxy storage is required; the original has no null checks.
// No writes, calls, floating-point work or exception registration occur.
// Two vtable references: 0x9f8e64 and 0x9fa82c, both slot +4.
// No direct E8 callers found in the image. The latter vtable is installed
// into a stack callback at 0x461d2e; exact original C++ class names and full
// object extents remain unresolved. group/mask are semantic field names.
bool RIFF_THISCALL RayCallbackFilter::accepts(const BroadphaseFilter* proxy) const {
    if ((proxy->group & mask) == 0)
        return false;
    return (proxy->mask & group) != 0;
}
}
