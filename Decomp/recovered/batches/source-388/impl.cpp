#include "impl.hpp"
namespace riff {
// Game.exe VA 0x440a60, RVA 0x40a60, 41 bytes. ECX=this,
// one callee-popped result-slot argument; EAX returns that same slot.
// Callers at 0x5c1fab and 0x5c2008 consume *result as a range endpoint.
char** RIFF_THISCALL NarrowString::end_pointer(char** result) {
    char* base = capacity < 16 ? storage.inline_bytes : storage.heap;
    // Integer address arithmetic preserves the original unchecked x86 add,
    // including malformed lengths, without C++ out-of-array pointer addition.
    const uintptr_t end = reinterpret_cast<uintptr_t>(base) + length;
    *result = reinterpret_cast<char*>(end);
    return result;
}
}
