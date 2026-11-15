#include "impl.hpp"
using namespace riff;
// EAX unused, EDX=end, ECX=begin; fourth argument on caller-cleaned stack.
extern "C" ReferenceView** __attribute__((regparm(3))) original_reference_slot_assign_range(
    unsigned, ReferenceView* const*, ReferenceView* const*, ReferenceView**);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Object { uint32_t before; ReferenceBase base; uint32_t middle;
                ReferenceView view; uint32_t after; };
struct State {
    Object objects[3];
    AdjustmentTable adjustments[3];
    ReferenceView* slots[12];
    unsigned calls, ids[12], flags[12], observed[12];
    bool mutate;
};
static State* active;
static void* RIFF_THISCALL destroy(ReferenceBase* base, unsigned flags) {
    unsigned id=0;
    while (id<3 && base != &active->objects[id].base) ++id;
    unsigned n=active->calls++;
    if(n<12) {
        active->ids[n]=id; active->flags[n]=flags;
        active->observed[n]=(active->slots[4]==&active->objects[0].view);
    }
    if(active->mutate) active->slots[0]=&active->objects[2].view;
    return base;
}
static LifetimeTable lifetime={destroy};
static void init(State& s, unsigned mode) {
    s.calls=0; s.mutate=(mode==8);
    for(unsigned i=0;i<12;++i) {
        s.ids[i]=s.flags[i]=s.observed[i]=0xabababab;
        s.slots[i]=0;
    }
    for(unsigned i=0;i<3;++i) {
        Object& o=s.objects[i];
        o.before=0x11223344+i; o.middle=0xaabbccdd; o.after=0x87654321;
        o.base.methods=&lifetime; o.base.count=5;
        s.adjustments[i].unknown=0xdeadbeef;
        s.adjustments[i].base_displacement=static_cast<int32_t>(
            reinterpret_cast<char*>(&o.base)-reinterpret_cast<char*>(&o.view));
        o.view.adjustments=&s.adjustments[i];
    }
    for(unsigned i=0;i<8;++i) s.slots[i]=&s.objects[i%3].view;
    if(mode==1) { s.slots[0]=0; s.slots[4]=0; }
    if(mode==2) s.slots[0]=0;
    if(mode==3) s.slots[4]=0;
    if(mode==4) s.slots[4]=s.slots[0];
    if(mode==5 || mode==8) s.objects[1].base.count=1;
    if(mode==6) s.objects[1].base.count=0;
    if(mode==7) s.objects[0].base.count=0xffffffffu;
    if(mode==8) { s.slots[4]=&s.objects[0].view; s.objects[0].base.count=1;
                  s.slots[0]=&s.objects[1].view; }
}
static int slot_id(State& s, ReferenceView* p) {
    if(!p) return -1;
    for(int i=0;i<3;++i) if(p==&s.objects[i].view) return i;
    return -2;
}
static bool same(State& a, State& b) {
    if(a.calls!=b.calls) return false;
    for(unsigned i=0;i<12;++i) {
        if(slot_id(a,a.slots[i])!=slot_id(b,b.slots[i]) || a.ids[i]!=b.ids[i] ||
           a.flags[i]!=b.flags[i] || a.observed[i]!=b.observed[i]) return false;
    }
    for(unsigned i=0;i<3;++i) {
        Object& x=a.objects[i]; Object& y=b.objects[i];
        if(x.base.count!=y.base.count || x.before!=y.before || x.middle!=y.middle ||
           x.after!=y.after || x.base.methods!=&lifetime || y.base.methods!=&lifetime ||
           x.view.adjustments!=&a.adjustments[i] || y.view.adjustments!=&b.adjustments[i] ||
           a.adjustments[i].unknown!=0xdeadbeef || b.adjustments[i].unknown!=0xdeadbeef ||
           a.adjustments[i].base_displacement!=b.adjustments[i].base_displacement) return false;
    }
    return true;
}
extern "C" int test_main() {
    unsigned fs[8]={0x13572468,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    unsigned head=test_get_fs_head();
    if(head!=fs[0]) return 2;
    for(unsigned mode=0;mode<9;++mode) for(unsigned n=0;n<=4;++n)
    for(unsigned layout=0;layout<4;++layout) {
        State a,b; init(a,mode); init(b,mode);
        unsigned src=layout==2?1:0;
        unsigned dst=layout==0?4:(layout==1?1:0);
        active=&a;
        ReferenceView** r=original_reference_slot_assign_range(0,a.slots+src+n,a.slots+src,a.slots+dst);
        if(test_get_fs_head()!=head) return 3;
        if(r!=a.slots+dst+n) return 4;
        active=&b;
        if(assign_reference_range(b.slots+src,b.slots+src+n,b.slots+dst)!=b.slots+dst+n) return 5;
        if(!same(a,b)) return 6;
        if(mode==8 && n==1 && layout==0 &&
           (a.calls!=1 || a.flags[0]!=1 || a.observed[0]!=1 ||
            a.slots[4]!=&a.objects[2].view || a.objects[2].base.count!=6)) return 7;
    }
    if(original_reference_slot_assign_range(0,0,0,0)!=0 || test_get_fs_head()!=head) return 8;
    if(assign_reference_range(0,0,0)!=0) return 9;
    // Count owner may also be after the view (positive table displacement).
    struct Positive { ReferenceView view; uint32_t guard; ReferenceBase base; uint32_t tail; };
    Positive p={};
    AdjustmentTable adjustment={0xcafebabe,static_cast<int32_t>(
        reinterpret_cast<char*>(&p.base)-reinterpret_cast<char*>(&p.view))};
    p.view.adjustments=&adjustment; p.guard=0x99887766; p.tail=0x55443322;
    p.base.methods=&lifetime; p.base.count=7;
    ReferenceView* source[1]={&p.view}; ReferenceView* dest[1]={0};
    if(original_reference_slot_assign_range(0,source+1,source,dest)!=dest+1 ||
       test_get_fs_head()!=head || dest[0]!=&p.view || p.base.count!=8) return 10;
    dest[0]=0; p.base.count=7;
    if(assign_reference_range(source,source+1,dest)!=dest+1 ||
       dest[0]!=&p.view || p.base.count!=8 || p.guard!=0x99887766 ||
       p.tail!=0x55443322 || p.view.adjustments!=&adjustment ||
       p.base.methods!=&lifetime || adjustment.unknown!=0xcafebabe) return 11;
    // Old destination release through the same positive adjustment.
    source[0]=0;
    original_reference_slot_assign_range(0,source+1,source,dest);
    if(test_get_fs_head()!=head || dest[0]!=0 || p.base.count!=7) return 12;
    dest[0]=&p.view; p.base.count=8;
    assign_reference_range(source,source+1,dest);
    if(dest[0]!=0 || p.base.count!=7 || p.guard!=0x99887766 || p.tail!=0x55443322) return 13;
    return 0;
}
