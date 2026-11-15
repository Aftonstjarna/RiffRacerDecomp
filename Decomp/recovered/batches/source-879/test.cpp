#include "impl.hpp"
using namespace riff;
extern "C" uint32_t __attribute__((regparm(3))) original_script_callinfo_resize(uint32_t, uint32_t, State*);
extern "C" uint32_t __attribute__((regparm(3))) original_script_reallocate(uint32_t, uint32_t, State*, uint32_t, uint32_t);
struct Global { uint8_t pad[12]; uint32_t (*alloc)(void*,uint32_t,uint32_t,uint32_t); void* user; uint8_t pad14[48]; uint32_t total; uint8_t pad48[16]; uint32_t panic; };
struct Full { State s; uint8_t tail[0x70-sizeof(State)]; };
static Global g;
static State* active;
static uint32_t flags,calls,seen_ptr,seen_old,seen_new;
static uint32_t allocate(void*,uint32_t p,uint32_t old_n,uint32_t new_n) {
    ++calls;seen_ptr=p;seen_old=old_n;seen_new=new_n;
    if(flags&1) active->current+=49;
    return (flags&2)?0:0x12345000u;
}
static uint32_t reallocate(State* s,uint32_t p,uint32_t a,uint32_t b) {
    return original_script_reallocate(0,p,s,a,b);
}
static uint32_t unexpected(State*) { return 0; }
static Services services={reallocate,unexpected};
static void fill(void* p,unsigned n,unsigned c){uint8_t* b=(uint8_t*)p;for(unsigned i=0;i<n;++i)b[i]=static_cast<uint8_t>(c);}
static bool equal(const void* a,const void* b,unsigned n){const uint8_t* x=(const uint8_t*)a;const uint8_t* y=(const uint8_t*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static int run(uint32_t n,uint32_t old_n,uint32_t delta,uint32_t f) {
    Full x;fill(&x,sizeof x,0xa5);fill(&g,sizeof g,0x5a);
    // Known fields used by the accepted realloc helper: global +10,
    // error frame +60, status +6. Null panic permits normal failure return.
    *reinterpret_cast<Global**>(reinterpret_cast<uint8_t*>(&x)+0x10)=&g;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(&x)+0x60)=0;
    g.alloc=allocate;g.user=0;g.total=0xfffffff0u;g.panic=0;
    x.s.records=0x23456000u;x.s.current=x.s.records+delta;x.s.capacity=old_n;
    Full initial=x; Global initial_g=g; Full expected=x;
    flags=f;active=&x.s;calls=0;
    uint32_t result=original_script_callinfo_resize(0,n,&x.s);
    if(calls!=1||seen_ptr!=initial.s.records||seen_old!=old_n*24u||seen_new!=n*24u)return 1;
    uint32_t base=(f&2)?0:0x12345000u;
    uint32_t d=delta+((f&1)?49u:0u);
    int32_t sd=d<0x80000000u?static_cast<int32_t>(d):-static_cast<int32_t>(~d)-1;
    expected.s.records=base;expected.s.capacity=n;
    expected.s.current=base+static_cast<uint32_t>(sd/24)*24u;
    expected.s.last=base+(n-1u)*24u;
    if((f&2)&&(n*24u!=0))reinterpret_cast<uint8_t*>(&expected)[6]=4;
    Global expected_g=initial_g;expected_g.total+=n*24u-old_n*24u;
    if(result!=expected.s.last||!equal(&x,&expected,sizeof x)||!equal(&g,&expected_g,sizeof g))return 2;
    x=initial;g=initial_g;calls=0;
    result=x.s.resize_callinfo(n,services);
    if(calls!=1||seen_ptr!=initial.s.records||seen_old!=old_n*24u||seen_new!=n*24u)return 3;
    if(result!=expected.s.last||!equal(&x,&expected,sizeof x)||!equal(&g,&expected_g,sizeof g))return 4;
    return 0;
}
extern "C" int test_main(){
    const uint32_t ns[]={0,1,2,17,20000,0x0aaaaaa9u,0xffffffffu};
    const uint32_t ds[]={0,24,48,23,25,0xffffffffu,0xffffffe7u,0x80000000u,0x7fffffffu};
    for(unsigned i=0;i<7;++i)for(unsigned j=0;j<9;++j)for(unsigned f=0;f<4;++f){int r=run(ns[i],0xf1234567u,ds[j],f);if(r)return r;}
    return 0;
}
