#include "impl.hpp"
// This is NOT thiscall or stdcall: caller at 0x4866de pops position.
// GCC regparm(3) supplies EAX (unused), EDX (ordinal), ECX (prototype),
// leaving position on the caller-cleaned stack, exactly as the original needs.
extern "C" const char* __attribute__((regparm(3))) original_script_prototype_local_name(
    uint32_t unused_eax, uint32_t ordinal, const riff::ScriptPrototype*, int32_t position);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned char names[6][32];
static riff::ScriptLocal entries[6];
static riff::ScriptPrototype proto;
static unsigned char saved_proto[sizeof(proto)];
static unsigned char saved_entries[sizeof(entries)];
static unsigned char saved_names[sizeof(names)];
static void save(void* dst, const void* src, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(uint32_t ordinal, int32_t position, const char* expected, bool explicit_expected) {
    save(saved_proto,&proto,sizeof(proto));
    save(saved_entries,entries,sizeof(entries));
    save(saved_names,names,sizeof(names));
    const char* recovered=proto.local_name(ordinal,position);
    const char* original=original_script_prototype_local_name(0xabcdef01u,ordinal,&proto,position);
    if(test_get_fs_head()!=0x13572468u) return 1;
    if(recovered!=original || (explicit_expected && recovered!=expected)) return 2;
    if(!same(saved_proto,&proto,sizeof(proto)) || !same(saved_entries,entries,sizeof(entries)) || !same(saved_names,names,sizeof(names))) return 3;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs_storage[8]={0x13572468u,0,0,0,0,0,0,0};
    if(test_install_fs(fs_storage)!=0) return 10;
    unsigned char* p=reinterpret_cast<unsigned char*>(&proto);
    for(unsigned i=0;i<sizeof(proto);++i) p[i]=static_cast<unsigned char>(i*7+3);
    for(unsigned i=0;i<sizeof(names);++i) reinterpret_cast<unsigned char*>(names)[i]=static_cast<unsigned char>(i+19);
    proto.locals=0;
    const int32_t counts[]={-2147483647-1,-1,0};
    for(unsigned i=0;i<3;++i) { proto.local_count=counts[i]; if(check(1,0,0,true)) return 11; }
    proto.locals=entries; proto.local_count=6;
    for(unsigned i=0;i<6;++i) { entries[i].name_object=names[i]; entries[i].start_position=int32_t(i*2)-4; entries[i].end_position=int32_t(i*2)+3; }
    if(check(1,-4,reinterpret_cast<const char*>(names[0])+16,true)) return 12;
    if(check(2,0,reinterpret_cast<const char*>(names[1])+16,true)) return 13;
    if(check(1,13,0,true) || check(0,0,0,true) || check(0xffffffffu,0,0,true)) return 14;
    const int32_t positions[]={-2147483647-1,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,2147483647};
    const uint32_t ordinals[]={0,1,2,3,4,5,6,7,0x7fffffffu,0x80000000u,0xffffffffu};
    // Also exercise zero/reversed ranges and out-of-order early termination.
    for(unsigned mode=0;mode<5;++mode) {
        if(mode==1) { entries[1].end_position=entries[1].start_position; entries[3].end_position=-100; }
        if(mode==2) entries[0].start_position=100;
        if(mode==3) { entries[0].start_position=(-2147483647-1); entries[0].end_position=2147483647; entries[0].name_object=0; }
        if(mode==4) entries[0].name_object=reinterpret_cast<void*>(uintptr_t(0xfffffff8u));
        for(unsigned n=0;n<=6;++n) {
            proto.local_count=int32_t(n);
            for(unsigned a=0;a<sizeof(positions)/sizeof(positions[0]);++a)
                for(unsigned b=0;b<sizeof(ordinals)/sizeof(ordinals[0]);++b)
                    if(check(ordinals[b],positions[a],0,false)) return 20+int(mode);
        }
    }
    test_write("local-name differential checks passed\n",38);
    return 0;
}
