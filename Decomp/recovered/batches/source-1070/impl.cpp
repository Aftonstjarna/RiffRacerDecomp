#include "impl.hpp"
namespace riff {
// 0x4f2150. Callers provide a valid circular list and valid pointers for
// every value whose tag is at least 4. The signed tag comparison is intentional.
void Global::scanLinkedValues() {
    for (LinkedValue* node = sentinel.next; node != &sentinel; node = node->next) {
        if ((node->marked & 7) != 0) continue;
        Value* value = node->value;
        if (value->tag >= 4 && (value->object->marked & 3) != 0)
            markObject(this, value->object);
    }
}
}
