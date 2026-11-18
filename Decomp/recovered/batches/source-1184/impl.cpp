#include "impl.hpp"
namespace riff {
// 0x4f20e0, thiscall. Call sites at 0x4f224c, 0x4f2377 and
// 0x4f251f enter from GC phase-driving code. All accessed pointers must
// be valid on their paths; field names are provisional.
void State::beginMark() {
    Global* g = global;
    g->gray = 0;
    g->gray_again = 0;
    g->weak = 0;
    Object* first = reinterpret_cast<Object*>(g->main_thread);
    if (first->marks & 3) markObject(g, first);
    ThreadObject* thread = g->main_thread;
    if (thread->value.tag >= 4 && (thread->value.object->marks & 3))
        markObject(g, thread->value.object);
    Global* current = global;
    if (current->value.tag >= 4 && (current->value.object->marks & 3))
        markObject(g, current->value.object);
    scanRoots(g);
    g->phase = 1;
}
}
