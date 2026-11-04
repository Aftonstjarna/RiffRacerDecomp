#include "impl.hpp"
extern "C" DecodeWorker* __attribute__((thiscall)) original_decode_worker_ctor(DecodeWorker*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
// Exactly one 4096-byte fixture: slots are offsets from 0x92d000.
unsigned char oracle_iat[4096] __attribute__((section(".oracle_iat"),used,aligned(4)));
static const unsigned N=0x180, PREFIX=16;
alignas(4) static unsigned char actual[N], expected[N];
static DecodeWorker* worker;
static unsigned stage, failures, mode, event_variant, write_id;
static uint32_t handle;
static void check(bool ok) { if (!ok) ++failures; }
static void put(unsigned off, uint32_t x) {
    for (unsigned i=0;i<4;++i) expected[PREFIX+off+i]=static_cast<unsigned char>(x>>(8*i));
}
static void compare() { for (unsigned i=0;i<N;++i) check(actual[i]==expected[i]); }
static uint32_t event_value(unsigned n) { return event_variant ? 0 : (n ? 0x87654321u : 0x12345678u); }
static uint32_t RR_STD event_callback(void* security,int manual,int initial,const char* name) {
    check(stage<2); compare();
    check(!security && !name && manual==static_cast<int>(stage) && initial==static_cast<int>(stage));
    uint32_t result=event_value(stage);
    put(stage ? 0x18 : 0x14,result);
    ++stage;
    return result;
}
static uint32_t RR_CDECL begin_callback(void* security,uint32_t stack,WorkerEntry entry,void* arg,uint32_t flags,uint32_t* id) {
    check(stage==2); compare();
    check(!security && !stack && !flags);
    check(reinterpret_cast<uintptr_t>(entry)==0x48dc50 && arg==worker && id==&worker->thread_id);
    // Model synchronous callback-visible writes, not actual thread execution.
    // This demonstrates priority is read after _beginthreadex returns.
    worker->priority_mode=mode;
    put(4,mode);
    if (write_id) { *id=0xfedcba98u; put(0xc,0xfedcba98u); }
    put(8,handle);
    ++stage;
    return handle;
}
static int RR_STD priority_callback(uint32_t h,int priority) {
    check(stage==3); compare(); check(h==handle);
    check(priority==(mode==0 ? -1 : mode==2 ? 1 : 0));
    ++stage;
    return 0; // original ignores failure
}
static void initialize_expected() {
    put(0,0x9fbdf0); put(4,1); put(8,0); put(0xc,0);
    expected[PREFIX+0x10]=0; expected[PREFIX+0x1c]=0;
    expected[PREFIX+0x20]=0; put(0x30,0); put(0x34,15);
    for (unsigned off=0x38;off<=0x48;off+=4) put(off,0);
    expected[PREFIX+0x4c]=0; expected[PREFIX+0x14c]=0;
}
extern "C" int test_main() {
    uint32_t fs_storage[8]={0x13579bdf,0,0,0,0,0,0,0};
    if (test_install_fs(fs_storage)!=0) return 1;
    *reinterpret_cast<CreateEventFunction*>(oracle_iat+0x114)=event_callback;
    *reinterpret_cast<BeginThreadFunction*>(oracle_iat+0x37c)=begin_callback;
    *reinterpret_cast<SetPriorityFunction*>(oracle_iat+0xd8)=priority_callback;
    const uint32_t handles[]={0,1,0x80000000u,0xffffffffu};
    const uint32_t modes[]={0,1,2,3,0x80000000u,0xffffffffu};
    unsigned cases=0;
    for (unsigned seed=0;seed<3;++seed)
    for (unsigned h=0;h<4;++h)
    for (unsigned m=0;m<6;++m)
    for (event_variant=0;event_variant<2;++event_variant)
    for (write_id=0;write_id<2;++write_id) {
        handle=handles[h]; mode=modes[m];
        for (unsigned implementation=0;implementation<2;++implementation) {
            for (unsigned i=0;i<N;++i) actual[i]=expected[i]=static_cast<unsigned char>(seed==0 ? 0 : seed==1 ? 255 : i*37+11);
            worker=reinterpret_cast<DecodeWorker*>(actual+PREFIX);
            initialize_expected(); stage=0;
            DecodeWorker* result=implementation ? worker->initialize() : original_decode_worker_ctor(worker);
            check(result==worker); compare();
            check(stage==(handle==UINT32_MAX ? 3u : 4u));
            check(test_get_fs_head()==fs_storage[0]);
        }
        ++cases;
    }
    check(cases==288);
    if (failures) { test_write("FAIL\n",5); return 2; }
    test_write("PASS: 288 paired constructor cases\n",35);
    return 0;
}
