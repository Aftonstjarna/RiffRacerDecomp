#include "impl.hpp"
extern "C" Record88* __attribute__((thiscall)) original_record88_copy_construct(Record88*, const Record88*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Guarded { uint32_t before[4]; Record88 record; uint32_t after[4]; };
static void fill(Guarded& g, uint32_t seed) {
    for (unsigned i=0;i<4;++i) {g.before[i]=seed+i; g.after[i]=~(seed+i);}
    for (unsigned i=0;i<22;++i) g.record.words[i]=seed ^ (0x9e3779b9u*(i+1));
}
static bool equal(const Guarded& a, const Guarded& b) {
    for(unsigned i=0;i<4;++i)
        if(a.before[i]!=b.before[i] || a.after[i]!=b.after[i]) return false;
    for(unsigned i=0;i<22;++i) if(a.record.words[i]!=b.record.words[i]) return false;
    return true;
}
extern "C" int test_main() {
    unsigned fs_storage[4]={0x13579bdfu,0,0,0};
    if(test_install_fs(fs_storage)!=0) return 1;
    const uint32_t patterns[]={0,~uint32_t(0),0x80000000u,0x7fc12345u,0x12345678u};
    for(unsigned trial=0;trial<69;++trial) {
        Guarded src, saved, actual, expected, untouched;
        fill(src,trial*0x1020304u); fill(saved,trial*0x1020304u);
        if(trial<5) for(unsigned i=0;i<22;++i)
            src.record.words[i]=saved.record.words[i]=patterns[trial];
        fill(actual,0xaabbccddu); fill(expected,0xaabbccddu); fill(untouched,0xaabbccddu);
        if(original_record88_copy_construct(&actual.record,&src.record)!=&actual.record) return 2;
        if(test_get_fs_head()!=fs_storage[0]) return 3;
        if(expected.record.copy_construct(src.record)!=&expected.record) return 4;
        if(!equal(actual,expected) || !equal(src,saved)) return 5;
        for(unsigned i=0;i<22;++i) if(actual.record.words[i]!=src.record.words[i]) return 6;
        for(unsigned i=0;i<4;++i) if(actual.before[i]!=untouched.before[i] || actual.after[i]!=untouched.after[i]) return 7;
        if(original_record88_copy_construct(&actual.record,&actual.record)!=&actual.record) return 8;
        if(test_get_fs_head()!=fs_storage[0]) return 9;
        if(expected.record.copy_construct(expected.record)!=&expected.record || !equal(actual,expected)) return 10;
    }
    return 0;
}
