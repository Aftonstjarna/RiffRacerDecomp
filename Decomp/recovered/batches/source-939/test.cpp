#include "impl.hpp"

extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fsStorage[16];
static bool fsFailure;
static const uint32_t fsSentinel = 0xffffffffu;

extern "C" uint32_t RIFF_CDECL original_audio_stream_commit_position(riff::AudioStream*);
extern "C" void RIFF_THISCALL original_audio_buffer_commit_consumed(riff::AudioBuffer*);

// Test-only binding of the unrecovered member dependency to accepted evidence.
// Both target implementations execute precisely the same original helper.
void RIFF_THISCALL riff::AudioBuffer::commitConsumed()
{
    original_audio_buffer_commit_consumed(this);
    if (test_get_fs_head() != fsSentinel) fsFailure = true;
}

struct Fixture {
    uint32_t leading[4];
    riff::AudioStream stream;
    uint32_t trailing[8];
    riff::AudioBlock nodes[4];
    unsigned char data[4][16];
};
static Fixture fixture;
static unsigned char input[sizeof(Fixture)];
static unsigned char expected[sizeof(Fixture)];

static void copy(unsigned char* dst, const unsigned char* src, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) dst[i] = src[i];
}
static bool equal(const unsigned char* a, const unsigned char* b, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) if (a[i] != b[i]) return false;
    return true;
}
static void setup(bool empty, bool zeroBlocks, uint32_t offset, uint32_t base)
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&fixture);
    for (unsigned i = 0; i < sizeof(fixture); ++i)
        bytes[i] = static_cast<unsigned char>(i * 37u + 0xa5u);
    riff::AudioBuffer& b = fixture.stream.buffer;
    for (unsigned i = 0; i < 4; ++i) {
        fixture.nodes[i].data = fixture.data[i];
        fixture.nodes[i].size = i == 0 ? 8 : (i == 1 ? 12 : 4);
        fixture.nodes[i].next = i < 2 ? &fixture.nodes[i+1] : 0;
    }
    if (zeroBlocks) {
        fixture.nodes[0].size = 0;
        fixture.nodes[1].size = 0;
    }
    b.head = empty ? 0 : &fixture.nodes[0];
    b.tail = empty ? 0 : &fixture.nodes[2];
    b.bufferedBytes = empty ? 0 : (zeroBlocks ? 4 : 24);
    b.position = offset;
    b.checkpoint = 0x12345678;
    b.committedBase = base;
    b.recycleLimit = 8; // Never reach unavailable original CRT free import.
    b.recycledCount = 1;
    b.recycled = &fixture.nodes[3];
}

static int runCase(bool empty, bool zeroBlocks, uint32_t offset, uint32_t base,
                   unsigned consumed, uint32_t removed)
{
    setup(empty, zeroBlocks, offset, base);
    copy(input, reinterpret_cast<unsigned char*>(&fixture), sizeof(fixture));
    const uint32_t oracle = original_audio_stream_commit_position(&fixture.stream);
    if (test_get_fs_head() != fsSentinel) return 15;
    const riff::AudioBuffer& b = fixture.stream.buffer;
    if (oracle != uint32_t(base + offset) || fixture.stream.committedPosition != oracle) return 1;
    if (b.position != uint32_t(offset - removed) || b.checkpoint != b.position) return 2;
    if (b.committedBase != uint32_t(base + removed)) return 3;
    if (b.bufferedBytes != uint32_t((empty ? 0 : (zeroBlocks ? 4 : 24)) - removed)) return 4;
    if (b.head != ((empty || consumed == 3) ? 0 : &fixture.nodes[consumed])) return 5;
    if (b.tail != ((empty || consumed == 3) ? 0 : &fixture.nodes[2])) return 6;
    if (b.recycledCount != 1 + consumed) return 7;
    if (b.recycled != &fixture.nodes[consumed ? consumed - 1 : 3]) return 8;
    for (unsigned i = 0; i < consumed; ++i)
        if (fixture.nodes[i].next != &fixture.nodes[i ? i-1 : 3]) return 9;
    copy(expected, reinterpret_cast<unsigned char*>(&fixture), sizeof(fixture));
    copy(reinterpret_cast<unsigned char*>(&fixture), input, sizeof(fixture));
    if (audio_stream_commit_position(&fixture.stream) != oracle) return 10;
    // Includes every opaque byte, guards, block headers/payloads and pointers.
    if (!equal(reinterpret_cast<unsigned char*>(&fixture), expected, sizeof(fixture))) return 11;
    if (audio_stream_commit_position(&fixture.stream) != oracle) return 12;
    if (!equal(reinterpret_cast<unsigned char*>(&fixture), expected, sizeof(fixture))) return 13;
    if (fsFailure) return 16;

    // Explicitly check bytes outside the helper's known writes and target store.
    const unsigned char* now = reinterpret_cast<const unsigned char*>(&fixture);
    const unsigned pos = offsetof(Fixture, stream) + offsetof(riff::AudioStream, committedPosition);
    const unsigned buf = offsetof(Fixture, stream) + offsetof(riff::AudioStream, buffer);
    const unsigned nodes = offsetof(Fixture, nodes);
    for (unsigned i = 0; i < sizeof(fixture); ++i) {
        bool changed = (i >= pos && i < pos+4);
        const unsigned offsets[] = {0, 4, 8, 12, 16, 20, 32, 36};
        for (unsigned k = 0; k < 8; ++k)
            if (i >= buf+offsets[k] && i < buf+offsets[k]+4) changed = true;
        for (unsigned k = 0; k < consumed; ++k)
            if (i >= nodes+k*16+12 && i < nodes+k*16+16) changed = true;
        if (!changed && now[i] != input[i]) return 14;
    }
    return 0;
}
extern "C" int test_main()
{
    fsStorage[0] = fsSentinel;
    if (test_install_fs(fsStorage) != 0) return 90;
    if (test_get_fs_head() != fsSentinel) return 91;
    const uint32_t offsets[] = {0, 7, 8, 19, 20, 23, 24, 30, 0x7fffffff, 0x80000000, 0xffffffff};
    const uint32_t bases[] = {0, 1000, 0x7fffffff, 0x80000000, 0xfffffff8, 0xffffffff};
    for (unsigned j = 0; j < sizeof(bases)/sizeof(bases[0]); ++j) {
        for (unsigned i = 0; i < sizeof(offsets)/sizeof(offsets[0]); ++i) {
            const uint32_t p = offsets[i];
            // Original dependency compares offsets and lengths as signed words.
            const unsigned n = p >= 0x80000000u ? 0 : (p >= 24 ? 3 : (p >= 20 ? 2 : (p >= 8 ? 1 : 0)));
            const uint32_t removed = n == 3 ? 24 : (n == 2 ? 20 : (n == 1 ? 8 : 0));
            int r = runCase(false, false, p, bases[j], n, removed);
            if (r) return r;
            r = runCase(true, false, p, bases[j], 0, 0);
            if (r) return 20+r;
        }
        int r = runCase(false, true, 0, bases[j], 2, 0);
        if (r) return 40+r;
        r = runCase(false, true, 4, bases[j], 3, 4);
        if (r) return 60+r;
    }
    return 0;
}
