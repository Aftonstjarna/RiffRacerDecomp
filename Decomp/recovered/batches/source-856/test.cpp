#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_string_buckets_resize(State*,uint32_t);
// Allocator helper uses ECX=state, EDX=old pointer, caller-cleaned stack sizes.
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(unsigned,void*,State*,uint32_t,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void* p,int c,unsigned n) {
    for(unsigned i=0;i<n;++i) static_cast<uint8_t*>(p)[i]=static_cast<uint8_t>(c);
    return p;
}
extern "C" void* memcpy(void* d,const void* s,unsigned n) {
    for(unsigned i=0;i<n;++i) static_cast<uint8_t*>(d)[i]=static_cast<const uint8_t*>(s)[i];
    return d;
}
static bool equalBytes(const void* a,const void* b,unsigned n) {
    const uint8_t* x=static_cast<const uint8_t*>(a);
    const uint8_t* y=static_cast<const uint8_t*>(b);
    while(n--) {
        if(*x++!=*y++) return false;
    }
    return true;
}
static State state;
static Global globals,alternate,third;
static String* oldBuckets[32];
static String* alternateBuckets[32];
static String* newBuckets[66]; // two guard slots beyond maximum initialized range
static String nodes[24];
static uint32_t requested,oldCount,mode,calls,bad,phase;
static String** selectedOld;
static uint32_t selectedCount;
struct Event {void* old;uint32_t oldSize,newSize;Global* published;};
static Event events[2];
static void* allocator(void* data,void* old,uint32_t oldSize,uint32_t newSize) {
    if(data!=&globals || calls>=2) {bad=1;return newBuckets;}
    Event& e=events[calls++];e.old=old;e.oldSize=oldSize;e.newSize=newSize;e.published=state.global;
    if(phase==0) {
        phase=1;
        if(old || oldSize || newSize!=requested*4u) bad=2;
        if(mode&1) state.global=&alternate;
        return newBuckets;
    }
    if(old!=selectedOld || oldSize!=selectedCount*4u || newSize) bad=3;
    Global* g=(mode&1)?&alternate:&globals;
    if(g->buckets!=selectedOld || g->capacity!=selectedCount) bad=4;
    // Free sees fully relinked strings, before bucket publication.
    if(static_cast<int32_t>(requested)>0 && static_cast<int32_t>(selectedCount)>0) {
        for(unsigned i=0;i<24;++i) {
            String* p=newBuckets[nodes[i].hash&(requested-1u)];
            unsigned steps=0;
            while(p && p!=&nodes[i] && steps++<24) p=p->next;
            if(p!=&nodes[i]) bad=5;
        }
    }
    if(mode&2) state.global=&third;
    phase=2;
    return 0;
}
static void* reallocAdapter(State* s,void* p,uint32_t a,uint32_t b) {
    void* r=original_script_reallocate(0,p,s,a,b);
    if(test_get_fs_head()!=0xffffffffu) bad=6;
    return r;
}
static void* sizeError(State*) {bad=7;return 0;}
static const Services services={reallocAdapter,sizeError};
static void setup(uint32_t count,uint32_t oldCapacity,unsigned flags,unsigned gc) {
    memset(&state,0xa5,sizeof state);memset(&globals,0x76,sizeof globals);
    memset(&alternate,0x87,sizeof alternate);memset(&third,0x98,sizeof third);
    memset(oldBuckets,0,sizeof oldBuckets);memset(alternateBuckets,0,sizeof alternateBuckets);
    memset(newBuckets,0xcd,sizeof newBuckets);memset(nodes,0x59,sizeof nodes);
    memset(events,0,sizeof events);
    requested=count;oldCount=oldCapacity;mode=flags;calls=bad=phase=0;
    globals.buckets=oldBuckets;globals.capacity=oldCapacity;
    globals.allocator=allocator;globals.allocatorData=&globals;globals.gcState=static_cast<uint8_t>(gc);
    globals.allocatedBytes=0xfffffff0u;
    alternate.buckets=alternateBuckets;alternate.capacity=oldCapacity;
    alternate.allocator=allocator;alternate.allocatorData=&globals;
    state.global=&globals;
    selectedOld=(flags&1)?alternateBuckets:oldBuckets;selectedCount=oldCapacity;
    for(unsigned i=0;i<24;++i) {
        nodes[i].hash=(i*0x9e3779b9u)^(i%3==0?0xffffffffu:0);
        nodes[i].next=0;
        if(static_cast<int32_t>(oldCapacity)>0) {
            // Deliberately include empty old buckets and multi-node chains.
            unsigned bucket=(i*3)%oldCapacity;
            nodes[i].next=selectedOld[bucket];selectedOld[bucket]=&nodes[i];
        }
    }
}
struct Snapshot {
    State s; Global g,a,t; String* old[32]; String* alt[32]; String* fresh[66];
    String n[24];Event e[2];unsigned callCount,stage;
};
static void capture(Snapshot& s) {
    memset(&s,0,sizeof s);s.s=state;s.g=globals;s.a=alternate;s.t=third;
    memcpy(s.old,oldBuckets,sizeof oldBuckets);memcpy(s.alt,alternateBuckets,sizeof alternateBuckets);
    memcpy(s.fresh,newBuckets,sizeof newBuckets);memcpy(s.n,nodes,sizeof nodes);
    memcpy(s.e,events,sizeof events);s.callCount=calls;s.stage=phase;
}
static int run(uint32_t count,uint32_t oldCapacity,unsigned flags,unsigned gc) {
    setup(count,oldCapacity,flags,gc);
    Snapshot before;capture(before);
    original_script_string_buckets_resize(&state,count);
    if(test_get_fs_head()!=0xffffffffu || bad) return 10+bad;
    Snapshot expected;capture(expected);
    if(gc==2) {
        if(!equalBytes(&before,&expected,sizeof before)) return 20;
    } else {
        if(calls!=2 || phase!=2) return 21;
        Global* g=(flags&1)?&alternate:&globals;
        if(g->buckets!=newBuckets || g->capacity!=count) return 22;
        if(globals.allocatedBytes!=0xfffffff0u+count*4u-((flags&1)?0u:oldCapacity*4u)) return 23;
        // Independently construct expected chain order and all memory effects.
        Snapshot independent=before;
        String** old=(flags&1)?before.alt:before.old;
        if(static_cast<int32_t>(count)>0) {
            for(uint32_t i=0;i<count;++i) independent.fresh[i]=0;
        }
        for(int32_t i=0;i<static_cast<int32_t>(oldCapacity);++i) {
            for(String* p=old[i];p;) {
                unsigned index=static_cast<unsigned>(p-nodes);
                String* next=before.n[index].next;
                unsigned bucket=before.n[index].hash&(count-1u);
                independent.n[index].next=independent.fresh[bucket];
                independent.fresh[bucket]=p;p=next;
            }
        }
        Global& changed=(flags&1)?independent.a:independent.g;
        changed.buckets=newBuckets;changed.capacity=count;
        independent.g.allocatedBytes+=count*4u;
        if(flags&1) independent.a.allocatedBytes-=oldCapacity*4u;
        else independent.g.allocatedBytes-=oldCapacity*4u;
        independent.s.global=(flags&2)?&third:((flags&1)?&alternate:&globals);
        independent.e[0].old=0;independent.e[0].oldSize=0;independent.e[0].newSize=count*4u;independent.e[0].published=&globals;
        independent.e[1].old=selectedOld;independent.e[1].oldSize=oldCapacity*4u;independent.e[1].newSize=0;independent.e[1].published=(flags&1)?&alternate:&globals;
        independent.callCount=2;independent.stage=2;
        if(!equalBytes(&independent,&expected,sizeof expected)) return 24;
    }
    setup(count,oldCapacity,flags,gc);
    state.resizeStringBuckets(count,services);
    Snapshot actual;capture(actual);
    if(bad || test_get_fs_head()!=0xffffffffu || !equalBytes(&expected,&actual,sizeof actual)) return 25;
    return 0;
}
extern "C" int test_main() {
    static unsigned fs[8];fs[0]=0xffffffffu;
    if(test_install_fs(fs)!=0) return 1;
    const unsigned sizes[]={1,2,3,4,7,8,16,31,32,64};
    const unsigned oldSizes[]={0,1,2,7,16,32};
    for(unsigned n=0;n<10;++n) for(unsigned o=0;o<6;++o) for(unsigned flags=0;flags<4;++flags) {
        int r=run(sizes[n],oldSizes[o],flags,0);if(r) return r;
    }
    // Empty old tables, zero-sized allocation/free, and negative signed old count.
    // UINT32_MAX wraps the size guard and allocation byte count; no memory is
    // touched because both signed traversal counts are nonpositive.
    const unsigned emptyNew[]={0,0xffffffffu};
    const unsigned emptyOld[]={0,0x80000000u,0xffffffffu};
    for(unsigned n=0;n<2;++n) for(unsigned o=0;o<3;++o) {
        int r=run(emptyNew[n],emptyOld[o],0,0);if(r) return r;
    }
    const unsigned suppressed[]={0,1,32,0x3ffffffe,0x3fffffff,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<7;++i) {int r=run(suppressed[i],7,3,2);if(r) return r;}
    int r=run(8,7,3,1);if(r) return r;
    r=run(8,7,0,255);if(r) return r;
    test_write("PASS\n",5);return 0;
}
