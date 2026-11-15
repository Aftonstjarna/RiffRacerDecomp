#include "impl.hpp"
#include <stddef.h>
namespace riff {
// Game.exe 0x44be60..0x44be8c. Caller at 0x44badf passes begin/end
// from [ebx]/[ebx+4], and newly allocated storage in the stack argument.
// Original ABI: ECX begin, EDX end, [ESP+4] destination, caller cleanup.
// This is a free range algorithm, not an object member method.
void pointer_slot_range_copy_retain(RetainedObject* const* begin,
                                   RetainedObject* const* end,
                                   RetainedObject** destination) {
    uintptr_t output = reinterpret_cast<uintptr_t>(destination);
    while (begin != end) {
        // Original tests the current output address each iteration. In
        // particular a null initial output skips only the FIRST source read;
        // for a longer range it advances to address 4 and would fault.
        if (output != 0) {
            RetainedObject* object = *begin;
            *reinterpret_cast<RetainedObject**>(output) = object;
            if (object != 0) ++object->references;
        }
        ++begin;
        output += sizeof(RetainedObject*);
    }
}
}
