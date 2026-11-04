#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_narrow_destroy(riff::NarrowString*);
extern "C" void test_write(const char*, unsigned);
namespace riff { ScalarDelete scalar_delete; }
extern "C" {
riff::ScalarDelete delete_iat __attribute__((section(".delete_iat"),used,aligned(4)));
}
static unsigned calls, bad;
static void* expected_pointer;
static riff::NarrowString* active;
static unsigned char before[24];
static unsigned char heap_data[64];
static void RIFF_CDECL audited_delete(void* p) {
    ++calls;
    if (p != expected_pointer) ++bad;
    // Verify no object write precedes the callback; simulate a visible release
    // side effect without using an allocator or dereferencing invalid pointers.
    const unsigned char* a = reinterpret_cast<const unsigned char*>(active);
    for (unsigned i=0;i<24;++i) if (a[i]!=before[i]) ++bad;
    heap_data[7] ^= 0x5a;
}
static void copy_bytes(void* d,const void* s,unsigned n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    const unsigned char* b=static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i) a[i]=b[i];
}
struct Guarded { uint32_t pre[2]; riff::NarrowString value; uint32_t post[2]; };
static int run(uint32_t capacity,uint32_t length,unsigned seed,unsigned pointer_kind) {
    Guarded a,b;
    unsigned char* bytes=reinterpret_cast<unsigned char*>(&a);
    for(unsigned i=0;i<sizeof(a);++i) bytes[i]=static_cast<unsigned char>(seed+37*i);
    a.value.capacity=capacity; a.value.length=length;
    if(capacity>=16u) a.value.storage.heap=pointer_kind ? static_cast<void*>(heap_data) : 0;
    copy_bytes(&b,&a,sizeof(a));
    unsigned char expected[sizeof(a)]; copy_bytes(expected,&a,sizeof(a));
    const unsigned offset=offsetof(Guarded,value);
    expected[offset]=0;
    for(unsigned i=0;i<4;++i) { expected[offset+16+i]=0; expected[offset+20+i]=i==0?15:0; }
    unsigned original_calls=0;
    for(unsigned pass=0;pass<2;++pass) {
        active=pass?&b.value:&a.value;
        copy_bytes(before,active,24);
        expected_pointer=capacity>=16u ? active->storage.heap : 0;
        calls=0; bad=0; heap_data[7]=0xa7;
        if(pass) active->destroy(); else original_narrow_destroy(active);
        if(bad || calls!=(capacity>=16u?1u:0u)) return 1;
        if(heap_data[7] != (capacity>=16u?(0xa7^0x5a):0xa7)) return 2;
        const unsigned char* got=reinterpret_cast<const unsigned char*>(pass?&b:&a);
        for(unsigned i=0;i<sizeof(a);++i) if(got[i]!=expected[i]) return 3;
        if(pass && calls!=original_calls) return 4;
        original_calls=calls;
        // Cleanup is idempotent after reset: no second release.
        calls=0;
        if(pass) active->destroy(); else original_narrow_destroy(active);
        if(calls) return 5;
        for(unsigned i=0;i<sizeof(a);++i) if(got[i]!=expected[i]) return 6;
    }
    return 0;
}
extern "C" int test_main() {
    delete_iat=&audited_delete; riff::scalar_delete=&audited_delete;
    const uint32_t caps[]={0,1,14,15,16,17,31,255,0x7fffffffU,0x80000000U,0xffffffffU};
    const uint32_t lengths[]={0,1,15,16,0x80000000U,0xffffffffU};
    for(unsigned c=0;c<11;++c) for(unsigned l=0;l<6;++l)
        for(unsigned p=0;p<2;++p) for(unsigned s=0;s<3;++s) {
            int result=run(caps[c],lengths[l],s*91,p);
            if(result) return result;
        }
    test_write("396 differential cases passed\n",30);
    return 0;
}
