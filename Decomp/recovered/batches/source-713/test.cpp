#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_stream_append_u16_be(Stream*, uint32_t);
extern "C" void test_write(const char*, unsigned);

static bool same(const void* x, const void* y, unsigned n) {
    const uint8_t* a = static_cast<const uint8_t*>(x);
    const uint8_t* b = static_cast<const uint8_t*>(y);
    for (unsigned i = 0; i < n; ++i) if (a[i] != b[i]) return false;
    return true;
}
static void fill(void* p, unsigned n, uint8_t value) {
    uint8_t* b = static_cast<uint8_t*>(p);
    for (unsigned i = 0; i < n; ++i) b[i] = value;
}
static bool ordinary(uint32_t value, unsigned start) {
    uint8_t a[80], b[80];
    fill(a, sizeof(a), 0xa5); fill(b, sizeof(b), 0xa5);
    Stream x, y;
    fill(&x, sizeof(x), 0x6b); fill(&y, sizeof(y), 0x6b);
    x.buffer = a; y.buffer = b; x.cursor = y.cursor = start;
    x.append_u16_be(value);
    original_stream_append_u16_be(&y, value);
    if (x.cursor != start + 2 || y.cursor != start + 2) return false;
    if (a[start] != static_cast<uint8_t>(value >> 8) || a[start+1] != static_cast<uint8_t>(value)) return false;
    if (!same(a,b,sizeof(a))) return false;
    // Normalize only the distinct backing-buffer addresses, then compare every
    // object byte, including opaque fields. Buffer itself must be untouched.
    if (x.buffer != a || y.buffer != b) return false;
    x.buffer = y.buffer;
    return same(&x,&y,sizeof(x));
}
struct AliasCase { Stream stream; uint8_t tail[300]; };
static bool alias_case(unsigned cursor, uint32_t value) {
    AliasCase a, b;
    fill(&a,sizeof(a),0x59); fill(&b,sizeof(b),0x59);
    a.stream.buffer = reinterpret_cast<uint8_t*>(&a);
    b.stream.buffer = reinterpret_cast<uint8_t*>(&b);
    a.stream.cursor = b.stream.cursor = cursor;
    a.stream.append_u16_be(value);
    original_stream_append_u16_be(&b.stream,value);
    if (a.stream.buffer != reinterpret_cast<uint8_t*>(&a) ||
        b.stream.buffer != reinterpret_cast<uint8_t*>(&b)) return false;
    a.stream.buffer = b.stream.buffer;
    return same(&a,&b,sizeof(a));
}
extern "C" int test_main() {
    static_assert(sizeof(void*) == 4, "oracle ABI requires i386");
    // Exhaust every possible output word; nonzero upper bits establish truncation.
    for (uint32_t v = 0; v < 65536; ++v) {
        if (!ordinary(v | 0xa53c0000u, v % 79)) return 1;
    }
    if (!ordinary(0,0) || !ordinary(0xffffffffu,78)) return 2;
    // Repeated appends verify cursor accumulation and exact adjacent output.
    uint8_t a[32], b[32]; fill(a,32,0xcd); fill(b,32,0xcd);
    Stream x = {}, y = {}; x.buffer=a; y.buffer=b;
    x.cursor=y.cursor=1;
    for (uint32_t i=0; i<12; ++i) {
        x.append_u16_be(i*0x1234u);
        original_stream_append_u16_be(&y,i*0x1234u);
        if (!same(a,b,32) || x.cursor != y.cursor) return 3;
    }
    // First byte overlaps cursor low byte: the second byte uses the changed
    // cursor. Also exercise its next byte, and otherwise opaque object words.
    if (!alias_case(20,0x001234u) || !alias_case(21,0x000056u) ||
        !alias_case(0,0xabcd) || !alias_case(24,0xdead)) return 4;
    static const char message[] = "stream-append-u16-be: passed\n";
    test_write(message, sizeof(message)-1);
    return 0;
}
