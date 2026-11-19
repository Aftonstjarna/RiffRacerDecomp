#ifndef INPUT_POINTER_GET_HPP
#define INPUT_POINTER_GET_HPP
#include <stdint.h>
#include <stddef.h>

// Partial input object; names describe observed storage, not inferred meaning.
struct InputPointer {
    uint8_t unknown000[0x23c];
    uint32_t pointer_words[2];
    uint8_t unknown244[2];
    uint8_t suppress_pointer;
    uint32_t* get_pointer(uint32_t* output);
};
static_assert(offsetof(InputPointer, pointer_words) == 0x23c, "pointer offset");
static_assert(offsetof(InputPointer, suppress_pointer) == 0x246, "flag offset");
#endif
