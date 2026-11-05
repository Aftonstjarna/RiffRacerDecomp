#include "impl.hpp"
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_append_terminated(NarrowString*, const char*);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_append_range(NarrowString*, const char*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);

static bool capture;
static NarrowString* seen_this;
static const char* seen_text;
static uint32_t seen_count, calls;
static NarrowString return_sentinel;
// Test-only dependency adapter. Original nonempty range calls cannot be run:
// accepted range evidence calls unregistered growth/subrange helpers. Captured
// nonempty calls check the recovered wrapper only, never claim oracle parity.
NarrowString* RIFF_THISCALL NarrowString::append_range(const char* p, uint32_t n) {
    if (!capture) return original_narrow_append_range(this, p, n);
    seen_this = this; seen_text = p; seen_count = n; ++calls;
    return &return_sentinel;
}
static void fill(void* p, unsigned n, unsigned seed) {
    unsigned char* d = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) d[i] = static_cast<unsigned char>(seed+i*37);
}
static void copy(void* p, const void* q, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(p);
    const unsigned char* s = static_cast<const unsigned char*>(q);
    for (unsigned i=0; i<n; ++i) d[i]=s[i];
}
static bool equal(const void* p, const void* q, unsigned n) {
    const unsigned char* a = static_cast<const unsigned char*>(p);
    const unsigned char* b = static_cast<const unsigned char*>(q);
    for (unsigned i=0; i<n; ++i) if (a[i]!=b[i]) return false;
    return true;
}
struct Guarded { uint32_t before[4]; NarrowString value; uint32_t after[4]; };
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24, "original i386 layout");
    unsigned fs[8]; fill(fs,sizeof(fs),71); fs[0]=0xffffffffu;
    if (test_install_fs(fs)!=0) return 1;
    const unsigned head=fs[0];
    // Empty external and self-terminator inputs, inline and heap modes.
    // Every byte in objects, guard words and heap backing must remain untouched.
    for (unsigned mode=0;mode<2;++mode) {
        for (unsigned n=0;n<(mode ? 64u : 16u);++n) {
            for (unsigned alias=0;alias<2;++alias) {
                Guarded a,b,saved_a,saved_b;
                char ha[80],hb[80],saved_ha[80],saved_hb[80];
                fill(&a,sizeof(a),n+mode*17); copy(&b,&a,sizeof(a));
                fill(ha,sizeof(ha),n); copy(hb,ha,sizeof(ha));
                a.value.size=b.value.size=n;
                a.value.capacity=b.value.capacity=mode ? 79 : 15;
                if (mode) { a.value.storage.heap=ha; b.value.storage.heap=hb; ha[n]=hb[n]=0; }
                else { a.value.storage.local[n]=b.value.storage.local[n]=0; }
                copy(&saved_a,&a,sizeof(a)); copy(&saved_b,&b,sizeof(b));
                copy(saved_ha,ha,sizeof(ha)); copy(saved_hb,hb,sizeof(hb));
                const char empty[2]={0,'x'};
                const char* pa=alias ? (mode ? ha+n : a.value.storage.local+n) : empty;
                const char* pb=alias ? (mode ? hb+n : b.value.storage.local+n) : empty;
                capture=false;
                if (a.value.append_terminated(pa)!=&a.value) return 2;
                if (test_get_fs_head()!=head) return 3;
                if (original_narrow_append_terminated(&b.value,pb)!=&b.value) return 4;
                if (test_get_fs_head()!=head) return 5;
                if (!equal(&a,&saved_a,sizeof(a)) || !equal(&b,&saved_b,sizeof(b))) return 6;
                if (!equal(ha,saved_ha,sizeof(ha)) || !equal(hb,saved_hb,sizeof(hb))) return 7;
            }
        }
    }
    // Independent scan/forwarding checks, with tails after embedded NUL and
    // all byte values 1..255. Deliberately return a different object to check EAX.
    Guarded a,saved; fill(&a,sizeof(a),31); copy(&saved,&a,sizeof(a));
    char text[1026],before[1026];
    capture=true;
    for (unsigned n=0;n<=1024;++n) {
        for (unsigned i=0;i<sizeof(text);++i) text[i]=static_cast<char>(1+i%255);
        text[n]=0; copy(before,text,sizeof(text)); calls=0;
        if (a.value.append_terminated(text)!=&return_sentinel) return 8;
        if (calls!=1 || seen_this!=&a.value || seen_text!=text || seen_count!=n) return 9;
        if (!equal(&a,&saved,sizeof(a)) || !equal(text,before,sizeof(text))) return 10;
    }
    // Self-alias scan must also finish before the range dependency is entered.
    for (unsigned n=0;n<16;++n) {
        fill(&a,sizeof(a),9); a.value.size=n; a.value.capacity=15;
        for (unsigned i=0;i<n;++i) a.value.storage.local[i]='a';
        a.value.storage.local[n]=0; copy(&saved,&a,sizeof(a)); calls=0;
        if (a.value.append_terminated(a.value.storage.local)!=&return_sentinel) return 11;
        if (calls!=1 || seen_text!=a.value.storage.local || seen_count!=n || seen_this!=&a.value) return 12;
        if (!equal(&a,&saved,sizeof(a))) return 13;
    }
    const char message[]="160 empty oracle comparisons; 1041 forwarding checks passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
