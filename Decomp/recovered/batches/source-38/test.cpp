#include "impl.hpp"
using recovered::SaveDevice;
extern "C" void __attribute__((thiscall)) original_save_device_destruct(SaveDevice*);
extern "C" void test_write(const char*,unsigned);
static SaveDevice* active;
struct Event { uintptr_t pointer; SaveDevice state; };
static Event events[2];
static unsigned count;
static void copy(void* dst,const void* src,unsigned n) {
    auto d=static_cast<unsigned char*>(dst); auto s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    auto x=static_cast<const unsigned char*>(a); auto y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void release(void* p) {
    if(count<2) { events[count].pointer=reinterpret_cast<uintptr_t>(p); copy(&events[count].state,active,sizeof(*active)); }
    ++count;
}
// Test-only binding of the original Windows import slot. Observes calls without
// dereferencing/freeing synthetic pointers, so null and alias cases are testable.
extern "C" {
__attribute__((section(".oracle_iat"),used)) recovered::DeleteStorage oracle_delete = release;
}
static void set_pointer(unsigned char* s,uint32_t p) {
    for(unsigned i=0;i<4;++i) s[i]=static_cast<unsigned char>(p>>(8*i));
}
static void expected_clear(recovered::WideStringStorage& s) {
    s.capacity=7; s.length=0; s.storage[0]=s.storage[1]=0;
}
struct Guarded { unsigned char before[16]; SaveDevice object; unsigned char after[16]; };
extern "C" int test_main() {
    const uint32_t caps[]={0,1,7,8,9,0x7fffffff,0x80000000,0xffffffff};
    for(unsigned a=0;a<8;++a) for(unsigned b=0;b<8;++b) for(unsigned variant=0;variant<3;++variant) {
        Guarded initial, original, candidate, expected;
        auto bytes=reinterpret_cast<unsigned char*>(&initial);
        for(unsigned i=0;i<sizeof(initial);++i) bytes[i]=static_cast<unsigned char>(i*37+variant*53);
        initial.object.first.capacity=caps[a]; initial.object.second.capacity=caps[b];
        initial.object.first.length= variant==0?0:0xffffffff;
        initial.object.second.length= variant==1?7:0x80000000;
        uint32_t p1=variant==0?0:0x12345678;
        uint32_t p2=variant==2?p1:0x87654321;
        set_pointer(initial.object.first.storage,p1); set_pointer(initial.object.second.storage,p2);
        copy(&original,&initial,sizeof(initial)); copy(&candidate,&initial,sizeof(initial)); copy(&expected,&initial,sizeof(initial));
        active=&original.object; count=0; original_save_device_destruct(active);
        Event saved[2]; unsigned original_count=count; copy(saved,events,sizeof(saved));
        active=&candidate.object; count=0; recovered::save_device_destruct(active,release);
        if(count!=original_count || !equal(&original,&candidate,sizeof(original))) return 1;
        for(unsigned i=0;i<count;++i) if(!equal(&saved[i],&events[i],sizeof(Event))) return 2;
        // Independent assertions for call order and intermediate object state.
        expected.object.primary_vtable=0x9ffe2c; expected.object.secondary_vtable=0x9ffe6c;
        unsigned index=0;
        if(caps[b]>=8) {
            if(saved[index].pointer!=p2 || !equal(&saved[index].state,&expected.object,sizeof(SaveDevice))) return 3;
            ++index;
        }
        expected_clear(expected.object.second);
        if(caps[a]>=8) {
            if(saved[index].pointer!=p1 || !equal(&saved[index].state,&expected.object,sizeof(SaveDevice))) return 4;
            ++index;
        }
        expected_clear(expected.object.first); expected.object.primary_vtable=0x9f99d8;
        if(index!=count || !equal(&candidate,&expected,sizeof(expected))) return 5;
    }
    test_write("192 destructor cases passed\n",28);
    return 0;
}
