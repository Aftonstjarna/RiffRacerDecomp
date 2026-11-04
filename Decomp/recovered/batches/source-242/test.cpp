#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_worker_start(riff::Worker*, bool);
extern "C" uint32_t __attribute__((stdcall)) original_worker_dispatch(void*);
extern "C" void test_write(const char*, unsigned);
extern "C" {
riff::BeginThread begin_iat __attribute__((section(".worker_iat_begin"),used,aligned(4))) = 0;
riff::SetPriority priority_iat __attribute__((section(".worker_iat_priority"),used,aligned(4))) = 0;
}
class Probe : public riff::Worker {
public:
    uint32_t guards[12];
    virtual Probe* RR_THISCALL deleting_wrapper(uint32_t) { return this; }
    virtual uint32_t RR_THISCALL run() { return 0; }
};
static Probe* current;
static uint32_t returned_handle, old_handle, old_id, new_id, flags_expected;
static uint32_t changed_mode;
static bool write_id, change_mode;
static int32_t priority_return;
static unsigned begin_calls, priority_calls, errors;
static uint32_t seen_handle;
static int32_t seen_priority;
static uint32_t RR_CDECL begin_callback(void* security, uint32_t stack,
        riff::ThreadEntry entry, void* arg, uint32_t flags, uint32_t* id) {
    ++begin_calls;
    if (security || stack || entry != original_worker_dispatch || arg != current ||
        flags != flags_expected || id != &current->thread_id ||
        current->handle != old_handle || current->thread_id != old_id || priority_calls)
        ++errors;
    if (write_id) *id = new_id;
    if (change_mode) current->priority_mode = changed_mode;
    return returned_handle;
}
static int32_t RR_STDCALL priority_callback(uint32_t handle, int32_t priority) {
    ++priority_calls;
    if (begin_calls != 1 || current->handle != returned_handle ||
        current->thread_id != (write_id ? new_id : old_id)) ++errors;
    seen_handle = handle;
    seen_priority = priority;
    return priority_return;
}
static void reset(Probe& p, uint32_t mode) {
    p.priority_mode = mode;
    p.handle = old_handle;
    p.thread_id = old_id;
    for (unsigned i=0;i<12;++i) p.guards[i] = 0xa5970301u + i * 0x11020304u;
    current = &p;
    begin_calls = priority_calls = errors = 0;
    seen_handle = 0xfeedfaceu;
    seen_priority = 42;
}
static bool verify(const Probe& p, bool result, uint32_t mode) {
    if (errors || begin_calls != 1 || result != (returned_handle != UINT32_MAX) ||
        priority_calls != (returned_handle != UINT32_MAX ? 1u : 0u) ||
        p.handle != returned_handle || p.thread_id != (write_id ? new_id : old_id) ||
        p.priority_mode != (change_mode ? changed_mode : mode)) return false;
    if (priority_calls) {
        uint32_t m = change_mode ? changed_mode : mode;
        int32_t priority = m == 0 ? -1 : m == 2 ? 1 : 0;
        if (seen_handle != returned_handle || seen_priority != priority) return false;
    }
    for (unsigned i=0;i<12;++i)
        if (p.guards[i] != 0xa5970301u + i * 0x11020304u) return false;
    return true;
}
static bool check(uint32_t mode, bool suspended) {
    Probe a,b;
    reset(a,mode);
    unsigned char before[sizeof(Probe)];
    for (unsigned i=0;i<sizeof(Probe);++i) before[i]=reinterpret_cast<unsigned char*>(&a)[i];
    bool ra=original_worker_start(&a,suspended);
    if (!verify(a,ra,mode)) return false;
    // Original must preserve vptr, all guard bytes, and any padding too.
    for (unsigned i=0;i<sizeof(Probe);++i)
        if ((i<4 || i>=16) && before[i]!=reinterpret_cast<unsigned char*>(&a)[i]) return false;
    uint32_t ah=seen_handle;
    int32_t ap=seen_priority;
    reset(b,mode);
    bool rb=b.start(suspended);
    if (!verify(b,rb,mode) || ra!=rb || ah!=seen_handle || ap!=seen_priority) return false;
    for (unsigned i=0;i<sizeof(Probe);++i)
        if (reinterpret_cast<unsigned char*>(&a)[i]!=reinterpret_cast<unsigned char*>(&b)[i]) return false;
    return true;
}
extern "C" int test_main() {
    begin_iat=begin_callback;
    priority_iat=priority_callback;
    riff::worker_services.begin=begin_callback;
    riff::worker_services.priority=priority_callback;
    riff::worker_services.entry=original_worker_dispatch;
    const uint32_t modes[]={0,1,2,3,0x7fffffffu,0x80000000u,0xffffffffu};
    const uint32_t handles[]={0xffffffffu,0,1,0x80000000u,0x13572468u};
    old_handle=0x87654321u; old_id=0x12345678u; new_id=0xfedcba98u;
    for (unsigned m=0;m<7;++m) for (unsigned h=0;h<5;++h)
    for (unsigned s=0;s<2;++s) for (unsigned options=0;options<8;++options) {
        returned_handle=handles[h]; flags_expected=s?4:0;
        write_id=(options&1)!=0; change_mode=(options&2)!=0;
        changed_mode=modes[(m+2)%7]; priority_return=(options&4)?0:-7;
        if (!check(modes[m],s!=0)) return 1;
    }
    test_write("worker-start: passed\n",21);
    return 0;
}
