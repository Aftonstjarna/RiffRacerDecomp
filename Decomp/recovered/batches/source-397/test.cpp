#include "impl.hpp"
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_append_range(NarrowString*,const char*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
static unsigned prepares,aliases,copies,seen_size,seen_offset,seen_count;
static NarrowString *seen_this;
static const NarrowString *seen_source;
static bool allow_prepare, relocate;
static char relocated[128];
static NarrowString sentinel; // Static lifetime avoids dangling callback state.
static void fill(void* p,unsigned n,unsigned seed) { unsigned char* d=(unsigned char*)p; for(unsigned i=0;i<n;++i)d[i]=(unsigned char)(seed+i*37); }
static void copy(void* p,const void* q,unsigned n) { unsigned char* d=(unsigned char*)p; const unsigned char* s=(const unsigned char*)q;for(unsigned i=0;i<n;++i)d[i]=s[i]; }
static bool equal(const void* p,const void* q,unsigned n) { const unsigned char* a=(const unsigned char*)p;const unsigned char* b=(const unsigned char*)q;for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;return true; }
NarrowString* RIFF_THISCALL NarrowString::append_substring(const NarrowString* s,uint32_t o,uint32_t n) {
    ++aliases;seen_this=this;seen_source=s;seen_offset=o;seen_count=n;return &sentinel;
}
bool RIFF_THISCALL NarrowString::prepare_append(uint32_t n,bool trim) {
    ++prepares;seen_this=this;seen_size=n;
    if(trim) return false;
    if(relocate) { copy(relocated,capacity>=16?storage.heap:storage.local,length); storage.heap=relocated;capacity=127; }
    return allow_prepare;
}
void* narrow_copy(void* d,const void* s,uint32_t n) { ++copies;copy(d,s,n);return d; }
RIFF_NORETURN void narrow_length_error(const char*) { __builtin_trap(); }
struct Guarded { unsigned before[4]; NarrowString s; unsigned after[4]; };
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"i386 layout");
    unsigned fs[8]={0xffffffffu,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    const unsigned head=fs[0];
    // Real original comparisons: zero count bypasses missing helpers only for
    // null, external, terminator or unused-capacity source addresses.
    for(unsigned mode=0;mode<2;++mode) for(unsigned n=0;n<(mode?64u:16u);++n)
    for(unsigned kind=0;kind<4;++kind) {
        Guarded a,b,sa,sb; char ha[128],hb[128],sha[128],shb[128];
        fill(&a,sizeof(a),n+17);copy(&b,&a,sizeof(a));fill(ha,128,n);copy(hb,ha,128);
        a.s.length=b.s.length=n;a.s.capacity=b.s.capacity=mode?127:15;
        if(mode){a.s.storage.heap=ha;b.s.storage.heap=hb;}
        char* da=mode?ha:a.s.storage.local;char* db=mode?hb:b.s.storage.local;
        // Deliberately nonzero end bytes prove no terminator is rewritten.
        const char external[3]={'a',0,'b'};
        const char* pa=kind==0?0:kind==1?external:da+(kind==2?n:(mode?127:15));
        const char* pb=kind==0?0:kind==1?external:db+(kind==2?n:(mode?127:15));
        copy(&sa,&a,sizeof(a));copy(&sb,&b,sizeof(b));copy(sha,ha,128);copy(shb,hb,128);
        if(a.s.append_range(pa,0)!=&a.s) return 2;
        if(original_narrow_append_range(&b.s,pb,0)!=&b.s) return 3;
        if(test_get_fs_head()!=head) return 4;
        if(!equal(&a,&sa,sizeof(a))||!equal(&b,&sb,sizeof(b))||!equal(ha,sha,128)||!equal(hb,shb,128))return 5;
    }
    // Source-only dependency checks: no claim these execute missing originals.
    for(unsigned mode=0;mode<2;++mode) for(unsigned n=1;n<(mode?64u:16u);++n)
    for(unsigned off=0;off<n;++off) for(unsigned c=0;c<3;++c) {
        Guarded a,saved;char heap[128];fill(&a,sizeof(a),n);fill(heap,128,off);
        a.s.length=n;a.s.capacity=mode?127:15;if(mode)a.s.storage.heap=heap;
        copy(&saved,&a,sizeof(a));aliases=prepares=copies=0;
        unsigned count=c==0?0:c==1?1:0xffffffffu;
        if(a.s.append_range((mode?heap:a.s.storage.local)+off,count)!=&sentinel)return 6;
        if(aliases!=1||prepares||copies||seen_this!=&a.s||seen_source!=&a.s||seen_offset!=off||seen_count!=count)return 7;
        if(!equal(&a,&saved,sizeof(a)))return 8;
    }
    for(unsigned mode=0;mode<2;++mode) for(unsigned n=0;n<8;++n)
    for(unsigned count=1;count<=7;++count) for(unsigned action=0;action<3;++action) {
        Guarded a,expected;char heap[128],saved_heap[128],text[8],saved_local[16],expected_relocated[128];
        fill(&a,sizeof(a),n);fill(heap,128,n);fill(text,8,101);
        a.s.length=n;a.s.capacity=mode?127:15;if(mode)a.s.storage.heap=heap;
        copy(&expected,&a,sizeof(a));copy(saved_heap,heap,128);copy(saved_local,a.s.storage.local,16);
        fill(relocated,128,77);copy(expected_relocated,relocated,128);
        aliases=prepares=copies=0;allow_prepare=action!=0;relocate=action==2;
        if(a.s.append_range(text,count)!=&a.s)return 9;
        if(prepares!=1||aliases||copies!=(allow_prepare?1u:0u)||seen_this!=&a.s||seen_size!=n+count)return 10;
        if(!allow_prepare) {if(!equal(&a,&expected,sizeof(a))||!equal(heap,saved_heap,128))return 11;continue;}
        if(relocate){expected.s.storage.heap=relocated;expected.s.capacity=127;}
        expected.s.length=n+count;
        char* actual=relocate?relocated:mode?heap:a.s.storage.local;
        const char* old=mode?saved_heap:saved_local;
        for(unsigned i=0;i<n;++i)if(actual[i]!=old[i])return 12;
        if(!equal(actual+n,text,count)||actual[n+count]!=0)return 13;
        if(!mode&&!relocate){copy(expected.s.storage.local+n,text,count);expected.s.storage.local[n+count]=0;}
        if(!equal(&a,&expected,sizeof(a)))return 14;
        if(mode&&!relocate){copy(saved_heap+n,text,count);saved_heap[n+count]=0;}
        if(!equal(heap,saved_heap,128))return 15;
        if(relocate){copy(expected_relocated,mode?saved_heap:saved_local,n);copy(expected_relocated+n,text,count);expected_relocated[n+count]=0;}
        if(!equal(relocated,expected_relocated,128))return 16;
    }
    const char msg[]="320 original zero-count comparisons and dependency checks passed\n";
    test_write(msg,sizeof(msg)-1);return 0;
}
