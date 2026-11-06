#include "impl.hpp"
using riff::TreeNode;
extern "C" TreeNode* __attribute__((thiscall)) original_tree_rightmost(TreeNode*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static TreeNode nodes[130];
static unsigned char before[sizeof(nodes)];
static bool unchanged() {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i)
        if (bytes[i] != before[i]) return false;
    return true;
}
static int check(unsigned depth, unsigned flag, unsigned start_flag) {
    // Distinct left/parent links and metadata detect unintended writes.
    for (unsigned i=0; i<130; ++i) {
        nodes[i].left = &nodes[(i+31)%130];
        nodes[i].parent = &nodes[(i+71)%130];
        nodes[i].right = &nodes[(i+1)%130];
        nodes[i].color = static_cast<uint8_t>(i*13+7);
        nodes[i].is_nil = 0;
        nodes[i].opaque[0] = static_cast<uint8_t>(i^0x59);
        nodes[i].opaque[1] = static_cast<uint8_t>(i^0xa3);
    }
    nodes[0].is_nil = static_cast<uint8_t>(start_flag);
    nodes[depth+1].is_nil = static_cast<uint8_t>(flag);
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i) before[i]=bytes[i];
    TreeNode* original = original_tree_rightmost(&nodes[0]);
    if (test_get_fs_head()!=0x12345678u) return 1;
    if (original != &nodes[depth] || !unchanged()) return 2;
    TreeNode* recovered = nodes[0].rightmost();
    if (recovered != original || !unchanged()) return 3;
    return 0;
}
extern "C" int test_main() {
    unsigned fs_storage[8] = {0x12345678u,0,0,0,0,0,0,0};
    if (test_install_fs(fs_storage)!=0) return 10;
    const unsigned depths[] = {0,1,2,7,31,127};
    for (unsigned d=0; d<6; ++d)
        for (unsigned flag=1; flag<=255; ++flag)
            for (unsigned start=0; start<2; ++start) {
                int result=check(depths[d],flag,start ? 0xa5 : 0);
                if (result) return 20+result;
            }
    // Conventional empty header: a flagged node whose right link is itself.
    nodes[0].right=&nodes[0]; nodes[0].is_nil=1;
    const unsigned char* bytes=reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0;i<sizeof(nodes);++i) before[i]=bytes[i];
    if(original_tree_rightmost(&nodes[0])!=&nodes[0]) return 30;
    if(test_get_fs_head()!=0x12345678u || !unchanged()) return 31;
    if(nodes[0].rightmost()!=&nodes[0] || !unchanged()) return 32;
    test_write("tree-rightmost: passed\n",23);
    return 0;
}
