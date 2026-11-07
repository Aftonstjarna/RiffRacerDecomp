#include "impl.hpp"
extern "C" riff::Shader* __attribute__((thiscall))
original_shader_slot_select(const riff::ShaderManager*, uint32_t);
static riff::ShaderManager manager;
static unsigned char snapshot[sizeof(manager)];
static riff::Shader* backing[260];
static riff::Shader* table_snapshot[260];
static void capture() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&manager);
    for (unsigned i=0;i<sizeof(manager);++i) snapshot[i]=p[i];
    for (unsigned i=0;i<260;++i) table_snapshot[i]=backing[i];
}
static bool unchanged() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&manager);
    for (unsigned i=0;i<sizeof(manager);++i) if(snapshot[i]!=p[i]) return false;
    for (unsigned i=0;i<260;++i) if(table_snapshot[i]!=backing[i]) return false;
    return true;
}
extern "C" int test_main() {
    unsigned char* p = reinterpret_cast<unsigned char*>(&manager);
    for (unsigned i=0;i<sizeof(manager);++i) p[i]=static_cast<unsigned char>(i*37+19);
    for (unsigned i=0;i<260;++i)
        backing[i]=reinterpret_cast<riff::Shader*>(uintptr_t(0x10000+i*0x101));
    backing[0]=0; backing[229]=reinterpret_cast<riff::Shader*>(uintptr_t(0xffffffffu));
    const unsigned char flags[]={0,1,2,0x80,0xff};
    const uint32_t indices[]={0,1,0x59,0x5a,0x5b,0x5c,0x5d,0x65,227,228,229,255,
                              0x40000000u,0x80000001u,0xc00000e5u,0xffffffffu};
    // Extra space before table makes index -1 a valid wrapped address.
    for(unsigned shift=1;shift<=2;++shift) {
        manager.slots=backing+shift;
        for(unsigned a=0;a<5;++a) for(unsigned b=0;b<5;++b) {
            manager.first_override=flags[a]; manager.second_override=flags[b];
            for(unsigned n=0;n<sizeof(indices)/sizeof(indices[0]);++n) {
                const uint32_t index=indices[n];
                const uint32_t chosen=flags[a]?228:flags[b]?229:index;
                const uint32_t address=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(manager.slots)) + chosen*4u;
                riff::Shader* expected=*reinterpret_cast<riff::Shader**>(uintptr_t(address));
                capture();
                riff::Shader* original=original_shader_slot_select(&manager,index);
                if(original!=expected || !unchanged()) return 1;
                riff::Shader* recovered=manager.select(index);
                if(recovered!=original || !unchanged()) return 2;
            }
        }
    }
    return 0;
}
