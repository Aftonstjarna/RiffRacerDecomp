#include "impl.hpp"
using namespace riff;
extern "C" uint32_t __attribute__((thiscall)) original_script_callinfo_grow(State*);
extern "C" uint32_t __attribute__((regparm(3))) original_script_callinfo_resize(uint32_t,uint32_t,State*);
extern "C" void __attribute__((fastcall)) original_script_throw_status(State*,uint32_t);
struct Global { uint8_t pad[12]; uint32_t (*alloc)(void*,uint32_t,uint32_t,uint32_t); void* user; uint8_t pad14[48]; uint32_t total; uint8_t pad48[16]; uint32_t panic; };
static Global g;
static State* active;
static unsigned flags,calls,unexpected_errors;
static uint32_t seen_ptr,seen_old,seen_new;
static uint32_t allocate(void*,uint32_t p,uint32_t old_n,uint32_t new_n) {
    ++calls; seen_ptr=p;seen_old=old_n;seen_new=new_n;
    if(flags&1u)active->current+=49u;
    return (flags&2u)?0u:0x12345000u;
}
namespace riff {
void resize_callinfo(State* s,uint32_t n){original_script_callinfo_resize(0,n,s);}
void throw_status(State* s,uint32_t n){original_script_throw_status(s,n);}
void runtime_error(State*,const char*){++unexpected_errors;}
}
static void fill(void* p,unsigned n,uint8_t c){uint8_t* b=(uint8_t*)p;for(unsigned i=0;i<n;++i)b[i]=c;}
static bool equal(const void* a,const void* b,unsigned n){const uint8_t* x=(const uint8_t*)a;const uint8_t* y=(const uint8_t*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static int run(uint32_t n,uint32_t delta,unsigned f){
    State x;fill(&x,sizeof x,0xa5);fill(&g,sizeof g,0x5a);
    *reinterpret_cast<Global**>(reinterpret_cast<uint8_t*>(&x)+0x10)=&g;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(&x)+0x60)=0;
    g.alloc=allocate;g.user=0;g.total=0xfffffff0u;g.panic=0;
    x.records=0x23456000u;x.current=x.records+delta;x.capacity=n;
    State initial=x,expected=x;Global initial_g=g,expected_g=g;
    const bool high=n<0x80000000u&&n>20000u;
    if(high)reinterpret_cast<uint8_t*>(&expected)[6]=5;
    else {
        uint32_t count=n+n,base=(f&2u)?0u:0x12345000u;
        uint32_t d=delta+((f&1u)?49u:0u);
        int32_t sd=d<0x80000000u?static_cast<int32_t>(d):-static_cast<int32_t>(~d)-1;
        expected.records=base;expected.capacity=count;
        expected.current=base+static_cast<uint32_t>(sd/24)*24u;
        expected.last=base+(count-1u)*24u;
        expected_g.total+=count*24u-n*24u;
        if((f&2u)&&(count*24u!=0u))reinterpret_cast<uint8_t*>(&expected)[6]=4;
    }
    expected.current+=24u;
    flags=f;active=&x;calls=0;
    uint32_t result=original_script_callinfo_grow(&x);
    if(result!=expected.current||!equal(&x,&expected,sizeof x)||!equal(&g,&expected_g,sizeof g))return 1;
    if(calls!=(high?0u:1u))return 2;
    if(!high&&(seen_ptr!=initial.records||seen_old!=n*24u||seen_new!=(n+n)*24u))return 3;
    x=initial;g=initial_g;calls=0;unexpected_errors=0;
    result=x.grow();
    if(result!=expected.current||!equal(&x,&expected,sizeof x)||!equal(&g,&expected_g,sizeof g))return 4;
    if(calls!=(high?0u:1u)||unexpected_errors)return 5;
    if(!high&&(seen_ptr!=initial.records||seen_old!=n*24u||seen_new!=(n+n)*24u))return 6;
    return 0;
}
extern "C" int test_main(){
    const uint32_t ns[]={0,1,2,17,9999,10000,20001,40000,0x7fffffffu,0x80000000u,0x80000001u,0x80002710u};
    const uint32_t ds[]={0,24,48,23,25,0xffffffffu,0xffffffe7u,0x80000000u,0x7fffffffu,0xdcba9ff0u};
    for(unsigned i=0;i<sizeof(ns)/sizeof(ns[0]);++i)
        for(unsigned j=0;j<sizeof(ds)/sizeof(ds[0]);++j)
            for(unsigned f=0;f<4;++f){int r=run(ns[i],ds[j],f);if(r)return r;}
    return 0;
}
