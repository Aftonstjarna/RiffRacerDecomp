#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_device_destroy(Device*);
extern "C" void test_write(const char*,unsigned);
static const unsigned offsets[]={0x478,0x474,0x470,0x484,0x480,0x47c,0x290,0x28c,0x204,0x298,0x29c,0x2a0,0x2a4,0x2a8,0x2ac,0x2b0,0x2b4,0x2b8,0x2bc,0x2c0,0x2c4,0x2c8,0x2cc,0x2d0,0x2d4,0x2d8,0x2dc,0x2e0,0x2e4,0x2e8,0x2ec,0x2f0,0x2f4,0x2f8,0x2fc,0x300,0x304,0x308,0x30c,0x310,0x314,0x318,0x21c,0x218,0x214,0x428,0x420,0x42c,0x424,0x430,0x438,0x434,0x440,0x43c,0x448,0x444,0x78,0x7c,0x70,0x74};
static const unsigned N=sizeof(offsets)/sizeof(offsets[0]);
struct Fixture { uint32_t before[8]; Device owner; uint32_t after[8]; };
struct Fake { Resource resource; unsigned id,calls,remaining; };
struct Event { unsigned id; unsigned char snapshot[sizeof(Fixture)]; };
static Fixture fixture, savedFixture;
static Fake objects[64], savedObjects[64];
static Event events[64], savedEvents[64];
static unsigned count, mutation, trigger;
static Resource*& slot(unsigned i) {
    return *reinterpret_cast<Resource**>(reinterpret_cast<unsigned char*>(&fixture.owner)+offsets[i]);
}
static void copy(void* dst,const void* src,unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static uint32_t RR_STDCALL releaseFake(Resource* p) {
    Fake* obj=reinterpret_cast<Fake*>(p);
    if(count>=64) return 0;
    Event& e=events[count++];
    e.id=obj->id;
    copy(e.snapshot,&fixture,sizeof fixture);
    ++obj->calls; --obj->remaining;
    if(mutation && count==trigger+1) {
        // On full fixtures the trigger matches the release-order slot index.
        // Replace the current slot (must clear), the next slot (must be read
        // after callback), a future slot, and a previously cleared slot.
        slot(trigger)=&objects[62].resource;
        if(trigger+1<N) slot(trigger+1)=&objects[63].resource;
        if(trigger+3<N) slot(trigger+3)=mutation==1 ? 0 : &objects[63].resource;
        if(trigger>0) slot(trigger-1)=&objects[62].resource;
        fixture.owner.unknown000[5]^=0x55;
        fixture.after[2]+=17;
        fixture.owner.state220[2]^=0x12345678;
    }
    return obj->remaining;
}
static ResourceVtable vtable={0,0,releaseFake};
// kind: 0 empty, 1 full, 2 one slot, 3 deterministic mixed mask.
static void initialize(unsigned kind,unsigned arg,unsigned alias) {
    unsigned char* b=reinterpret_cast<unsigned char*>(&fixture);
    for(unsigned i=0;i<sizeof fixture;++i) b[i]=static_cast<unsigned char>(i*37+19);
    for(unsigned i=0;i<64;++i) {
        objects[i].resource.vtable=&vtable;
        objects[i].id=i+1; objects[i].calls=0; objects[i].remaining=0xf0000000+i;
    }
    unsigned seed=arg;
    for(unsigned i=0;i<N;++i) {
        seed=seed*1664525u+1013904223u;
        bool present=kind==1 || (kind==2 && i==arg) || (kind==3 && (seed&0x80000000u));
        slot(i)=present ? &objects[alias ? 0 : i].resource : 0;
    }
    count=0;
    for(unsigned i=0;i<sizeof events;++i) reinterpret_cast<unsigned char*>(events)[i]=0;
}
static bool ordinaryAssertions(unsigned kind,unsigned arg,unsigned alias) {
    unsigned n=0,seed=arg;
    for(unsigned i=0;i<N;++i) {
        seed=seed*1664525u+1013904223u;
        bool present=kind==1 || (kind==2 && i==arg) || (kind==3 && (seed&0x80000000u));
        if(present && events[n++].id!=(alias ? 1 : i+1)) return false;
        if(slot(i)) return false;
    }
    if(n!=count) return false;
    // Check every byte, including gaps, prefix/tail canaries and reset scalars.
    const unsigned char* b=reinterpret_cast<const unsigned char*>(&fixture);
    for(unsigned i=0;i<sizeof fixture;++i) {
        bool cleared=false;
        unsigned ownerStart=offsetof(Fixture,owner);
        for(unsigned j=0;j<N;++j)
            if(i>=ownerStart+offsets[j] && i<ownerStart+offsets[j]+4) cleared=true;
        if(i>=ownerStart+0x220 && i<ownerStart+0x230) cleared=true;
        if(b[i]!=(cleared ? 0 : static_cast<unsigned char>(i*37+19))) return false;
    }
    return true;
}
static bool run(unsigned kind,unsigned arg,unsigned alias,unsigned mode,unsigned at) {
    mutation=mode; trigger=at;
    initialize(kind,arg,alias);
    original_device_destroy(&fixture.owner);
    if(!mode && !ordinaryAssertions(kind,arg,alias)) return false;
    unsigned expectedCount=count;
    copy(&savedFixture,&fixture,sizeof fixture);
    copy(savedObjects,objects,sizeof objects);
    copy(savedEvents,events,sizeof events);
    initialize(kind,arg,alias);
    fixture.owner.destroy();
    if(count!=expectedCount || !equal(&savedFixture,&fixture,sizeof fixture) ||
       !equal(savedObjects,objects,sizeof objects) || !equal(savedEvents,events,sizeof events)) return false;
    if(!mode) {
        fixture.owner.destroy();
        if(count!=expectedCount || !equal(&savedFixture,&fixture,sizeof fixture)) return false;
    }
    return true;
}
extern "C" int test_main() {
    if(!run(0,0,0,0,0)) return 1;
    for(unsigned alias=0;alias<2;++alias) {
        if(!run(1,0,alias,0,0)) return 2;
        for(unsigned i=0;i<N;++i) {
            if(!run(2,i,alias,0,0)) return 3;
            for(unsigned m=1;m<=2;++m) if(!run(1,0,alias,m,i)) return 4;
        }
        for(unsigned i=0;i<256;++i) if(!run(3,i,alias,0,0)) return 5;
    }
    test_write("device-destroy differential tests passed\n",41);
    return 0;
}
