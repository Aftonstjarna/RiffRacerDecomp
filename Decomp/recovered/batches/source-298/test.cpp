#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((thiscall)) original_buffer_release(Buffer*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(Buffer)==28, "original x86 layout");
static_assert(offsetof(Buffer,state)==12, "state offset");
static_assert(offsetof(ReleaseVtable,release)==8, "COM slot");
struct Object { ReleaseInterface iface; unsigned id, calls, guard; };
struct Guarded { unsigned before[2]; Buffer buffer; unsigned after[2]; };
struct Event { unsigned id; uintptr_t fields[7]; };
static Object objects[4];
static Guarded fixture;
static Event events[8], expected[8];
static unsigned count, mode;
static uint32_t fs_storage[8];
static void snapshot(Event& e, unsigned id) {
    e.id=id;
    e.fields[0]=reinterpret_cast<uintptr_t>(fixture.buffer.first);
    e.fields[1]=reinterpret_cast<uintptr_t>(fixture.buffer.second);
    e.fields[2]=reinterpret_cast<uintptr_t>(fixture.buffer.third);
    for(unsigned i=0;i<4;++i) e.fields[3+i]=fixture.buffer.state[i];
}
static uint32_t RIFF_STDCALL release_callback(ReleaseInterface* p) {
    Object* obj=reinterpret_cast<Object*>(p);
    if(count>=8) return 0;
    snapshot(events[count],obj->id);
    ++count; ++obj->calls;
    if(count==1 && mode && fixture.buffer.third) {
        // Deliberate mutation verifies that later pointers are loaded after
        // the preceding callback, and final stores override callback writes.
        fixture.buffer.first=&objects[3].iface;
        fixture.buffer.second=mode==1 ? &objects[3].iface : 0;
        fixture.buffer.third=&objects[3].iface;
        for(unsigned i=0;i<4;++i) fixture.buffer.state[i]=0xfedcba98u+i;
    }
    return 0x87654321u; // ignored by both implementations
}
static const ReleaseVtable table={0,0,release_callback};
static void setup(unsigned mask, bool alias) {
    count=0;
    for(unsigned i=0;i<4;++i) {
        objects[i].iface.vtable=&table; objects[i].id=i;
        objects[i].calls=0; objects[i].guard=0xdecafbad;
    }
    fixture.before[0]=0x12345678; fixture.before[1]=0xffffffff;
    fixture.after[0]=0x87654321; fixture.after[1]=0x80000000;
    fixture.buffer.first=(mask&1)?&objects[0].iface:0;
    fixture.buffer.second=(mask&2)?&objects[alias?0:1].iface:0;
    fixture.buffer.third=(mask&4)?&objects[alias?0:2].iface:0;
    for(unsigned i=0;i<4;++i) fixture.buffer.state[i]=0x80000000u+i*0x1234567u;
}
static bool cleared() {
    if(fixture.buffer.first || fixture.buffer.second || fixture.buffer.third) return false;
    for(unsigned i=0;i<4;++i) if(fixture.buffer.state[i]) return false;
    if(fixture.before[0]!=0x12345678 || fixture.before[1]!=0xffffffff ||
       fixture.after[0]!=0x87654321 || fixture.after[1]!=0x80000000) return false;
    for(unsigned i=0;i<4;++i)
        if(objects[i].guard!=0xdecafbad || objects[i].iface.vtable!=&table || objects[i].id!=i) return false;
    return true;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdf;
    if(test_install_fs(fs_storage)!=0) return 1;
    for(mode=0;mode<3;++mode) for(unsigned alias=0;alias<2;++alias)
    for(unsigned mask=0;mask<8;++mask) {
        setup(mask,alias!=0);
        original_buffer_release(&fixture.buffer);
        if(test_get_fs_head()!=fs_storage[0] || !cleared()) return 2;
        unsigned expected_count=count, calls[4];
        for(unsigned i=0;i<count;++i) expected[i]=events[i];
        for(unsigned i=0;i<4;++i) calls[i]=objects[i].calls;
        // Also assert ordinary semantics independently of differential checks.
        if(mode==0) {
            unsigned n=0;
            for(int i=2;i>=0;--i) if(mask&(1u<<i)) {
                if(events[n++].id!=(alias?0u:static_cast<unsigned>(i))) return 3;
            }
            if(count!=n) return 4;
        }
        original_buffer_release(&fixture.buffer);
        if(test_get_fs_head()!=fs_storage[0] || count!=expected_count || !cleared()) return 5;
        setup(mask,alias!=0);
        fixture.buffer.release();
        if(!cleared() || count!=expected_count) return 6;
        for(unsigned i=0;i<count;++i) {
            if(events[i].id!=expected[i].id) return 7;
            for(unsigned j=0;j<7;++j) if(events[i].fields[j]!=expected[i].fields[j]) return 8;
        }
        for(unsigned i=0;i<4;++i) if(objects[i].calls!=calls[i]) return 9;
        fixture.buffer.release();
        if(count!=expected_count || !cleared()) return 10;
    }
    static const char message[]="buffer-release: 48 differential cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
