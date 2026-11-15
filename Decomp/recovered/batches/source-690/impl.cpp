#include "impl.hpp"
#include <stddef.h>
extern "C" void* memcpy(void*, const void*, size_t);
#ifdef _MSC_VER
#pragma intrinsic(memcpy)
#endif
// The only direct caller found (0x46ab1a) copies this prefix to a stack
// matrix, then separately copies floats at +0x30..+0x3c. Those are not ours.
// No pointer checks, allocation, globals, floating operations or result contract.
// Each DWORD is completely read before its store: overlap propagates forward;
// substituting memcpy of the entire object or memmove changes that behavior.
void RIFF_THISCALL Matrix3Storage::copy_storage(const void* source) {
    const unsigned char* input = static_cast<const unsigned char*>(source);
    unsigned char* output = reinterpret_cast<unsigned char*>(this);
    for (unsigned row = 0; row < 3; ++row) {
        for (unsigned column = 0; column < 4; ++column) {
            const unsigned offset = row * 16 + column * 4;
            uint32_t word;
            memcpy(&word, input + offset, sizeof word);
            memcpy(output + offset, &word, sizeof word);
        }
    }
}
