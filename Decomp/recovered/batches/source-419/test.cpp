#include "impl.hpp"
// GCC regparm(3) maps dummy->EAX, end->EDX, begin->ECX, destination->stack,
// with caller cleanup. This adapter models the custom internal ABI exactly;
// fastcall would incorrectly pop destination. EAX input is unused.
extern "C" void* __attribute__((regparm(3))) original_record16_range_copy(
    unsigned unused, const void* end, const void* begin, void* destination);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned fs_storage[8];
static unsigned char a[256], b[256];
static void initialize() {
    for (unsigned i=0;i<256;++i) a[i]=b[i]=static_cast<unsigned char>(i*73+19);
}
static bool same() {
    for (unsigned i=0;i<256;++i) if (a[i]!=b[i]) return false;
    return true;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdf;
    if(test_install_fs(fs_storage)!=0) return 1;
    // All byte alignments, disjoint copies, identity, and overlaps in both
    // directions, including overlaps within a single four-byte field.
    for(unsigned count=0;count<=6;++count) {
        for(unsigned source=32;source<40;++source) {
            for(unsigned dest=16;dest<=144;++dest) {
                initialize();
                void* expected=original_record16_range_copy(0,a+source+16*count,a+source,a+dest);
                if(test_get_fs_head()!=fs_storage[0]) return 2;
                void* actual=record16_range_copy(b+source,b+source+16*count,b+dest);
                if(reinterpret_cast<uintptr_t>(expected)-reinterpret_cast<uintptr_t>(a) != dest+16*count) return 3;
                if(reinterpret_cast<uintptr_t>(actual)-reinterpret_cast<uintptr_t>(b) != dest+16*count) return 4;
                if(!same()) return 5; // Includes all source and guard bytes.
            }
        }
    }
    // Empty ranges never dereference source or destination, even invalid ones.
    for(unsigned i=0;i<3;++i) {
        const void* source=reinterpret_cast<void*>(uintptr_t(i));
        void* dest=reinterpret_cast<void*>(uintptr_t(i*17));
        if(original_record16_range_copy(0,source,source,dest)!=dest) return 6;
        if(test_get_fs_head()!=fs_storage[0]) return 7;
        if(record16_range_copy(source,source,dest)!=dest) return 8;
    }
    // Single null-output iteration performs no source read, even at address 1.
    void* end=reinterpret_cast<void*>(uintptr_t(17));
    void* begin=reinterpret_cast<void*>(uintptr_t(1));
    if(original_record16_range_copy(0,end,begin,0)!=reinterpret_cast<void*>(uintptr_t(16))) return 9;
    if(test_get_fs_head()!=fs_storage[0]) return 10;
    if(record16_range_copy(begin,end,0)!=reinterpret_cast<void*>(uintptr_t(16))) return 11;
    test_write("record16 tests passed\n",21);
    return 0;
}
