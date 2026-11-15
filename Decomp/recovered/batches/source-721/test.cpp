#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_reference_slot_vector_remove_tail(ReferenceSlotVector*, uint32_t);
extern "C" void test_write(const char*, unsigned);
struct Object { ReferenceBase before; ReferenceSlot slot; ReferenceBase after; uint32_t guard; };
struct Fixture {
    uint32_t left;
    ReferenceSlotVector vector;
    uint32_t right;
    ReferenceSlot* slots[8];
    Object objects[3];
    uint32_t calls, ids[8], flags[8], visible_end[8];
    uint32_t mutate;
};
static Fixture f;
static unsigned char expected[sizeof(Fixture)];
static int32_t offsets[3][2];
static void __attribute__((thiscall)) deleted(ReferenceBase* base, uint32_t flag) {
    unsigned id = 99;
    for (unsigned i=0;i<3;++i)
        if (base == &f.objects[i].before || base == &f.objects[i].after) id=i;
    unsigned n=f.calls++;
    if(n<8) { f.ids[n]=id; f.flags[n]=flag;
        f.visible_end[n]=static_cast<uint32_t>(f.vector.end-f.slots); }
    if(f.mutate) {
        f.vector.end=f.slots;
        f.slots[6]=&f.objects[2].slot;
    }
}
static DeleteReference methods[1]={deleted};
static void reset(unsigned scenario) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof(f);++i) p[i]=0;
    f.left=0x12345678; f.right=0x87654321;
    f.vector.begin=f.slots; f.vector.end=f.slots+7; f.vector.capacity_end=f.slots+8;
    for(unsigned i=0;i<3;++i) {
        Object& o=f.objects[i];
        ReferenceBase* base=i==1 ? &o.before : &o.after;
        offsets[i][0]=0x1234;
        offsets[i][1]=static_cast<int32_t>(reinterpret_cast<unsigned char*>(base)-reinterpret_cast<unsigned char*>(&o.slot));
        o.slot.base_offsets=offsets[i];
        o.before.virtual_methods=methods; o.after.virtual_methods=methods;
        o.before.references=0xaabbccdd; o.after.references=0xaabbccdd;
        base->references=i==0 ? 2 : 1;
        o.guard=0xcafebabe;
    }
    f.slots[0]=&f.objects[2].slot;
    f.slots[1]=&f.objects[0].slot;
    f.slots[2]=0;
    f.slots[3]=&f.objects[1].slot;
    f.slots[4]=&f.objects[0].slot;
    f.slots[5]=0;
    f.slots[6]=&f.objects[0].slot;
    f.slots[7]=&f.objects[1].slot;
    if(scenario==1) f.objects[0].after.references=0;
    if(scenario==2) f.mutate=1;
    if(scenario==4) for(unsigned i=0;i<8;++i) f.slots[i]=0;
    if(scenario==3) { f.vector.begin=0; f.vector.end=0; f.vector.capacity_end=0; }
}
extern "C" int test_main() {
    const uint32_t counts[]={0,1,3,4,7,0x40000000u,0x40000001u};
    for(unsigned scenario=0;scenario<5;++scenario) {
        for(unsigned c=0;c<7;++c) {
            if(scenario==3 && c!=0 && c!=5) continue;
            reset(scenario);
            original_reference_slot_vector_remove_tail(&f.vector,counts[c]);
            unsigned char* p=reinterpret_cast<unsigned char*>(&f);
            for(unsigned i=0;i<sizeof(f);++i) expected[i]=p[i];
            reset(scenario);
            f.vector.remove_tail(counts[c]);
            for(unsigned i=0;i<sizeof(f);++i) if(expected[i]!=p[i]) return 1;
            if(f.left!=0x12345678 || f.right!=0x87654321) return 2;
            for(unsigned i=0;i<f.calls && i<8;++i) if(f.flags[i]!=1) return 3;
        }
    }
    test_write("remove-tail differential tests passed\n",38);
    return 0;
}
