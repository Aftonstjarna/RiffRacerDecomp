#include "impl.hpp"
extern "C" void RR_THISCALL original_query_create(QueryOwner*);
extern "C" void test_write(const char*, unsigned);
struct TaggedQuery { Query base; unsigned id; };
struct Event { unsigned kind, id, type, slot, state[6]; };
struct Run { QueryOwner owner; unsigned char tail[32]; Event events[16]; unsigned count, calls; };
static Run runs[2];
static Run* active;
static TaggedQuery objects[12];
static Device devices[2];
static DeviceVtable tables[2];
static unsigned failAt, mode, mutate;
static int32_t successStatus, failureStatus;
static unsigned id(Query* q) { return q ? static_cast<TaggedQuery*>(static_cast<void*>(q))->id : 0; }
static Event& event(unsigned kind, unsigned ident, unsigned type, unsigned slot) {
    Event& e = active->events[active->count++];
    e.kind=kind; e.id=ident; e.type=type; e.slot=slot;
    for(unsigned i=0;i<6;++i) e.state[i]=id(active->owner.queries[i/3][i%3]);
    return e;
}
static uint32_t RR_STDCALL release(Query* q) {
    unsigned n=id(q);
    event(2,n,0,0);
    // A COM callback can alter the next slot; read-before-clear is observable.
    if(mutate) {
        unsigned g = n % 2;
        active->owner.queries[g][0]=&objects[10].base;
        active->owner.queries[g][1]=&objects[11].base;
    }
    return 0x87654321u;
}
static int32_t RR_STDCALL create(Device* device, uint32_t type, Query** out) {
    unsigned call=active->calls++;
    unsigned slot=99;
    for(unsigned i=0;i<6;++i) if(out==&active->owner.queries[i/3][i%3]) slot=i;
    event(1,device==&devices[0]?0:1,type,slot);
    bool failed=call==failAt;
    if(!failed || mode==1) *out=&objects[call].base;
    else if(mode==2) *out=0;
    if(mutate) active->owner.device=&devices[(call+1)%2];
    return failed?failureStatus:successStatus;
}
static void init(Run& r,unsigned mask) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&r);
    for(unsigned i=0;i<sizeof(r);++i) p[i]=0;
    p=reinterpret_cast<unsigned char*>(&r.owner);
    for(unsigned i=0;i<sizeof(r.owner);++i) p[i]=(unsigned char)(i*37+19);
    r.owner.device=&devices[0];
    for(unsigned i=0;i<6;++i) r.owner.queries[i/3][i%3]=(mask&(1u<<i))?&objects[i+6].base:0;
    for(unsigned i=0;i<sizeof(r.tail);++i) r.tail[i]=(unsigned char)(i+31);
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    QueryVtable qvt = {{0,0},release};
    for(unsigned i=0;i<12;++i) { objects[i].base.vtable=&qvt; objects[i].id=i+1; }
    for(unsigned i=0;i<2;++i) { tables[i].createQuery=create; devices[i].vtable=&tables[i]; }
    // Every failure position, null/non-null initial-slot combination, and output
    // behavior (unchanged, assigned on failure, cleared on failure).
    for(unsigned f=0;f<7;++f) for(unsigned mask=0;mask<64;++mask)
    for(mode=0;mode<3;++mode) for(mutate=0;mutate<2;++mutate)
    for(unsigned status=0;status<3;++status) {
        failAt=f; successStatus=status==0?0:status==1?1:0x7fffffff;
        failureStatus=status==0?(-1):status==1?(int32_t)0x80000000u:(int32_t)0x8876086au;
        init(runs[0],mask); init(runs[1],mask);
        QueryOwner before=runs[0].owner;
        active=&runs[0]; original_query_create(&active->owner);
        active=&runs[1]; active->owner.createQueries();
        if(!equal(&runs[0],&runs[1],sizeof(Run))) return 1;
        if(active->calls!=(f<6?f+1:6)) return 2;
        if(!equal(&before,&active->owner,0x78) ||
           !equal(before.unknown7c,active->owner.unknown7c,sizeof(before.unknown7c))) return 3;
        if(!mutate && f<6) for(unsigned i=0;i<6;++i)
            if(active->owner.queries[i/3][i%3]) return 4;
        unsigned expectedTypes[3]={10,10,12}; unsigned c=0;
        for(unsigned i=0;i<active->count;++i) if(active->events[i].kind==1) {
            if(active->events[i].type!=expectedTypes[c%3] || active->events[i].slot!=c) return 5;
            ++c;
        }
    }
    test_write("query-create differential tests passed\n",39);
    return 0;
}
extern "C" void* memcpy(void* dst,const void* src,unsigned n) {
    unsigned char* d=(unsigned char*)dst; const unsigned char* s=(const unsigned char*)src;
    for(unsigned i=0;i<n;++i) d[i]=s[i];
    return dst;
}
