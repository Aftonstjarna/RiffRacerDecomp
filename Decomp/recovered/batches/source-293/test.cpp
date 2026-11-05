#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_graphics_entry_release_all(riff::GraphicsEntries*, uint32_t);
extern "C" bool __attribute__((thiscall)) original_graphics_entry_release(riff::GraphicsEntry*, bool);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
namespace riff {
bool RIFF_THISCALL GraphicsEntry::release(bool force) {
    return original_graphics_entry_release(this, force);
}
RIFF_NORETURN void graphicsEntryRangeError() { __builtin_trap(); }
}
struct Resource { uint32_t tag; int32_t* vbtable; void** vtable; uint32_t refs; uint32_t tail; };
struct Fixture {
    uint32_t before;
    riff::GraphicsEntries table;
    uint32_t tableTail;
    riff::GraphicsEntry a[8], b[8];
    Resource resources[16];
    uint32_t calls, ids[16], flags[16], mode;
    uint32_t after;
};
static Fixture f;
static int32_t vbtable[2] = {0,4};
static void* vtable[1];
static void* __attribute__((thiscall)) destroy(void* base, uint32_t flag) {
    Resource* r = reinterpret_cast<Resource*>(reinterpret_cast<char*>(base)-8);
    unsigned i=f.calls++;
    f.ids[i]=r->tag; f.flags[i]=flag;
    if(i==0 && f.mode==1) f.table.end=f.table.begin+8;
    if(i==0 && f.mode==2) { f.table.begin=f.b; f.table.end=f.b+8; }
    if(i==0 && f.mode==3) f.table.end=f.table.begin+4;
    return base;
}
static void init(unsigned n,unsigned pattern,unsigned mode) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof(f);++i) p[i]=0;
    f.before=0x12345678; f.after=0xabcdef98; f.tableTail=0x87654321;
    f.table.begin=f.a; f.table.end=f.a+n; f.table.capacity=f.a+8; f.mode=mode;
    for(unsigned i=0;i<16;++i) {
        Resource& r=f.resources[i]; r.tag=i; r.vbtable=vbtable; r.vtable=vtable;
        r.refs=1+(i+pattern)%5; r.tail=0xbad01234;
        riff::GraphicsEntry& e=i<8?f.a[i]:f.b[i-8];
        e.ownership=(i+pattern)%3; e.unknown=0xfeed0000+i;
        e.resource=((pattern==1 && i%2==0)||pattern==2)?0:&r;
    }
}
extern "C" int test_main() {
    static uint32_t fs[8]; fs[0]=0xffffffffU;
    if(test_install_fs(fs)!=0) return 1;
    vtable[0]=reinterpret_cast<void*>(&destroy);
    unsigned char saved[sizeof(Fixture)];
    for(unsigned n=0;n<=8;++n) for(unsigned pattern=0;pattern<3;++pattern)
    for(unsigned mode=0;mode<4;++mode) {
        if(mode==3 && n>4) continue;
        init(n,pattern,mode);
        original_graphics_entry_release_all(&f.table,0xdeadbeef);
        if(test_get_fs_head()!=0xffffffffU) return 2;
        const unsigned char* p=reinterpret_cast<const unsigned char*>(&f);
        for(unsigned i=0;i<sizeof(f);++i) saved[i]=p[i];
        // Independent basic assertions complement full differential snapshots.
        if(f.before!=0x12345678 || f.after!=0xabcdef98 || f.tableTail!=0x87654321) return 3;
        for(unsigned i=0;i<f.calls;++i) if(f.flags[i]!=1) return 4;
        for(unsigned i=0;i<n;++i) {
            riff::GraphicsEntry& e=(mode==2 && i>0 && pattern!=2)?f.b[i]:f.a[i];
            // Relocation happens only when some resource was destroyed.
            if(mode!=2 && e.resource) return 5;
        }
        init(n,pattern,mode);
        f.table.releaseAll(0x12345678);
        if(test_get_fs_head()!=0xffffffffU) return 6;
        p=reinterpret_cast<const unsigned char*>(&f);
        for(unsigned i=0;i<sizeof(f);++i) if(saved[i]!=p[i]) return 7;
    }
    // Nonmultiples below one entry also truncate to zero without access.
    for(unsigned bytes=0;bytes<12;++bytes) {
        init(0,0,0);
        f.table.end=reinterpret_cast<riff::GraphicsEntry*>(reinterpret_cast<uintptr_t>(f.a)+bytes);
        original_graphics_entry_release_all(&f.table,0);
        if(test_get_fs_head()!=0xffffffffU || f.calls) return 8;
        f.table.releaseAll(1);
        if(f.calls) return 9;
    }
    return 0;
}
