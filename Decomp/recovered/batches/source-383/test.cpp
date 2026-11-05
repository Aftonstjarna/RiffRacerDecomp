#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((thiscall)) original_shader_grid_notify_slot12(ShaderGrid*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(void*) == 4, "oracle requires i386");
static_assert(offsetof(ShaderGrid, entries) == 0xe1c, "grid offset");
static_assert(sizeof(((ShaderGrid*)0)->entries[0]) == 0x460, "row stride");
struct Entry { ShaderEntry base; unsigned id, calls, guard; };
struct Fixture { unsigned before[4]; ShaderGrid grid; unsigned after[4]; };
static Fixture fixture;
static Entry objects[8];
static unsigned logIds[1800], logCount, mode;
static unsigned savedLog[1800], savedCount;
static unsigned char savedFixture[sizeof(Fixture)], savedObjects[sizeof(objects)];
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i) a[i]=b[i];
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void __attribute__((thiscall)) callback(ShaderEntry* base) {
    Entry* e=reinterpret_cast<Entry*>(base);
    if(logCount<1800) logIds[logCount]=e->id;
    ++logCount; ++e->calls;
    if(mode==4 && logCount==1) {
        fixture.grid.entries[1][0]=&objects[6].base;
        fixture.grid.entries[5][279]=0;
        fixture.grid.entries[0][1]=&objects[7].base;
        fixture.grid.entries[0][0]=0;
    }
}
static const ShaderEntryVtable table={{0,0,0},callback};
static void setup(unsigned m) {
    mode=m; logCount=0;
    unsigned char* p=reinterpret_cast<unsigned char*>(&fixture);
    for(unsigned i=0;i<sizeof(fixture);++i) p[i]=static_cast<unsigned char>(i*37+19);
    for(unsigned i=0;i<8;++i) {
        objects[i].base.vtable=&table; objects[i].id=i;
        objects[i].calls=0; objects[i].guard=0xaabbee00+i;
    }
    for(unsigned r=0;r<6;++r) for(unsigned c=0;c<280;++c) {
        ShaderEntry* e=0;
        if(m==2) e=&objects[(r*3+c)%8].base;
        if(m==3 && ((r+c)%13==0)) e=&objects[2].base;
        fixture.grid.entries[r][c]=e;
    }
    if(m==1 || m==4) {
        fixture.grid.entries[0][0]=&objects[0].base;
        fixture.grid.entries[5][0]=&objects[1].base;
        fixture.grid.entries[0][279]=&objects[2].base;
        fixture.grid.entries[5][279]=&objects[3].base;
    }
}
extern "C" int test_main() {
    for(unsigned m=0;m<5;++m) {
        setup(m);
        copy(savedFixture,&fixture,sizeof(fixture));
        original_shader_grid_notify_slot12(&fixture.grid);
        // Neither traversal nor controlled callbacks touch prefix/canaries.
        if(!equal(savedFixture,&fixture,offsetof(Fixture,grid)+0xe1c)) return 1;
        if(!equal(savedFixture+offsetof(Fixture,after),fixture.after,sizeof(fixture.after))) return 2;
        if(m!=4 && !equal(savedFixture,&fixture,sizeof(fixture))) return 3;
        unsigned expected=m==0?0:m==1?4:m==2?1680:m==4?5:0;
        if(m==3) for(unsigned r=0;r<6;++r) for(unsigned c=0;c<280;++c) if((r+c)%13==0) ++expected;
        if(logCount!=expected) return 4;
        savedCount=logCount;
        copy(savedLog,logIds,logCount*sizeof(unsigned));
        copy(savedFixture,&fixture,sizeof(fixture));
        copy(savedObjects,objects,sizeof(objects));
        setup(m);
        fixture.grid.notifySlot12();
        if(logCount!=savedCount || !equal(logIds,savedLog,logCount*sizeof(unsigned))) return 5;
        if(!equal(&fixture,savedFixture,sizeof(fixture))) return 6;
        if(!equal(objects,savedObjects,sizeof(objects))) return 7;
    }
    test_write("grid notify tests passed\n",25);
    return 0;
}
