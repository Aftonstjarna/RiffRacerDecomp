#include "impl.hpp"
#include <stddef.h>
using riff::TreeNode;
using riff::Tree;
extern "C" void __attribute__((thiscall)) original_tree_rotate_right(Tree*, TreeNode*);
static_assert(sizeof(void*) == 4, "original oracle requires i386");
static_assert(offsetof(TreeNode, is_nil) == 13, "original node layout");
static_assert(offsetof(TreeNode, color) == 12, "original node layout");
struct NodeStorage { TreeNode node; unsigned char payload[32]; };
struct Fixture { unsigned before[4]; Tree tree; unsigned metadata[5]; NodeStorage nodes[8]; unsigned after[4]; };
static Fixture fixture;
static unsigned char initial[sizeof(Fixture)], expected[sizeof(Fixture)], observed[sizeof(Fixture)];
static void copy(void* dst, const void* src, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
// Every comparison uses the same addresses: restore the fixture between calls.
// Independent expected-image edits also verify all bytes not written by the
// rotation, including sentinel parent, header extrema, payload and metadata.
extern "C" int test_main() {
    const unsigned char nil_values[] = {0,1,2,255};
    for(unsigned branch=0;branch<3;++branch)
    for(unsigned nil=0;nil<4;++nil)
    for(unsigned seed=0;seed<16;++seed) {
        unsigned char* bytes=reinterpret_cast<unsigned char*>(&fixture);
        for(unsigned i=0;i<sizeof(fixture);++i) bytes[i]=static_cast<unsigned char>(i*37+seed*19);
        TreeNode* h=&fixture.nodes[0].node;
        TreeNode* p=&fixture.nodes[1].node;
        TreeNode* x=&fixture.nodes[2].node;
        TreeNode* y=&fixture.nodes[3].node;
        TreeNode* b=&fixture.nodes[4].node;
        TreeNode* extra=&fixture.nodes[5].node;
        for(unsigned i=0;i<8;++i) {
            TreeNode* n=&fixture.nodes[i].node;
            n->left=h; n->right=h; n->parent=h;
            n->color=static_cast<unsigned char>(seed+i);
            n->is_nil=0;
        }
        fixture.tree.head=h; h->is_nil=1;
        h->left=y; h->right=extra; h->parent=(branch==0 ? x:p);
        p->left=branch==2 ? x:extra;
        p->right=branch==1 ? x:extra;
        x->parent=branch==0 ? h:p; x->left=y; x->right=extra;
        y->parent=x; y->left=extra; y->right=b;
        b->parent=y; b->is_nil=nil_values[nil];
        // Also exercise the usual shared header sentinel as transferred child.
        if(nil && (seed&1)) { y->right=h; b=h; h->is_nil=nil_values[nil]; }
        copy(initial,&fixture,sizeof(fixture));
        x->left=b;
        if(!b->is_nil) b->parent=x;
        y->parent=branch==0 ? h:p;
        if(branch==0) h->parent=y;
        else if(branch==1) p->right=y;
        else p->left=y;
        y->right=x; x->parent=y;
        copy(expected,&fixture,sizeof(fixture));
        copy(&fixture,initial,sizeof(fixture));
        original_tree_rotate_right(&fixture.tree,x);
        if(!equal(&fixture,expected,sizeof(fixture))) return 1;
        copy(observed,&fixture,sizeof(fixture));
        copy(&fixture,initial,sizeof(fixture));
        fixture.tree.rotate_right(x);
        if(!equal(&fixture,observed,sizeof(fixture))) return 2;
    }
    return 0;
}
