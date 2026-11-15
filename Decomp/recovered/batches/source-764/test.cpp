#include "impl.hpp"
extern "C" bool __attribute__((stdcall)) original_pointer_range_has_state_six_or_seven(
    uint32_t, int32_t, const riff::PointerRange32*);
static uint32_t objects[4][160];
static uint32_t entries[4];
static uint32_t saved[4][160];
static uint32_t address(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static int check(riff::PointerRange32 r, int32_t index, bool expected) {
    for (unsigned j=0;j<4;++j) for(unsigned k=0;k<160;++k) saved[j][k]=objects[j][k];
    uint32_t oldEntries[4];
    for(unsigned j=0;j<4;++j) oldEntries[j]=entries[j];
    const riff::PointerRange32 before=r;
    for(unsigned variant=0;variant<2;++variant) {
        const uint32_t unused=variant ? 0xdeadbeefu : 0;
        bool a=original_pointer_range_has_state_six_or_seven(unused,index,&r);
        if(a!=expected) return 1;
        if(r.begin!=before.begin || r.end!=before.end || r.capacity!=before.capacity) return 2;
        for(unsigned j=0;j<4;++j) {
            if(entries[j]!=oldEntries[j]) return 3;
            for(unsigned k=0;k<160;++k) if(objects[j][k]!=saved[j][k]) return 4;
        }
        bool b=riff::pointer_range_has_state_six_or_seven(unused,index,&r);
        if(b!=a) return 5;
        if(r.begin!=before.begin || r.end!=before.end || r.capacity!=before.capacity) return 6;
        for(unsigned j=0;j<4;++j) {
            if(entries[j]!=oldEntries[j]) return 7;
            for(unsigned k=0;k<160;++k) if(objects[j][k]!=saved[j][k]) return 8;
        }
    }
    return 0;
}
extern "C" int test_main() {
    for(unsigned j=0;j<4;++j) {
        entries[j]=address(objects[j]);
        for(unsigned k=0;k<160;++k) objects[j][k]=0xa5a5a5a5u;
    }
    riff::PointerRange32 r={address(entries),address(entries+4),0xdeadbeefu};
    const uint32_t states[]={0,1,5,6,7,8,0xffffffffu,0x80000006u};
    const int32_t indices[]={-2,-1,0,1,2,3,0x40000000};
    for(unsigned n=0;n<7;++n) {
        int32_t index=indices[n];
        uint32_t slot=(static_cast<uint32_t>(index)*100u+0xd4u)/4u;
        for(unsigned s=0;s<8;++s) for(unsigned pos=0;pos<4;++pos) {
            for(unsigned j=0;j<4;++j) objects[j][slot]=8;
            objects[pos][slot]=states[s];
            if(check(r,index,states[s]==6 || states[s]==7)) return 10;
        }
    }
    // Incomplete trailing pointer bytes are rounded down by SAR.
    for(unsigned j=0;j<4;++j) objects[j][53]=8;
    objects[3][53]=6;
    for(unsigned bytes=0;bytes<=16;++bytes) {
        r.end=r.begin+bytes;
        if(check(r,0,bytes>=16)) return 11;
    }
    // No pointer dereference on zero/negative signed counts, even bogus starts.
    const uint32_t distances[]={0,1,2,3,0xffffffffu,0xfffffffcu,0x80000000u};
    for(unsigned j=0;j<7;++j) {
        r.begin=0xfffffff0u; r.end=r.begin+distances[j];
        if(check(r,0x7fffffff,false)) return 12;
    }
    // Early exit must not inspect the invalid pointer following a match.
    r.begin=address(entries); r.end=address(entries+4);
    objects[0][53]=7; entries[1]=0; entries[2]=0; entries[3]=0;
    if(check(r,0,true)) return 13;
    return 0;
}
