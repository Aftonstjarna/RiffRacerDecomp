#include "impl.hpp"
extern "C" riff::TerminalVectorStorage* __attribute__((thiscall))
    original_node_chain_terminal_vector(riff::Node*);
extern "C" void test_write(const char*, unsigned);
static riff::Node nodes[65];
static unsigned char saved[sizeof(nodes)];
static void snapshot() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i) saved[i]=p[i];
}
static bool unchanged() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i) if (saved[i]!=p[i]) return false;
    return true;
}
static bool check(riff::Node* start, riff::Node* last) {
    snapshot();
    riff::TerminalVectorStorage* actual=original_node_chain_terminal_vector(start);
    if (actual != &last->terminal_vector || !unchanged()) return false;
    riff::TerminalVectorStorage* recovered=start->terminalVector();
    return recovered==actual && unchanged();
}
extern "C" int test_main() {
    // Distinct arbitrary bytes include NaN-like and pointer-like contents:
    // the field must be addressed, never interpreted or copied.
    unsigned char* bytes=reinterpret_cast<unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i)
        bytes[i]=static_cast<unsigned char>((i*73u+91u) ^ (i>>3));
    for (unsigned i=0; i<65; ++i) nodes[i].next=0;
    for (unsigned i=0; i<65; ++i) if (!check(&nodes[i], &nodes[i])) return 1;
    // Every length 1..65; odd-stride permutation makes links noncontiguous
    // and makes both forward and backward address transitions.
    for (unsigned length=1; length<=65; ++length) {
        for (unsigned i=0; i<65; ++i) nodes[i].next=0;
        for (unsigned i=0; i+1<length; ++i)
            nodes[(i*17u)%65].next=&nodes[((i+1)*17u)%65];
        for (unsigned i=0; i<length; ++i)
            if (!check(&nodes[(i*17u)%65], &nodes[((length-1)*17u)%65])) return 2;
    }
    // Shared suffix and a changed terminal on the next invocation: no cache.
    nodes[0].next=&nodes[64]; nodes[1].next=&nodes[64]; nodes[64].next=0;
    if (!check(&nodes[0], &nodes[64]) || !check(&nodes[1], &nodes[64])) return 3;
    nodes[64].next=&nodes[32]; nodes[32].next=0;
    if (!check(&nodes[0], &nodes[32]) || !check(&nodes[1], &nodes[32])) return 4;
    test_write("PASS: terminal chain address and untouched storage\n", 51);
    return 0;
}
