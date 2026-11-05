#include "impl.hpp"
// Game.exe VA 0x44fab0, RVA 0x4fab0, size 37, thiscall, callee pops 4.
// The unsigned capacity comparison precedes the length store in the original.
// Callers such as 0x536143 (append substring) ignore EAX. It contains the
// heap pointer on the heap path and zero on the inline path; this is not a
// consistent C++ return value. Model the method as void.
// No allocation, capacity update, encoding validation or range check occurs.
void RIFF_THISCALL WideString::set_length(uint32_t new_length) {
    length = new_length;
    if (capacity >= 8u)
        storage.heap[new_length] = 0;
    else
        storage.inline_units[new_length] = 0;
}
