#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_ui_item_set_focus_id(UiItem*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

static unsigned fs_storage[8];
static int calls, arg1, arg2, who;
static UiItem* nodes_base;
static void __attribute__((thiscall)) focus(UiItem* p, int32_t a, int32_t b) {
    ++calls; arg1 = a; arg2 = b; who = int(p - nodes_base);
    p->unknown04 += 17; // Observable callback side effect.
}
static UiItemVtable vt;
struct Fixture { UiItem n[5]; UiItem* root_children[3]; UiItem* sub_children[1]; };
static void setup(Fixture& f) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&f);
    for (unsigned i = 0; i < sizeof f; ++i) bytes[i] = 0xa5;
    for (int i = 0; i < 5; ++i) {
        f.n[i].vtable = &vt; f.n[i].id = 10 + i; f.n[i].state = 0;
        f.n[i].flags = 6; f.n[i].alternate_eligible = 0;
        f.n[i].children_begin = f.n[i].children_end = 0;
    }
    f.root_children[0] = &f.n[1]; f.root_children[1] = &f.n[2]; f.root_children[2] = &f.n[3];
    f.sub_children[0] = &f.n[4];
    f.n[0].children_begin = f.root_children; f.n[0].children_end = f.root_children + 3;
    f.n[1].children_begin = f.sub_children; f.n[1].children_end = f.sub_children + 1;
}
static void configure(Fixture& f, int scenario) {
    switch (scenario) {
    case 0: break; // root match
    case 1: f.n[0].state = 3; break;
    case 2: f.n[0].flags = 2; break; // root prunes subtree
    case 3: f.n[0].flags = 4; f.n[0].alternate_eligible = 0x80; break;
    case 4: f.n[1].flags = 0; break; // prune matching descendant, reach sibling
    case 5: f.n[1].id = 14; break; // parent precedes matching descendant
    case 6: f.n[4].state = 3; f.n[2].id = 14; break;
    case 7: f.n[0].flags = 0xff; break;
    case 8: f.n[0].flags = 0; f.n[0].alternate_eligible = 1; break;
    case 9: f.n[0].children_end = f.n[0].children_begin; break;
    case 10: f.n[1].flags = 2; f.n[1].alternate_eligible = 2; break;
    }
}
static bool equal_nodes(const Fixture& a, const Fixture& b) {
    for (int i = 0; i < 5; ++i) {
        const unsigned char* x = reinterpret_cast<const unsigned char*>(&a.n[i]);
        const unsigned char* y = reinterpret_cast<const unsigned char*>(&b.n[i]);
        for (unsigned j = 0; j < sizeof(UiItem); ++j) {
            // Child pointers differ between fixtures; all other bytes must agree.
            if (j >= 0x178 && j < 0x180) continue;
            if (x[j] != y[j]) return false;
        }
        if (i == 0) {
            if (a.n[i].children_begin != a.root_children || b.n[i].children_begin != b.root_children ||
                a.n[i].children_end - a.root_children != b.n[i].children_end - b.root_children) return false;
        } else if (i == 1) {
            if (a.n[i].children_begin != a.sub_children || b.n[i].children_begin != b.sub_children ||
                a.n[i].children_end != a.sub_children + 1 || b.n[i].children_end != b.sub_children + 1) return false;
        } else if (a.n[i].children_begin || a.n[i].children_end || b.n[i].children_begin || b.n[i].children_end) return false;
    }
    return true;
}
extern "C" int test_main() {
    if (sizeof(void*) != 4 || __builtin_offsetof(UiItem, alternate_eligible) != 0x190) return 1;
    fs_storage[0] = 0x12345678;
    if (test_install_fs(fs_storage) != 0) return 2;
    vt.set_focus = focus;
    for (int s = 0; s <= 10; ++s) {
        for (int t = 0; t < 3; ++t) {
            Fixture a, b; setup(a); setup(b); configure(a,s); configure(b,s);
            uint32_t target = t == 0 ? 10 : t == 1 ? 14 : 0xffffffffu;
            calls = 0; arg1 = arg2 = who = -99; nodes_base = a.n;
            bool ar = original_ui_item_set_focus_id(&a.n[0], target);
            if (test_get_fs_head() != fs_storage[0]) return 3;
            int ac = calls, aa = arg1, ab = arg2, aw = who;
            calls = 0; arg1 = arg2 = who = -99; nodes_base = b.n;
            bool br = b.n[0].set_focus_id(target);
            if (ar != br || calls != ac || arg1 != aa || arg2 != ab || who != aw || !equal_nodes(a,b)) return 4 + s;
        }
    }
    return 0;
}
