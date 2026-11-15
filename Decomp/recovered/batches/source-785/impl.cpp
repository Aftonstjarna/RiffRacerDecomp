#include "impl.hpp"
#include <stddef.h>
static_assert(sizeof(ScriptNode) == 20, "32-bit node layout");
static_assert(offsetof(ScriptTable, arraySize) == 28, "32-bit table layout");
// Original VA 0x4f0d80..0x4f0e84. Tail-called by table length at
// 0x4f0edd: ECX=this, EDX=arraySize, result EAX; no stack arguments.
// Read-only. The lower endpoint is presumed occupied by normal callers.
// Holes preserve the original choices, not a unique mathematical length.
uint32_t RIFF_FASTCALL ScriptTable::hashBoundary(uint32_t lower) const {
    uint32_t upper = lower + 1u;
    for (;;) {
        bool occupied;
        if (upper - 1u < arraySize) {
            occupied = array[upper - 1u].tag != 0;
        } else {
            // CVTDQ2PS interprets the index as signed, including wrapped inputs.
            const float key = static_cast<float>(static_cast<int32_t>(upper));
            uint32_t bits;
            // Character copying avoids aliasing and union type-punning assumptions.
            const unsigned char* src = reinterpret_cast<const unsigned char*>(&key);
            unsigned char* dst = reinterpret_cast<unsigned char*>(&bits);
            for (unsigned i = 0; i < 4; ++i) dst[i] = src[i];
            const uint32_t divisor = ((1u << (hashLogSize & 31u)) - 1u) | 1u;
            ScriptNode* node = hash + (key == 0.0f ? 0u : bits % divisor);
            while (node && !(node->keyTag == 3u && node->key == key)) node = node->next;
            // Original uses shared nil TValue at 0x99a41c on a miss.
            occupied = node && node->value.tag != 0;
        }
        if (!occupied) break;
        lower = upper;
        upper += upper;
        if (upper > 0x7ffffffdu) {
            uint32_t index = 1;
            while (script_table_get_integer(this, index)->tag != 0) ++index;
            return index - 1u;
        }
    }
    while (upper - lower > 1u) {
        const uint32_t middle = (lower + upper) >> 1;
        if (script_table_get_integer(this, middle)->tag == 0) upper = middle;
        else lower = middle;
    }
    return lower;
}
