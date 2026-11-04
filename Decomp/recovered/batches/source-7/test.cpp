#include "impl.hpp"
using namespace riff;
extern "C" bool __attribute__((thiscall)) original_save_device_close(SaveDevicePrefix*);
extern "C" void test_write(const char*, unsigned);
// Test-only ELF data, not recovered game data. A local verification link places
// this at the actual Windows import address. No executable bytes are supplied.
CloseStream oracle_import __attribute__((section(".oracle_import"), aligned(4))) = nullptr;
struct Guarded {
    unsigned before[4];
    SaveDevicePrefix device;
    unsigned after[16];
};
static SaveDevicePrefix* observed;
static void* expected_stream;
static unsigned calls, error;
static int close_result;
static bool mutate;
static int __attribute__((cdecl)) close_spy(void* stream) {
    ++calls;
    if (stream != expected_stream || observed->state != 0 ||
        observed->stream != expected_stream) error = 1;
    // Verify post-call stream clearing and absence of a second state write.
    if (mutate) {
        observed->state = 0x12345678;
        observed->stream = reinterpret_cast<void*>(0x87654320u);
    }
    return close_result;
}
static void init(Guarded& value, unsigned state, unsigned stream) {
    auto* bytes = reinterpret_cast<unsigned char*>(&value);
    for (unsigned i=0; i<sizeof(value); ++i) bytes[i] = (i*37+91)&255;
    value.device.state = state;
    value.device.stream = reinterpret_cast<void*>(stream);
}
static bool equal(const Guarded& a, const Guarded& b) {
    auto* x = reinterpret_cast<const unsigned char*>(&a);
    auto* y = reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
static bool run_case(unsigned state, unsigned stream, bool reference) {
    Guarded actual, expected;
    init(actual,state,stream); init(expected,state,stream);
    if(stream) {
        expected.device.state = mutate ? 0x12345678 : 0;
        expected.device.stream = nullptr;
    }
    observed=&actual.device; expected_stream=reinterpret_cast<void*>(stream);
    calls=error=0;
    bool result = reference ? original_save_device_close(&actual.device)
                            : save_device_close(&actual.device,close_spy);
    if(!result || error || calls != (stream ? 1u : 0u) || !equal(actual,expected)) return false;
    // Closing again must preserve the entire resulting object, including +0xC.
    calls=0;
    result = reference ? original_save_device_close(&actual.device)
                       : save_device_close(&actual.device,close_spy);
    return result && !calls && equal(actual,expected);
}
extern "C" int test_main() {
    const bool mapped = reinterpret_cast<unsigned>(&oracle_import)==0x92d470u;
    oracle_import=close_spy;
    const unsigned states[]={0,1,0xffffffffu,0x80000000u,0x12345678u};
    const unsigned streams[]={0,1,0x10203040u,0xffffffffu};
    const int results[]={0,-1,1,0x7fffffff,(-2147483647-1)};
    for(unsigned state:states) for(unsigned stream:streams)
        for(int r:results) for(unsigned m=0;m<2;++m) {
            close_result=r; mutate=m!=0;
            if(!run_case(state,stream,false)) return 1;
            if((!stream || mapped) && !run_case(state,stream,true)) return 2;
        }
    if(mapped) test_write("PASS: full original comparison\n",31);
    else test_write("PASS: null original; nonnull C++ only (IAT not mapped)\n",55);
    return 0;
}
