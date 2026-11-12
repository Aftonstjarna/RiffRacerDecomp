#include "impl.hpp"
extern "C" {
// sseregparm supplies dummy in XMM0 and value in XMM1; thiscall supplies
// self in ECX and callee-popped owner/descriptor/source on the stack.
void* __attribute__((thiscall,sseregparm)) original_body_construction_record_initialize(
    void* self, float dummy, float value, uint32_t owner, uint32_t descriptor, const void* source);
int test_install_fs(void*);
unsigned test_get_fs_head();
unsigned test_get_mxcsr();
void test_set_mxcsr(unsigned);
void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i = 0; i < n; ++i) { a[i] = b[i]; }
    return d;
}
void* memset(void* d, int c, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    for (unsigned i = 0; i < n; ++i) { a[i] = static_cast<unsigned char>(c); }
    return d;
}
}
struct Guarded { uint32_t before[4]; riff::BodyConstructionRecord body; uint32_t after[4]; };
static uint32_t bits(const void* p) { uint32_t v; memcpy(&v,p,4); return v; }
extern "C" int test_main() {
    uint32_t fs[8] = {0x13579bdf};
    if (test_install_fs(fs) != 0) return 1;
    const unsigned head = test_get_fs_head();
    const unsigned saved = test_get_mxcsr();
    const uint32_t values[] = {0,0x80000000u,0x3f800000u,0xbf800000u,1,0x007fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,0xffffffffu};
    for (unsigned mode = 0; mode < 16; ++mode) {
        const unsigned mxcsr = 0x1f80u | ((mode & 3) << 13) | ((mode & 4) ? 0x8000u : 0) | ((mode & 8) ? 0x40u : 0);
        test_set_mxcsr(mxcsr);
        for (unsigned v = 0; v < sizeof(values)/sizeof(values[0]); ++v) {
            for (int alias = -1; alias <= 0x78; ++alias) {
                Guarded a, b;
                unsigned char external[20];
                for (unsigned i = 0; i < sizeof(a); ++i) reinterpret_cast<unsigned char*>(&a)[i] = static_cast<unsigned char>(i*37+v*19+mode);
                memcpy(&b,&a,sizeof(a));
                for (unsigned i = 0; i < sizeof(external); ++i) external[i] = static_cast<unsigned char>(i*61+v);
                float scalar; memcpy(&scalar,&values[v],4);
                const uint32_t owner = values[v] ^ 0xa5a5a5a5u;
                const uint32_t descriptor = ~values[v];
                const void* sa = alias < 0 ? external+1 : reinterpret_cast<unsigned char*>(&a.body)+alias;
                const void* sb = alias < 0 ? external+1 : reinterpret_cast<unsigned char*>(&b.body)+alias;
                void* result = original_body_construction_record_initialize(&a.body,0.0f,scalar,owner,descriptor,sa);
                if (test_get_fs_head() != head) return 2;
                if (result != &a.body) return 3;
                if (b.body.initialize(scalar,owner,descriptor,sb) != &b.body) return 4;
                for (unsigned i = 0; i < sizeof(a); ++i)
                    if (reinterpret_cast<unsigned char*>(&a)[i] != reinterpret_cast<unsigned char*>(&b)[i]) return 5;
                if (test_get_mxcsr() != mxcsr) return 6;
                if (bits(&a.body.scalar) != values[v] || a.body.owner != owner || a.body.descriptor != descriptor) return 7;
                for (unsigned i = 0; i < 16; ++i)
                    if (bits(&a.body.basis[i]) != ((i==0 || i==5 || i==10) ? 0x3f800000u : 0)) return 8;
                const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&a);
                for (unsigned i = 0; i < sizeof(a); ++i) {
                    const unsigned start = offsetof(Guarded,body);
                    if (i < start || i >= start+sizeof(a.body) || (i >= start+0x75 && i < start+0x78))
                        if (bytes[i] != static_cast<unsigned char>(i*37+v*19+mode)) return 9;
                }
            }
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
