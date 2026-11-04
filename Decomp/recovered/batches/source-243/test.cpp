#include "impl.hpp"
extern "C" recovered::SaveDevice* __attribute__((thiscall)) original_save_device_ctor(recovered::SaveDevice*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
// Exact audited fixture, VA 0xBFCB40; the pointer slot is its fourth word.
uint32_t oracle_globals[8] __attribute__((section(".oracle_globals"),used,aligned(4)));
struct Guarded { uint32_t before[4]; recovered::SaveDevice object; uint32_t after[4]; };
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0;i<n;++i) b[i]=static_cast<unsigned char>(seed);
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    uint32_t fs_storage[4]={0x12345678,0,0,0};
    if(test_install_fs(fs_storage)!=0) return 1;
    Guarded original, candidate, expected;
    // Every repeated-byte poison, including zero and FF; repeated construction
    // also verifies publication overwrites an existing active object.
    for(unsigned seed=0;seed<256;++seed) {
        fill(&original,sizeof(original),seed);
        fill(&candidate,sizeof(candidate),seed);
        fill(&expected,sizeof(expected),seed);
        expected.object.primary_vtable=0x9ffe2c;
        expected.object.enabled=1;
        expected.object.secondary_vtable=0x9ffe6c;
        expected.object.unknown0c=0;
        expected.object.file_handle=0;
        expected.object.first.inline_storage[0]=0;
        expected.object.first.length=0;
        expected.object.first.capacity=7;
        expected.object.second.inline_storage[0]=0;
        expected.object.second.length=0;
        expected.object.second.capacity=7;
        for(unsigned repeat=0;repeat<2;++repeat) {
            uint32_t saved[8];
            for(unsigned i=0;i<8;++i) saved[i]=oracle_globals[i]=0xa0b00000+seed*16+i;
            recovered::active_save_device=&original.object;
            if(original_save_device_ctor(&original.object)!=&original.object) return 2;
            if(test_get_fs_head()!=fs_storage[0]) return 3;
            if(candidate.object.initialize()!=&candidate.object) return 4;
            if(recovered::active_save_device!=&candidate.object) return 5;
            if(oracle_globals[3]!=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&original.object))) return 6;
            for(unsigned i=0;i<8;++i) if(i!=3 && oracle_globals[i]!=saved[i]) return 7;
            if(!equal(&original,&candidate,sizeof(original))) return 8;
            if(!equal(&original,&expected,sizeof(original))) return 9;
        }
    }
    test_write("save-device-ctor: passed\n",25);
    return 0;
}
