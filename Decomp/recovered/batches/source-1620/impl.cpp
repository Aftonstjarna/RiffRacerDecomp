#include "impl.hpp"

// Game.exe 0x448180: eligibility applies to the entire subtree. The callback
// and state names are provisional; the slot receives (1, -1).
bool UiItem::set_focus_id(uint32_t target) {
    if ((flags & 6) != 6 && !alternate_eligible)
        return false;
    if (id == target) {
        if (state != 3)
            vtable->set_focus(this, 1, -1);
        return true;
    }
    for (UiItem** child = children_begin; child != children_end; ++child) {
        if ((*child)->set_focus_id(target))
            return true;
    }
    return false;
}
