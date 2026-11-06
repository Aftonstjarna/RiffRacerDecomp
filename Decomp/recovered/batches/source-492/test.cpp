#include "impl.hpp"
#include <stddef.h>
using riff::TreeNode;
using riff::TreeIterator;
extern "C" TreeIterator* __attribute__((thiscall)) original_tree_iterator_decrement(TreeIterator*);
static_assert(sizeof(void*) == 4, "oracle requires i386");
static_assert(offsetof(TreeNode, sentinel) == 13, "node ABI");
static_assert(sizeof(TreeNode) == 16, "node prefix ABI");
static_assert(sizeof(TreeIterator) == 4, "iterator ABI");
struct FixtureNode { TreeNode link; uint32_t payload[3]; };
static FixtureNode nodes[8];
static unsigned char snapshot[sizeof(nodes)];
static unsigned cases;
static bool unchanged() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i) if (p[i]!=snapshot[i]) return false;
    return true;
}
static int check(TreeNode* start, TreeNode* expected) {
    struct Guarded { uint32_t before; TreeIterator it; uint32_t after; };
    Guarded a = {0x13579bdf, {start}, 0xfedcba98};
    Guarded b = a;
    TreeIterator* returned = original_tree_iterator_decrement(&a.it);
    if (returned != &a.it || a.it.node != expected || !unchanged()) return 1;
    if (a.before!=b.before || a.after!=b.after) return 2;
    if (b.it.decrement()!=&b.it || b.it.node!=a.it.node || !unchanged()) return 3;
    if (b.before!=a.before || b.after!=a.after) return 4;
    ++cases;
    return 0;
}
static int exercise(const unsigned* order, unsigned count, unsigned char marker) {
    unsigned char* raw = reinterpret_cast<unsigned char*>(nodes);
    for (unsigned i=0; i<sizeof(nodes); ++i) raw[i]=static_cast<unsigned char>(i*37+11);
    TreeNode* head=&nodes[0].link;
    head->left=head; head->parent=head; head->right=head; head->sentinel=marker;
    for (unsigned i=1; i<=count; ++i) {
        TreeNode* n=&nodes[i].link;
        n->left=head; n->right=head; n->parent=head; n->sentinel=0;
    }
    for (unsigned k=0; k<count; ++k) {
        unsigned id=order[k];
        TreeNode* n=&nodes[id].link;
        TreeNode* parent=head;
        TreeNode** slot=&head->parent;
        while (*slot != head) {
            parent=*slot;
            unsigned parentId=static_cast<unsigned>((reinterpret_cast<FixtureNode*>(parent))-nodes);
            slot=id<parentId ? &parent->left : &parent->right;
        }
        *slot=n; n->parent=parent;
    }
    if (count) { head->left=&nodes[1].link; head->right=&nodes[count].link; }
    for (unsigned i=0; i<sizeof(nodes); ++i) snapshot[i]=raw[i];
    int result=check(head,count ? &nodes[count].link : head);
    if(result) return result;
    for(unsigned i=1; i<=count; ++i) {
        result=check(&nodes[i].link, i==1 ? head : &nodes[i-1].link);
        if(result) return result;
    }
    return 0;
}
static int permutations(unsigned* order,unsigned depth,unsigned count) {
    if(depth==count) {
        const unsigned char markers[3]={1,128,255};
        for(unsigned k=0;k<3;++k) {
            int result=exercise(order,count,markers[k]);
            if(result) return result;
        }
        return 0;
    }
    for(unsigned k=depth;k<count;++k) {
        unsigned temp=order[k]; order[k]=order[depth]; order[depth]=temp;
        int result=permutations(order,depth+1,count);
        temp=order[k]; order[k]=order[depth]; order[depth]=temp;
        if(result) return result;
    }
    return 0;
}
extern "C" int test_main() {
    unsigned order[7]={1,2,3,4,5,6,7};
    for(unsigned n=0;n<=7;++n) {
        int result=permutations(order,0,n);
        if(result) return result;
    }
    return cases==138699 ? 0 : 5;
}
