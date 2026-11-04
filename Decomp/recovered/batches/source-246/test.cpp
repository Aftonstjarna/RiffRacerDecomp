#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_member_cleanup(MemberCleanup*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
unsigned char oracle_iat[4096] __attribute__((section(".oracle_iat"),used,aligned(4)));
struct Event { uint32_t kind, arg, timeout; unsigned char state[0x60]; };
static Event events[6], expected_events[6];
static unsigned count, expected_count;
static uint32_t result;
alignas(4) static unsigned char object[0x60];
static unsigned char initial[0x60], expected[0x60];
static void copy(void* d, const void* s, unsigned n) {
    for(unsigned i=0;i<n;++i) static_cast<unsigned char*>(d)[i]=static_cast<const unsigned char*>(s)[i];
}
static bool equal(const void* a,const void* b,unsigned n) {
    for(unsigned i=0;i<n;++i) if(static_cast<const unsigned char*>(a)[i]!=static_cast<const unsigned char*>(b)[i]) return false;
    return true;
}
static void record(unsigned k,uint32_t a,uint32_t t=0) {
    if(count>=6) return;
    Event& e=events[count++]; e.kind=k;e.arg=a;e.timeout=t;copy(e.state,object,sizeof object);
}
static uint32_t RR_STDCALL wait_cb(uint32_t h,uint32_t t) {record(1,h,t);return result;}
static int32_t RR_STDCALL reset_cb(uint32_t h) {record(2,h);return static_cast<int32_t>(result);}
static int32_t RR_STDCALL set_cb(uint32_t h) {record(3,h);return static_cast<int32_t>(result);}
static int32_t RR_STDCALL close_cb(uint32_t h) {record(5,h);return static_cast<int32_t>(result);}
static void RR_CDECL delete_cb(void* p) {record(4,static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)));}
template<class T> static void bind(unsigned offset,T p) {copy(oracle_iat+offset,&p,4);}
extern "C" int test_main() {
    uint32_t fs_storage=0xffffffffu;
    if(test_install_fs(&fs_storage)!=0) return 1;
    bind(0x124,&wait_cb);bind(0x104,&reset_cb);bind(0x120,&set_cb);bind(0xd4,&close_cb);bind(0x4b0,&delete_cb);
    const uint32_t capacities[]={0,1,14,15,16,17,0x7fffffff,0x80000000u,0xffffffffu};
    const uint32_t values[]={0,1,0x80,0x102,0xffffffffu};
    for(unsigned c=0;c<9;++c) for(unsigned r=0;r<5;++r) for(unsigned seed=0;seed<8;++seed) {
        for(unsigned i=0;i<sizeof object;++i) object[i]=static_cast<unsigned char>(i*37+seed*19);
        MemberCleanup* m=reinterpret_cast<MemberCleanup*>(object);
        m->text_capacity=capacities[c];m->text_size=values[(r+1)%5];
        m->thread=values[r];m->idle_event=values[(r+2)%5];m->request_event=values[(r+3)%5];
        m->text.heap=values[(r+4)%5];result=values[r];copy(initial,object,sizeof object);
        count=0;original_member_cleanup(m);
        if(test_get_fs_head()!=fs_storage) return 2;
        expected_count=count;copy(expected_events,events,sizeof events);copy(expected,object,sizeof object);
        // Independent footprint and order checks supplement differential comparison.
        if(count!=(capacities[c]>=16?6u:5u)) return 3;
        if(events[0].kind!=1 || events[1].kind!=2 || events[2].kind!=3 || events[3].kind!=1 || events[count-1].kind!=5) return 4;
        if(events[0].timeout!=0xffffffffu || events[3].timeout!=0xffffffffu) return 5;
        for(unsigned i=0;i<sizeof object;++i) {
            bool changed=i<4 || i==0x1c || i==0x20 || (i>=0x30 && i<0x38);
            if(!changed && object[i]!=initial[i]) return 6;
        }
        if(m->vtable!=0x9fbe20 || m->stop!=1 || m->text_capacity!=15 || m->text_size || m->text.inline_bytes[0]) return 7;
        copy(object,initial,sizeof object);count=0;m->cleanup();
        if(test_get_fs_head()!=fs_storage) return 8;
        if(count!=expected_count || !equal(events,expected_events,count*sizeof(Event)) || !equal(object,expected,sizeof object)) return 9;
    }
    test_write("360 differential cases passed\n",30);return 0;
}
