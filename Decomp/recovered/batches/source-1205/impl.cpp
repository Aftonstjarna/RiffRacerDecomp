#include "impl.hpp"
using namespace riff;
// VA 0x4f1320. Counts are signed and are re-read after each marker call.
extern "C" void RIFF_FASTCALL visit_prototype(Global* global, Prototype* p) {
    if (p->source) p->source->marked &= 0xfc;
    for (int32_t i = 0; i < p->constantCount; ++i) {
        Value* v = &p->constants[i];
        if (v->tag >= 4 && (v->object->marked & 3))
            original_script_gc_mark_object(global, v->object);
    }
    for (int32_t i = 0; i < p->nameCount; ++i)
        if (p->names[i]) p->names[i]->marked &= 0xfc;
    for (int32_t i = 0; i < p->childCount; ++i) {
        Object* child = p->children[i];
        if (child && (child->marked & 3))
            original_script_gc_mark_object(global, child);
    }
    for (int32_t i = 0; i < p->localCount; ++i)
        if (p->locals[i].name) p->locals[i].name->marked &= 0xfc;
}
