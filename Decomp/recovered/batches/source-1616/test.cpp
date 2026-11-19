#include "impl.hpp"
extern "C" void* __attribute__((thiscall)) original_archive_index_lookup(ArchiveIndex*, const char*);
extern "C" ArchiveEntry* __attribute__((thiscall)) original_archive_component_lookup(ArchiveIndex*, const char*, const ArchiveEntry*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" { unsigned oracle_cookie __attribute__((section(".oracle_cookie"),used,aligned(4))) = 0x12345678; }
ArchiveEntry* ArchiveIndex::component(const char* s, const ArchiveEntry* p) { return original_archive_component_lookup(this,s,p); }
static ArchiveIndex index;
static ArchiveEntry entries[8];
static unsigned char records[28*8];
static char names[0x30010];
static unsigned fs[8];
static int same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return 0;
    return 1;
}
static int check(const char* path, void* expected) {
    ArchiveIndex before=index; ArchiveEntry nodes[8]; unsigned char data[sizeof(records)]; static char strings[sizeof(names)];
    for(unsigned i=0;i<8;++i) nodes[i]=entries[i];
    for(unsigned i=0;i<sizeof(records);++i) data[i]=records[i];
    for(unsigned i=0;i<sizeof(names);++i) strings[i]=names[i];
    void* a=original_archive_index_lookup(&index,path);
    if(test_get_fs_head()!=0x13572468) return 1;
    void* b=index.lookup(path);
    if(test_get_fs_head()!=0x13572468 || a!=expected || b!=a) return 2;
    if(!same(&index,&before,sizeof(index)) || !same(entries,nodes,sizeof(entries)) || !same(records,data,sizeof(records)) || !same(names,strings,sizeof(names))) return 3;
    return 0;
}
extern "C" int test_main() {
    fs[0]=0x13572468;
    if(test_install_fs(fs)!=0 || test_get_fs_head()!=0x13572468) return 1;
    const char text[]="dir\0file\0\0leaf\0dup\0";
    for(unsigned i=0;i<sizeof(text);++i) names[i]=text[i];
    for(unsigned i=0;i<4;++i) names[0x30000+i]=text[i];
    for(unsigned i=0;i<5;++i) names[0x20004+i]=text[4+i];
    index.entries=entries; index.records=records; index.names=names; index.root.first_child=0;
    index.unknown04[0]=0x12345678; index.unknown1c[1]=0x87654321;
    // Root: dir, empty, dup. dir: file, empty. Empty root: leaf.
    entries[0]=ArchiveEntry{0,2,1,0xc001};
    entries[1]=ArchiveEntry{4,4,0xffff,0x8002};
    entries[2]=ArchiveEntry{9,5,3,3};
    entries[3]=ArchiveEntry{10,0xffff,0xffff,4};
    entries[4]=ArchiveEntry{9,0xffff,0xffff,5};
    entries[5]=ArchiveEntry{15,6,0xffff,6};
    entries[6]=ArchiveEntry{15,0xffff,0xffff,7};
    if(check("dir",records+28) || check("dir\\file",records+56)) return 2;
    if(check("",records+84) || check("\\leaf",records+112) || check("dir\\",records+140)) return 3;
    if(check("dup",records+168) || check("missing",0) || check("dir\\missing",0)) return 4;
    if(check("Dir",0) || check("dir/file",0) || check("dir\\\\file",0) || check("\\",0)) return 5;
    index.root.first_child=0xffff;
    if(check("",0) || check("dir",0)) return 6;
    return 0;
}
