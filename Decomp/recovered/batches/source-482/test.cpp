#include "impl.hpp"
#include <stddef.h>
using riff::TreeNode;
using riff::Tree;
static_assert(sizeof(void*) == 4, "oracle is i386");
static_assert(offsetof(TreeNode, parent)==4 && offsetof(TreeNode,right)==8 && offsetof(TreeNode,color)==12 && offsetof(TreeNode,is_nil)==13,"node ABI");
extern "C" void __attribute__((thiscall)) original_tree_rotate_left(Tree*, TreeNode*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct NodeStorage { TreeNode node; unsigned char payload[18]; };
struct Fixture { Tree tree; unsigned tree_tail[5]; NodeStorage nodes[8]; unsigned guards[4]; };
static Fixture f;
static unsigned char before[sizeof(Fixture)], expected[sizeof(Fixture)];
static void copy(void* dst,const void* src,unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i)d[i]=s[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
extern "C" int test_main() {
    unsigned fs_storage[8]={0x13572468u,0,0,0,0,0,0,0};
    if(test_install_fs(fs_storage)!=0)return 1;
    const unsigned flags[3]={0,1,255};
    for(unsigned mode=0;mode<4;++mode)for(unsigned flag=0;flag<3;++flag)
    for(unsigned seed=0;seed<16;++seed) {
        unsigned char* raw=reinterpret_cast<unsigned char*>(&f);
        for(unsigned i=0;i<sizeof(f);++i)raw[i]=static_cast<unsigned char>(i*37+seed*19);
        for(unsigned i=0;i<8;++i){
            TreeNode& n=f.nodes[i].node;
            n.left=&f.nodes[0].node;n.parent=&f.nodes[0].node;n.right=&f.nodes[0].node;
            n.color=static_cast<uint8_t>(seed+i);n.is_nil=0;
        }
        TreeNode* h=&f.nodes[0].node;
        TreeNode* x=&f.nodes[1].node;
        TreeNode* y=&f.nodes[2].node;
        TreeNode* p=&f.nodes[3].node;
        TreeNode* middle=flag==1 ? h : &f.nodes[4].node;
        f.tree.head=h;h->is_nil=1;h->parent=mode==0?x:p;
        h->left=&f.nodes[5].node;h->right=&f.nodes[6].node;
        x->parent=mode==0?h:p;x->right=y;
        y->parent=x;y->left=middle;
        middle->is_nil=static_cast<uint8_t>(flags[flag]);
        if(mode==1)p->left=x;
        if(mode==2)p->right=x;
        // mode 3 also checks the original's unconditional right-link fallback
        // when the pivot is neither of the recorded parent's children.
        copy(before,&f,sizeof(f));
        original_tree_rotate_left(&f.tree,x);
        if(test_get_fs_head()!=fs_storage[0])return 2;
        copy(expected,&f,sizeof(f));
        if(x->right!=middle || x->parent!=y || y->left!=x ||
           y->parent!=(mode==0?h:p))return 3;
        if((mode==0?h->parent:(mode==1?p->left:p->right))!=y)return 4;
        if(!middle->is_nil && middle->parent!=x)return 5;
        // Entire fixture comparison includes payload, padding, colors, nil flags,
        // tree tail, unrelated nodes and all sentinel links, at identical addresses.
        copy(&f,before,sizeof(f));
        f.tree.rotate_left(x);
        if(!equal(&f,expected,sizeof(f)))return 6;
    }
    return 0;
}
