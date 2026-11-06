#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_device_clear_texture_cache(riff::Device*, uint32_t);
extern "C" void test_write(const char*, unsigned);
struct Fixture { riff::Device object; uint32_t tail[8]; };
struct Event { uint32_t stage, device_id, cache[16]; };
static riff::TextureDeviceVtable table;
static riff::TextureDevice devices[2];
static Fixture a, b;
static Fixture* active;
static Event events[16], saved[16];
static unsigned count, saved_count, mode, failures;
static int32_t RIFF_STDCALL callback(riff::TextureDevice* dev, uint32_t stage, void* texture) {
    if (texture || stage >= 16 || count >= 16) { ++failures; return -1; }
    Event& e = events[count++];
    e.stage = stage;
    e.device_id = dev == &devices[0] ? 0 : dev == &devices[1] ? 1 : 99;
    for (unsigned i=0;i<16;++i) e.cache[i]=active->object.texture_cache[i];
    if (mode && stage == 0) {
        active->object.device = &devices[1];
        active->object.texture_cache[0] = 0x5555; // Must be cleared after return.
        active->object.texture_cache[1] = 0; // Must suppress future call.
        active->object.texture_cache[15] = 0x8888; // Must enable future call.
    }
    if (mode && stage == 15) active->object.texture_cache[0] = 0x1234; // No revisit.
    return (stage & 1) ? -1 : 0; // HRESULT is ignored, including failure.
}
static void run(uint32_t mask, unsigned mutation, uint32_t argument) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&a);
    for (unsigned i=0;i<sizeof(a);++i) p[i]=static_cast<unsigned char>(i*37+19);
    a.object.device = mask ? &devices[0] : 0; // Empty cache needs no device.
    for (unsigned i=0;i<16;++i) a.object.texture_cache[i]=(mask & (1u<<i)) ? (i&1 ? 0xffffffffu : 0x80000000u) : 0;
    b=a;
    mode=mutation; active=&a; count=0;
    original_device_clear_texture_cache(&a.object, argument);
    saved_count=count;
    for (unsigned i=0;i<count;++i) saved[i]=events[i];
    active=&b; count=0;
    b.object.clear_texture_cache(argument);
    if (count != saved_count) ++failures;
    for (unsigned i=0;i<count && i<saved_count;++i) {
        if (events[i].stage!=saved[i].stage || events[i].device_id!=saved[i].device_id) ++failures;
        for (unsigned j=0;j<16;++j) if(events[i].cache[j]!=saved[i].cache[j]) ++failures;
    }
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) ++failures;
    // Independently assert the normal contract and all untouched bytes.
    for(unsigned i=0;i<sizeof(a);++i) {
        if(i>=0x78 && i<0x7c) continue;
        if(i>=0x9ec && i<0xa2c) continue;
        if(x[i]!=static_cast<unsigned char>(i*37+19)) ++failures;
    }
    for(unsigned i=0;i<16;++i) {
        uint32_t expected = mutation && i==0 ? 0x1234 : 0;
        if(a.object.texture_cache[i]!=expected) ++failures;
    }
    if(!mutation) {
        unsigned n=0;
        for(unsigned i=0;i<16;++i) if(mask & (1u<<i)) {
            if(saved[n].stage!=i || saved[n].device_id!=0) ++failures;
            ++n;
        }
        if(n!=saved_count) ++failures;
    } else if(saved_count!=2 || saved[0].stage!=0 || saved[1].stage!=15 || saved[1].device_id!=1) ++failures;
}
extern "C" int test_main() {
    table.slots[65]=callback;
    devices[0].vtable=&table; devices[1].vtable=&table;
    run(0,0,0); run(0xffff,0,0xffffffffu);
    run(0xaaaa,0,42); run(0x5555,0,0);
    for(unsigned i=0;i<16;++i) run(1u<<i,0,i);
    run(3,1,0xdeadbeef);
    // A second clear of an already cleared cache makes no calls.
    active=&b; mode=0; count=0;
    b.object.texture_cache[0]=0;
    b.object.clear_texture_cache(0);
    if(count) ++failures;
    if(failures) { test_write("FAIL\n",5); return 1; }
    test_write("PASS\n",5); return 0;
}
extern "C" void* memcpy(void* destination, const void* source, size_t length) {
    unsigned char* d=static_cast<unsigned char*>(destination);
    const unsigned char* s=static_cast<const unsigned char*>(source);
    for(size_t i=0;i<length;++i) d[i]=s[i];
    return destination;
}
