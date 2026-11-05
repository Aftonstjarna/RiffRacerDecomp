#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_graphics_entry_release(riff::GraphicsEntry*, bool);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
using namespace riff;
struct Block {
    ReferenceBase early;
    uint32_t guard;
    ResourcePrefix prefix;
    ReferenceBase late;
    uint32_t tail;
};
struct Fixture {
    uint32_t before;
    GraphicsEntry entry;
    Block block;
    uint32_t after;
    uint32_t calls, flags, baseOffset, observedCount, observedPointer, mode;
};
static Fixture f;
static int32_t offsets[2];
static void* __attribute__((thiscall)) destroy(ReferenceBase* base, uint32_t flags) {
    ++f.calls;
    f.flags=flags;
    f.baseOffset=uint32_t(reinterpret_cast<char*>(base)-reinterpret_cast<char*>(&f.block));
    f.observedCount=base->references;
    f.observedPointer=f.entry.resource==&f.block.prefix;
    if(f.mode==1) f.entry.resource=0;
    if(f.mode==2) f.entry.resource=&f.block.prefix;
    if(f.mode==3) { f.entry.ownership=0x12345678; f.entry.unknown=0x87654321; }
    return base;
}
static ReferenceVtable vtable={destroy};
static void init(uint32_t count,uint32_t owner,bool absent,bool negative,unsigned mode) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof(f);++i) p[i]=0;
    f.before=0xabcddcba; f.after=0x13572468;
    f.entry.ownership=owner; f.entry.unknown=0xfeedbeef;
    f.entry.resource=absent?0:&f.block.prefix;
    f.block.early.vtable=&vtable; f.block.early.references=negative?count:0xa5a5a5a5;
    f.block.guard=0xdeadbeef;
    f.block.prefix.unknown=0xface1234; f.block.prefix.virtualBaseOffsets=offsets;
    f.block.late.vtable=&vtable; f.block.late.references=negative?0xa5a5a5a5:count;
    f.block.tail=0x31415926; f.mode=mode;
    offsets[0]=0x76543210; offsets[1]=negative?-16:4;
}
extern "C" int test_main() {
    static uint32_t fs[8]; fs[0]=0xffffffffU;
    if(test_install_fs(fs)!=0) return 1;
    const uint32_t counts[]={0,1,2,3,17,257,0x80000000U,0xffffffffU};
    const uint32_t owners[]={0,1,2,0xffffffffU};
    unsigned char saved[sizeof(f)];
    for(unsigned c=0;c<8;++c) for(unsigned o=0;o<4;++o)
    for(unsigned force=0;force<2;++force) for(unsigned absent=0;absent<2;++absent)
    for(unsigned negative=0;negative<2;++negative) for(unsigned mode=0;mode<4;++mode) {
        uint32_t count=counts[c],owner=owners[o];
        // Huge forced counts require billions of iterations; ordinary release
        // still exercises their unsigned arithmetic without a synthetic shortcut.
        if(force && count>257 && !absent) continue;
        init(count,owner,absent!=0,negative!=0,mode);
        bool actual=original_graphics_entry_release(&f.entry,force!=0);
        if(test_get_fs_head()!=0xffffffffU) return 2;
        bool released=absent || owner==0 || force;
        bool touched=!absent && released;
        uint32_t expectedCount=touched?(force && count>0?0:count-1):count;
        ReferenceBase& base=negative?f.block.early:f.block.late;
        if(actual!=released || base.references!=expectedCount) return 3;
        unsigned expectedCalls=touched && count!=0 && (force || count==1)?1:0;
        if(f.calls!=expectedCalls) return 4;
        if(f.calls && (f.flags!=1 || f.observedCount!=0 || !f.observedPointer || f.baseOffset!=(negative?0U:20U))) return 5;
        if(f.entry.resource!=(released?0:&f.block.prefix)) return 6;
        if(f.before!=0xabcddcba || f.after!=0x13572468 || f.block.guard!=0xdeadbeef || f.block.tail!=0x31415926) return 7;
        if(f.entry.ownership!=(f.calls && mode==3?0x12345678U:owner) || f.entry.unknown!=(f.calls && mode==3?0x87654321U:0xfeedbeefU)) return 8;
        const unsigned char* p=reinterpret_cast<const unsigned char*>(&f);
        for(unsigned i=0;i<sizeof(f);++i) saved[i]=p[i];
        init(count,owner,absent!=0,negative!=0,mode);
        bool recovered=f.entry.release(force!=0);
        if(recovered!=actual) return 9;
        p=reinterpret_cast<const unsigned char*>(&f);
        for(unsigned i=0;i<sizeof(f);++i) if(saved[i]!=p[i]) return 10;
    }
    return 0;
}
