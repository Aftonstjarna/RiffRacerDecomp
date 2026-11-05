#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_minimum_caps(GraphicsDevice*, unsigned char*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned calls, bad;
static unsigned lengths[2];
static char messages[2][128];
static unsigned terminated;
static NarrowString* expected_member;
static unsigned text_length(const char* p) {
    unsigned n = 0;
    while (p[n]) { ++n; }
    return n;
}
static NarrowString* capture(NarrowString* s, const char* p, unsigned n) {
    if (s != expected_member) { bad = 1; }
    if (calls >= 2 || n >= 128) { bad = 1; return s; }
    lengths[calls] = n;
    for (unsigned i = 0; i < n; ++i) { messages[calls][i] = p[i]; }
    messages[calls][n] = 0;
    ++calls;
    return s;
}
NarrowString* RIFF_THISCALL NarrowString::assign_range(const char* p, uint32_t n) {
    if (calls != 0) { bad = 1; }
    return capture(this, p, n);
}
NarrowString* RIFF_THISCALL NarrowString::append_range(const char* p, uint32_t n) {
    if (calls != 1) { bad = 1; }
    return capture(this, p, n);
}
NarrowString* RIFF_THISCALL NarrowString::assign_terminated(const char* p) {
    terminated |= 1;
    return assign_range(p, text_length(p));
}
NarrowString* RIFF_THISCALL NarrowString::append_terminated(const char* p) {
    terminated |= 2;
    return append_range(p, text_length(p));
}
static void fill(void* p, unsigned n, unsigned char value) {
    unsigned char* d = static_cast<unsigned char*>(p);
    for (unsigned i = 0; i < n; ++i) { d[i] = value; }
}
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i = 0; i < n; ++i) { a[i] = b[i]; }
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i = 0; i < n; ++i) {
        if (x[i] != y[i]) { return false; }
    }
    return true;
}
struct Guarded { uint32_t before; GraphicsDevice device; uint32_t after; };
static void setup(Guarded& g, uint32_t vertex, uint32_t pixel, uint32_t caps,
                  uint32_t width, uint32_t height, uint32_t targets) {
    fill(&g, sizeof(g), 0xa5);
    g.device.vertex_shader_version = vertex;
    g.device.pixel_shader_version = pixel;
    g.device.texture_caps = caps;
    g.device.max_texture_width = width;
    g.device.max_texture_height = height;
    g.device.simultaneous_render_targets = targets;
}
static int success(uint32_t vertex, uint32_t pixel, uint32_t caps,
                   uint32_t width, uint32_t height, uint32_t targets, unsigned alias) {
    Guarded a, b, expected;
    setup(a, vertex, pixel, caps, width, height, targets);
    copy(&b, &a, sizeof(a));
    copy(&expected, &a, sizeof(a));
    unsigned char oa[3] = {0x37, 0xa5, 0x73};
    unsigned char ob[3] = {0x37, 0xa5, 0x73};
    unsigned char* pa = &oa[1];
    unsigned char* pb = &ob[1];
    unsigned char flag = vertex < 0xfffe0300u ? 1 : 0;
    if (alias) {
        pa = reinterpret_cast<unsigned char*>(&a.device.vertex_shader_version) + alias - 1;
        pb = reinterpret_cast<unsigned char*>(&b.device.vertex_shader_version) + alias - 1;
        reinterpret_cast<unsigned char*>(&expected.device.vertex_shader_version)[alias - 1] = flag;
    }
    calls = bad = terminated = 0;
    expected_member = &a.device.diagnostic;
    if (!a.device.minimum_caps(pa)) { return 20; }
    unsigned head = test_get_fs_head();
    if (!original_minimum_caps(&b.device, pb)) { return 21; }
    if (test_get_fs_head() != head) { return 22; }
    if (!equal(&a, &b, sizeof(a)) || !equal(&a, &expected, sizeof(a))) { return 23; }
    if (!equal(oa, ob, 3) || oa[0] != 0x37 || oa[2] != 0x73) { return 24; }
    if (!alias && oa[1] != flag) { return 25; }
    if (calls || bad || terminated) { return 26; }
    return 0;
}
// Failure tests inspect external member calls, not fabricated original helpers.
static int failure(uint32_t pixel, uint32_t caps, uint32_t width, uint32_t height,
                   uint32_t targets, const char* reason, unsigned n, bool wrappers) {
    Guarded a, before;
    setup(a, 0xfffe02ffu, pixel, caps, width, height, targets);
    copy(&before, &a, sizeof(a));
    calls = bad = terminated = 0;
    expected_member = &a.device.diagnostic;
    unsigned char out[3] = {0x37, 0xa5, 0x73};
    if (a.device.minimum_caps(&out[1])) { return 30; }
    if (out[0] != 0x37 || out[1] != 1 || out[2] != 0x73) { return 31; }
    if (!equal(&a, &before, sizeof(a))) { return 32; }
    const char* prefix = "Graphics card does not meet minimum system requirements.\n\n";
    if (bad || calls != 2 || lengths[0] != 58 || lengths[1] != n) { return 33; }
    if (!equal(messages[0], prefix, 59) || !equal(messages[1], reason, n + 1)) { return 34; }
    if (terminated != (wrappers ? 3u : 0u)) { return 35; }
    return 0;
}
extern "C" int test_main() {
    unsigned fs[64];
    fill(fs, sizeof(fs), 0);
    fs[0] = 0x13579bdf;
    if (test_install_fs(fs) != 0) { return 10; }
    if (test_get_fs_head() != fs[0]) { return 11; }
    const uint32_t vertices[] = {0, 0x7fffffff, 0xfffe02ff, 0xfffe0300, 0xfffe0301, 0xffffffff};
    const uint32_t pixels[] = {0xffff0300, 0xffff0301, 0xffffffff};
    const uint32_t caps[] = {0, 0x100, 0x102, 0xffffffdf};
    const uint32_t sizes[] = {4096, 4097, 0x80000000, 0xffffffff};
    const uint32_t targets[] = {3, 4, 0x80000000, 0xffffffff};
    for (unsigned v = 0; v < 6; ++v) {
        for (unsigned p = 0; p < 3; ++p) {
            for (unsigned c = 0; c < 4; ++c) {
                for (unsigned w = 0; w < 4; ++w) {
                    for (unsigned h = 0; h < 4; ++h) {
                        for (unsigned t = 0; t < 4; ++t) {
                            int r = success(vertices[v], pixels[p], caps[c], sizes[w], sizes[h], targets[t], 0);
                            if (r) { return r; }
                        }
                    }
                }
            }
        }
        for (unsigned alias = 1; alias <= 4; ++alias) {
            int r = success(vertices[v], 0xffff0300, 0, 4096, 4096, 3, alias);
            if (r) { return r; }
        }
    }
    const uint32_t low[] = {0, 1, 0x7fffffff, 0xffff02ff};
    for (unsigned i = 0; i < 4; ++i) {
        int r = failure(low[i], 0x22, 0, 0, 0, "Pixel Shader v3.0 is required.", 30, false);
        if (r) { return r; }
    }
    int r = failure(0xffff0300, 0x22, 0, 0, 0, "NP2 texture support is required.", 32, false);
    if (r) { return r; }
    r = failure(0xffffffff, 0x122, 0, 0, 0, "Non-square texture support is required.", 39, false);
    if (r) { return r; }
    const uint32_t small[] = {0, 1, 4095};
    for (unsigned i = 0; i < 3; ++i) {
        r = failure(0xffff0300, 0x102, small[i], 4096, 0, "4096x4096 textures required", 27, false);
        if (r) { return r; }
        r = failure(0xffff0300, 0, 4096, small[i], 0, "4096x4096 textures required", 27, false);
        if (r) { return r; }
        r = failure(0xffff0300, 0, 4096, 4096, i, "At least 3 simultaneous render targers are required.", 52, true);
        if (r) { return r; }
    }
    test_write("minimum-caps partial-oracle checks passed\n", sizeof("minimum-caps partial-oracle checks passed\n") - 1);
    return 0;
}
