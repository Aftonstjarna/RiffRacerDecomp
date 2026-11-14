#include "impl.hpp"
using riff::Record12;
// This is NOT stdcall or thiscall: the original pops no stack arguments.
// GCC regparm(3) supplies EAX (ignored), EDX=last, ECX=first, then
// destination on the stack, with caller cleanup. The ignored EAX input is
// safe: the original never reads entry EAX. No machine-code wrapper needed.
extern "C" Record12* __attribute__((regparm(3)))
original_record12_range_copy_construct(unsigned ignored_eax,
    const Record12* last, const Record12* first, Record12* destination);
static Record12* oracle(const Record12* first, const Record12* last, Record12* dst) {
    return original_record12_range_copy_construct(0, last, first, dst);
}
static void fill(Record12* p, unsigned n) {
    for (unsigned i=0; i<n; ++i)
        for (unsigned j=0; j<3; ++j)
            p[i].words[j] = 0xa5000000u ^ (i*0x1234567u) ^ (j*0x9abcdefu);
}
static bool same(const Record12* a, const Record12* b, unsigned n) {
    for (unsigned i=0; i<n; ++i)
        for (unsigned j=0; j<3; ++j)
            if (a[i].words[j] != b[i].words[j]) return false;
    return true;
}
extern "C" int test_main() {
    Record12 source[12], saved[12], a[16], b[16];
    fill(source,12); fill(saved,12);
    for (unsigned n=0; n<=12; ++n) {
        fill(a,16); fill(b,16);
        if (oracle(source,source+n,a+2) != a+2+n) return 1;
        if (riff::record12_range_copy_construct(source,source+n,b+2) != b+2+n) return 2;
        if (!same(a,b,16) || !same(source,saved,12)) return 3;
        for (unsigned i=0;i<16;++i) {
            const Record12* expected = (i>=2 && i<2+n) ? source+i-2 : 0;
            for (unsigned j=0;j<3;++j) {
                uint32_t value = expected ? expected->words[j] :
                    (0xa5000000u ^ (i*0x1234567u) ^ (j*0x9abcdefu));
                if (a[i].words[j]!=value) return 4;
            }
        }
    }
    // Exact alias, forward propagation, and backward overlap. Compare entire
    // buffers so untouched prefix/suffix and all three fields are checked.
    for (unsigned src=1;src<=3;++src) for (unsigned dst=1;dst<=3;++dst) {
        fill(a,16); fill(b,16);
        if (oracle(a+src,a+src+8,a+dst)!=a+dst+8) return 5;
        if (riff::record12_range_copy_construct(b+src,b+src+8,b+dst)!=b+dst+8) return 6;
        if (!same(a,b,16)) return 7;
    }
    if (oracle(0,0,0)!=0 || riff::record12_range_copy_construct(0,0,0)!=0) return 8;
    // A single null destination skips ALL source loads. The source address
    // is deliberately unreadable; iteration two would try to write at 12.
    const Record12* bad = reinterpret_cast<const Record12*>(0x1000u);
    const Record12* end = reinterpret_cast<const Record12*>(0x100cu);
    if (reinterpret_cast<uintptr_t>(oracle(bad,end,0))!=12) return 9;
    if (reinterpret_cast<uintptr_t>(riff::record12_range_copy_construct(bad,end,0))!=12) return 10;
    return 0;
}
