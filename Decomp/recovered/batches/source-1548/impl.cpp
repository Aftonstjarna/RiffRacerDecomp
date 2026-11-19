#include "impl.hpp"

// VA 0x55b470, virtual slot +0x20. ECX is this; one stack argument,
// callee-popped. EAX returns the output pointer. Preserve the ordered loads:
// output can overlap the stored words.
uint32_t* InputPointer::get_pointer(uint32_t* output)
{
    if (suppress_pointer) {
        output[0] = 0;
        output[1] = 0;
    } else {
        output[0] = pointer_words[0];
        output[1] = pointer_words[1];
    }
    return output;
}
