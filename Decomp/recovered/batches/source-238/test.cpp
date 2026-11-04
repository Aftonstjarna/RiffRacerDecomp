#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_worker_destroy(Worker*);
static Worker* active;
static uint32_t expected_handle;
static uint32_t calls;
static int callback_result;
static int callback_error;
extern "C" int RIFF_STDCALL CloseHandle(void* handle) {
    ++calls;
    if (static_cast<uint32_t>(reinterpret_cast<uintptr_t>(handle)) != expected_handle ||
        active->vtable != 0x009FBE20u || active->handle != expected_handle)
        callback_error = 1;
    return callback_result;
}
typedef int (RIFF_STDCALL *CloseCallback)(void*);
extern "C" {
CloseCallback worker_handle_iat
    __attribute__((section(".worker_iat_handle"),used,aligned(4))) = CloseHandle;
}
struct Guarded {
    uint32_t before[2];
    Worker worker;
    uint32_t after[4];
};
static bool same(const Guarded& a, const Guarded& b) {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* q = reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0; i<sizeof(a); ++i) if(p[i]!=q[i]) return false;
    return true;
}
extern "C" int test_main() {
    const uint32_t handles[] = {0u,1u,0x12345678u,0x80000000u,0xFFFFFFFEu,0xFFFFFFFFu};
    const uint32_t tables[] = {0u,0x009FBE20u,0xDEADBEEFu};
    const int results[] = {0,1,-1};
    worker_handle_iat = CloseHandle;
    for (unsigned h=0; h<6; ++h) for(unsigned t=0; t<3; ++t)
    for(unsigned r=0; r<3; ++r) {
        Guarded recovered = {{0x11223344u,0x55667788u},
            {tables[t],0x87654321u,handles[h],0xA5A5A5A5u},
            {0xABCDEF01u,0x98765432u,0x13579BDFu,0x2468ACE0u}};
        Guarded original = recovered;
        Guarded expected = recovered;
        expected.worker.vtable = 0x009FBE20u;
        expected_handle=handles[h]; callback_result=results[r];
        // Repeated cleanup also calls CloseHandle again with unchanged handle.
        for(unsigned repeat=0; repeat<2; ++repeat) {
            calls=0; callback_error=0; active=&recovered.worker;
            recovered.worker.destroy();
            if(calls!=1 || callback_error || !same(recovered,expected)) return 1;
            calls=0; callback_error=0; active=&original.worker;
            original_worker_destroy(&original.worker);
            if(calls!=1 || callback_error || !same(original,expected)) return 2;
            if(!same(recovered,original)) return 3;
        }
    }
    return 0;
}
