#include "impl.hpp"
#include <stddef.h>
extern "C" int __attribute__((thiscall)) original_script_stream_refill(ScriptStream*);
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(ScriptStream)==20, "i386 stream size");
static_assert(offsetof(ScriptStream,cursor)==4 && offsetof(ScriptStream,reader)==8 && offsetof(ScriptStream,data)==12 && offsetof(ScriptStream,state)==16, "original layout");
struct Fixture {
    ScriptStream stream;
    uint32_t guard;
};
struct Context {
    Fixture* owner;
    const unsigned char* result;
    uint32_t length;
    unsigned calls;
    bool mutate;
    bool writeLength;
    bool bad;
};
static unsigned char bytes[258];
static int stateToken, replacementToken;
static const unsigned char* RIFF_CDECL readBlock(void* state, void* data, uint32_t* length) {
    Context* c = static_cast<Context*>(data);
    ++c->calls;
    if (state != &stateToken || !length) c->bad = true;
    if (c->writeLength) *length = c->length;
    if (c->mutate) {
        c->owner->stream.remaining = 0xaabbccddu;
        c->owner->stream.cursor = bytes + 257;
        c->owner->stream.data = &replacementToken;
        c->owner->stream.state = &replacementToken;
    }
    return c->result;
}
static bool run(uint32_t oldCount, uint32_t length, bool nonnull, unsigned byte, bool mutate, bool writeLength) {
    Fixture a = {}, b = {};
    Context ca = {&a, nonnull ? bytes + byte : 0, length, 0, mutate, writeLength, false};
    Context cb = {&b, nonnull ? bytes + byte : 0, length, 0, mutate, writeLength, false};
    a.stream.remaining = b.stream.remaining = oldCount;
    a.stream.cursor = b.stream.cursor = bytes + 256;
    a.stream.reader = b.stream.reader = readBlock;
    a.stream.data = &ca; b.stream.data = &cb;
    a.stream.state = b.stream.state = &stateToken;
    a.guard = b.guard = 0x73516a92;
    int expected = original_script_stream_refill(&a.stream);
    int actual = b.stream.refill();
    bool success = nonnull && length != 0;
    if (actual != expected || actual != (success ? int(bytes[byte]) : -1)) return false;
    uint32_t count = success ? length-1 : (mutate ? 0xaabbccddu : oldCount);
    const unsigned char* cursor = success ? bytes+byte+1 : (mutate ? bytes+257 : bytes+256);
    if (a.stream.remaining != count || b.stream.remaining != count || a.stream.cursor != cursor || b.stream.cursor != cursor) return false;
    if (a.stream.reader != readBlock || b.stream.reader != readBlock) return false;
    if (a.stream.data != (mutate ? static_cast<void*>(&replacementToken) : &ca) || b.stream.data != (mutate ? static_cast<void*>(&replacementToken) : &cb)) return false;
    if (a.stream.state != (mutate ? &replacementToken : &stateToken) || a.stream.state != b.stream.state) return false;
    return a.guard == 0x73516a92 && b.guard == a.guard && ca.calls == 1 && cb.calls == 1 && !ca.bad && !cb.bad;
}
extern "C" int test_main() {
    for (unsigned i=0; i<258; ++i) bytes[i]=static_cast<unsigned char>(i);
    const uint32_t counts[] = {0,1,17,0xffffffffu};
    const uint32_t lengths[] = {0,1,2,257,0x80000000u,0xffffffffu};
    for (unsigned c=0;c<4;++c)
        for (unsigned l=0;l<6;++l)
            for (unsigned m=0;m<2;++m)
                for (unsigned n=0;n<2;++n)
                    if (!run(counts[c],lengths[l],n!=0,128,m!=0,true)) return 1;
    for (unsigned i=0;i<256;++i)
        if (!run(0xffffffffu,1,true,i,false,true)) return 2;
    // A null result short-circuits the uninitialized length, as in the original.
    if (!run(19,0,false,0,false,false)) return 3;
    test_write("script-stream-refill: passed\n",29);
    return 0;
}
