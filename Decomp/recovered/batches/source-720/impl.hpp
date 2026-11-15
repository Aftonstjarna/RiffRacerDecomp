#ifndef RIFF_NODE_CHAIN_TERMINAL_VECTOR_HPP
#define RIFF_NODE_CHAIN_TERMINAL_VECTOR_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Only the observed layout is recovered. The name 'vector' comes from the
// assigned evidence; this routine does not establish its element type or ABI.
struct TerminalVectorStorage { uint8_t opaque[16]; };
struct Node {
    uint8_t unknown_000[0x1b0];
    TerminalVectorStorage terminal_vector;
    Node* next;
    TerminalVectorStorage* RIFF_THISCALL terminalVector();
};
static_assert(offsetof(Node, terminal_vector) == 0x1b0, "original field offset");
static_assert(offsetof(Node, next) == 0x1c0, "original link offset");
}
#endif
