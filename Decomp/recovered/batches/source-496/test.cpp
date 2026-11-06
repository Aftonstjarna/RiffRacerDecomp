#include "impl.hpp"
#include <stddef.h>
static_assert(sizeof(void*) == 4, "oracle requires i386");
static_assert(offsetof(TreeNode, is_nil) == 13, "node ABI");
static_assert(sizeof(TreeIterator) == 4, "iterator ABI");
extern "C" TreeIterator* __attribute__((thiscall)) original_tree_iterator_increment(TreeIterator*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
extern "C" void test_write(const char*, unsigned);
struct Record { TreeNode node; uint32_t payload[3]; };
struct Guarded { uint32_t before; TreeIterator it; uint32_t after; };
static Record records[8];
static unsigned char snapshot[sizeof(records)];
static unsigned checks;
static void save() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(records);
    for (unsigned i=0;i<sizeof(records);++i) snapshot[i]=p[i];
}
static bool unchanged() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(records);
    for (unsigned i=0;i<sizeof(records);++i) if (snapshot[i]!=p[i]) return false;
    return true;
}
static bool check(TreeNode* start, TreeNode* expected) {
    Guarded a = {0x12345678u, {start}, 0xfedcba98u};
    Guarded b = {0x12345678u, {start}, 0xfedcba98u};
    save();
    TreeIterator* result = original_tree_iterator_increment(&a.it);
    if (test_get_fs_head()!=0x13572468u) return false;
    if (result != &a.it || a.it.node != expected || !unchanged()) return false;
    TreeIterator* recovered = &b.it.increment();
    if (recovered != &b.it || b.it.node != a.it.node || !unchanged()) return false;
    if (a.before!=0x12345678u || b.before!=a.before ||
        a.after!=0xfedcba98u || b.after!=a.after) return false;
    ++checks;
    return true;
}
static bool tree(unsigned n, const unsigned* order, unsigned nil) {
    TreeNode* head=&records[0].node;
    for (unsigned i=0;i<8;++i) {
        TreeNode& p=records[i].node;
        p.left=p.parent=p.right=head;
        p.color=static_cast<uint8_t>(i*31+nil);
        p.is_nil=0;
        p.opaque[0]=0xa5; p.opaque[1]=static_cast<uint8_t>(i+7);
        for(unsigned j=0;j<3;++j) records[i].payload[j]=0xaabbcc00u+i*3+j;
    }
    head->is_nil=static_cast<uint8_t>(nil);
    for (unsigned i=0;i<n;++i) {
        unsigned key=order[i];
        TreeNode* p=&records[key].node;
        TreeNode* parent=head;
        TreeNode** link=&head->parent;
        while (*link!=head) {
            parent=*link;
            unsigned parentKey=static_cast<unsigned>(reinterpret_cast<Record*>(parent)-records);
            link=key<parentKey ? &parent->left : &parent->right;
        }
        p->parent=parent; *link=p;
    }
    head->left=n ? &records[1].node : head;
    head->right=n ? &records[n].node : head;
    if (!check(head,head)) return false;
    for(unsigned k=1;k<=n;++k)
        if(!check(&records[k].node,k<n ? &records[k+1].node : head)) return false;
    // Repeated traversal tests iterator state across successive calls.
    TreeIterator a={head->left}, b={head->left};
    for(unsigned i=0;i<n+2;++i) {
        if(original_tree_iterator_increment(&a)!=&a || &b.increment()!=&b ||
           a.node!=b.node || !unchanged() || test_get_fs_head()!=0x13572468u) return false;
    }
    return true;
}
static bool permutations(unsigned* a,unsigned depth,unsigned n,unsigned nil) {
    if(depth==n) return tree(n,a,nil);
    for(unsigned j=depth;j<n;++j) {
        unsigned t=a[depth];a[depth]=a[j];a[j]=t;
        if(!permutations(a,depth+1,n,nil)) return false;
        t=a[depth];a[depth]=a[j];a[j]=t;
    }
    return true;
}
extern "C" int test_main() {
    fs_storage[0]=0x13572468u;
    if(test_install_fs(fs_storage)!=0 || test_get_fs_head()!=fs_storage[0]) return 3;
    const unsigned flags[]={1,2,255};
    for(unsigned f=0;f<3;++f) {
        for(unsigned n=0;n<=7;++n) {
            unsigned order[7];for(unsigned i=0;i<n;++i) order[i]=i+1;
            if(!permutations(order,0,n,flags[f])) return 1;
        }
    }
    // A marked current node must not inspect any of its links.
    records[0].node.left=records[0].node.parent=records[0].node.right=0;
    records[0].node.is_nil=128;
    if(!check(&records[0].node,&records[0].node) || checks==0) return 2;
    test_write("PASS tree iterator successor\n",29);
    return 0;
}
