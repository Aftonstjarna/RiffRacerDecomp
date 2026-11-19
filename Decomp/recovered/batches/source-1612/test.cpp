#include "impl.hpp"
extern "C" void* __attribute__((thiscall)) original_mounted_archive_search(MountedArchives*, const char*, uint32_t*);
extern "C" void* __attribute__((thiscall)) original_archive_index_lookup(ArchiveIndex*, const char*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" { unsigned oracle_cookie __attribute__((section(".oracle_cookie"),used,aligned(4))) = 0x12345678; }
void* ArchiveIndex::lookup(const char* path) { return original_archive_index_lookup(this, path); }

struct Node { uint16_t name, next, child, flags; };
struct IndexFixture { Node* nodes; uint32_t pad4, pad8; unsigned char* results; uint32_t pad10, pad14; const char* names; uint32_t pad1c, pad20; Node root; };
static Node nodes0[2], nodes1[3];
static unsigned char results0[84], results1[84];
static const char names0[] = "first\0";
static const char names1[] = "folder\0file\0first\0";
static IndexFixture a, b;
static MountRecord mounts[2];
static MountedArchives manager;
static unsigned fs_storage[8];
static void init() {
    nodes0[0] = Node{0, 0xffff, 0xffff, 1};
    nodes1[0] = Node{0, 2, 1, 0};
    nodes1[1] = Node{7, 0xffff, 0xffff, 2};
    nodes1[2] = Node{12, 0xffff, 0xffff, 0};
    a.nodes=nodes0; a.results=results0; a.names=names0; a.root.child=0;
    b.nodes=nodes1; b.results=results1; b.names=names1; b.root.child=0;
    mounts[0].index=reinterpret_cast<ArchiveIndex*>(&a);
    mounts[1].index=reinterpret_cast<ArchiveIndex*>(&b);
    mounts[0].unknown0=0x1234; mounts[1].unknown16=0x5678;
    manager.begin=mounts; manager.end=mounts+2; manager.unknown[3]=0xa5;
}
static int check(const char* path, int count, void* expected, unsigned expected_index) {
    manager.end=mounts+count;
    unsigned x=0xdeadbeef, y=0xdeadbeef;
    void* p=original_mounted_archive_search(&manager,path,&x);
    if (test_get_fs_head()!=0x13572468) return 1;
    void* q=manager.search(path,&y);
    if (test_get_fs_head()!=0x13572468) return 2;
    if (p!=expected || q!=p || x!=expected_index || y!=x) return 3;
    if (manager.begin!=mounts || manager.end!=mounts+count || manager.unknown[3]!=0xa5 || mounts[0].unknown0!=0x1234 || mounts[1].unknown16!=0x5678 || a.root.child!=0 || b.root.child!=0) return 4;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13572468;
    if (test_install_fs(fs_storage)!=0 || test_get_fs_head()!=0x13572468) return 10;
    init();
    if (check("first",0,0,0)) return 11;
    if (check("first",2,results0+28,0)) return 12;
    if (check("folder\\file",2,results1+56,1)) return 13;
    if (check("first",1,results0+28,0)) return 14;
    if (check("folder",2,results1,1)) return 15;
    if (check("missing",2,0,0)) return 16;
    if (check("folder\\missing",2,0,0)) return 17;
    if (check("First",2,0,0)) return 18;
    if (check("",2,0,0)) return 19;
    return 0;
}
