#include "impl.hpp"
extern "C" void VIEW_STDCALL original_worker_view_pointer_range_destroy(WorkerView**, WorkerView**);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Fixture { WorkerView view; uint32_t untouched; CountedView counted; uint32_t tail; };
static unsigned calls, args[16], ids[16];
static CountedView* objects[4];
static void VIEW_THISCALL record(CountedView* p, unsigned flag) {
    unsigned id = 99;
    for (unsigned i = 0; i < 4; ++i) if (objects[i] == p) id = i;
    if (calls < 16) { ids[calls] = id; args[calls] = flag; }
    ++calls;
}
static CountedViewTable ct = {record};
static ViewTable vt = {0, 8};
struct Result { uint32_t counts[4], untouched[4], tails[4]; unsigned n, id[16], arg[16]; unsigned range_ok; };
static Result run(bool original, int scenario, unsigned head) {
    Fixture f[4]; WorkerView* range[8]; Result r = {};
    for (unsigned i=0;i<4;++i) {
        f[i].view.table=&vt; f[i].untouched=0x11223300u+i;
        f[i].counted.table=&ct; f[i].counted.references=i==0 ? 1 : i==1 ? 2 : i==2 ? 0 : 3;
        f[i].tail=0x55667700u+i; objects[i]=&f[i].counted;
    }
    range[0]=&f[0].view; range[1]=0; range[2]=&f[1].view; range[3]=&f[1].view;
    range[4]=&f[2].view; range[5]=&f[3].view; range[6]=&f[0].view; range[7]=0;
    WorkerView* saved[8]; for (unsigned i=0;i<8;++i) saved[i]=range[i];
    calls=0; for(unsigned i=0;i<16;++i) {ids[i]=args[i]=0;}
    WorkerView** begin=range+(scenario==1 ? 3 : 0);
    WorkerView** end=range+(scenario==1 ? 3 : scenario==2 ? 1 : 8);
    if(original) original_worker_view_pointer_range_destroy(begin,end);
    else worker_view_pointer_range_destroy(begin,end);
    r.range_ok = test_get_fs_head()==head;
    for(unsigned i=0;i<8;++i) if(range[i]!=saved[i]) r.range_ok=0;
    for(unsigned i=0;i<4;++i) {
        r.counts[i]=f[i].counted.references; r.untouched[i]=f[i].untouched; r.tails[i]=f[i].tail;
        if(f[i].view.table!=&vt || f[i].counted.table!=&ct) r.range_ok=0;
    }
    r.n=calls; for(unsigned i=0;i<16;++i) {r.id[i]=ids[i];r.arg[i]=args[i];}
    return r;
}
extern "C" int test_main() {
    unsigned fs[4]={0x76543210u,0,0,0}; if(test_install_fs(fs)!=0) return 1;
    for(int s=0;s<3;++s) {
        Result a=run(true,s,fs[0]), b=run(false,s,fs[0]);
        if(!a.range_ok || !b.range_ok || a.n!=b.n) return 2;
        for(unsigned i=0;i<4;++i) if(a.counts[i]!=b.counts[i] || a.untouched[i]!=b.untouched[i] || a.tails[i]!=b.tails[i]) return 3;
        for(unsigned i=0;i<16;++i) if(a.id[i]!=b.id[i] || a.arg[i]!=b.arg[i]) return 4;
        if(s==0 && (a.n!=2 || a.id[0]!=0 || a.id[1]!=1 || a.arg[0]!=1 || a.arg[1]!=1 || a.counts[0]!=0xffffffffu || a.counts[1]!=0 || a.counts[2]!=0xffffffffu || a.counts[3]!=2)) return 5;
        if(s==1 && a.n!=0) return 6;
        if(s==2 && (a.n!=1 || a.id[0]!=0 || a.counts[0]!=0)) return 7;
    }
    return 0;
}
