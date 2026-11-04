#include "impl.hpp"
#include <stddef.h>
using recovered::Worker;
extern "C" Worker* __attribute__((thiscall)) original_worker_delete(Worker*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static Worker* active;
static unsigned calls, errors, delete_calls;
static uint32_t expected_handle;
static int32_t close_result;
static bool mutate;
static int32_t WORKER_STDCALL on_close(uint32_t handle) {
    if (calls++ != 0 || handle != expected_handle || active->vtable_address != 0x9fbe20u)
        ++errors;
    if (mutate) { active->vtable_address = 0x12345678u; active->handle = 0x87654321u; }
    return close_result;
}
static void WORKER_CDECL on_delete(void* p) {
    if (calls++ != 1 || p != active || active->vtable_address != (mutate ? 0x12345678u : 0x9fbe20u))
        ++errors;
    ++delete_calls;
}
extern "C" {
recovered::CloseHandleImport oracle_close __attribute__((section(".worker_iat_handle"),used,aligned(4))) = on_close;
recovered::DeleteImport oracle_delete __attribute__((section(".worker_iat_delete"),used,aligned(4))) = on_delete;
}
struct Fixture { uint32_t before[2]; Worker worker; uint32_t after[4]; };
static void initialize(Fixture& f) {
    f.before[0]=0xaabbccddu; f.before[1]=0x11223344u;
    f.worker.vtable_address=0xcafebabeu; f.worker.priority=0xfedcba98u;
    f.worker.handle=expected_handle; f.worker.thread_id=0xabcdef01u;
    for (unsigned i=0;i<4;++i) f.after[i]=0x10203040u+i;
}
static bool equal(const Fixture& a,const Fixture& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    static_assert(sizeof(Worker)==16,"32-bit original layout");
    static_assert(offsetof(Worker,handle)==8,"handle offset");
    recovered::close_handle=on_close; recovered::delete_storage=on_delete;
    oracle_close=on_close; oracle_delete=on_delete;
    const uint32_t handles[]={0,1,0xffffffffu,0x80000000u,0x12345678u};
    for(unsigned h=0;h<5;++h) for(unsigned flag=0;flag<256;++flag)
    for(unsigned mode=0;mode<4;++mode) {
        expected_handle=handles[h]; close_result=(mode&1)?0:-1; mutate=(mode&2)!=0;
        // High bits are irrelevant: original tests only bit 0 of the stack byte.
        const uint32_t flags=flag | ((flag&2)?0xffffff00u:0u);
        Fixture a,b,expected; initialize(a); initialize(b); initialize(expected);
        expected.worker.vtable_address=mutate?0x12345678u:0x9fbe20u;
        if(mutate) expected.worker.handle=0x87654321u;
        calls=delete_calls=errors=0; active=&a.worker;
        Worker* result=original_worker_delete(active,flags);
        if(result!=active || errors || calls!=1+(flags&1) || delete_calls!=(flags&1)) return 1;
        calls=delete_calls=errors=0; active=&b.worker;
        result=active->scalar_delete(flags);
        if(result!=active || errors || calls!=1+(flags&1) || delete_calls!=(flags&1)) return 2;
        if(!equal(a,b) || !equal(a,expected)) return 3;
    }
    test_write("worker-delete: 5120 comparisons passed\n",39);
    return 0;
}
