#include "impl.hpp"
// regparm(3) maps the unused argument to EAX, last to EDX, first to
// ECX, and destination to a caller-cleaned stack slot. Fastcall would
// incorrectly assume that the original's plain RET pops that slot.
extern "C" U32Vector* __attribute__((regparm(3)))
original_nested_vector12_range_assign(unsigned unused, const U32Vector* last,
                                     const U32Vector* first, U32Vector* destination);
extern "C" U32Vector* __attribute__((thiscall))
original_u32_vector_copy_assign(U32Vector*, const U32Vector*);
U32Vector& U32Vector::assign(const U32Vector& source) {
    return *original_u32_vector_copy_assign(this, &source);
}
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];
struct Fixture {
    unsigned before;
    U32Vector records[8];
    unsigned after;
    uint32_t words[8][6];
};
static void initialize(Fixture& f, bool empty) {
    f.before=0x13579bdf; f.after=0xfdb97531;
    for(unsigned i=0;i<8;++i) {
        for(unsigned j=0;j<6;++j) f.words[i][j]=100*i+j;
        f.records[i].begin=f.words[i];
        f.records[i].end=f.words[i]+(empty ? 0 : (i%6));
        f.records[i].capacity_end=f.words[i]+6;
    }
}
static bool equal(const Fixture& a,const Fixture& b) {
    if(a.before!=b.before || a.after!=b.after) return false;
    for(unsigned i=0;i<8;++i) {
        if(a.records[i].begin!=a.words[i] || b.records[i].begin!=b.words[i]) return false;
        if(a.records[i].end-a.words[i]!=b.records[i].end-b.words[i]) return false;
        if(a.records[i].capacity_end!=a.words[i]+6 || b.records[i].capacity_end!=b.words[i]+6) return false;
        for(unsigned j=0;j<6;++j) if(a.words[i][j]!=b.words[i][j] || a.words[i][j]!=100*i+j) return false;
    }
    return a.before==0x13579bdf && a.after==0xfdb97531;
}
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0) return 1;
    // Empty range must not dereference even null pointers.
    if(original_nested_vector12_range_assign(0,0,0,0)!=0) return 2;
    if(test_get_fs_head()!=fs_storage[0]) return 3;
    if(nested_vector12_range_assign(0,0,0)!=0) return 4;
    for(unsigned count=0;count<=8;++count) {
        Fixture a,b;
        initialize(a,false); initialize(b,false);
        U32Vector* r=original_nested_vector12_range_assign(0,a.records+count,a.records,a.records);
        if(test_get_fs_head()!=fs_storage[0]) return 5;
        U32Vector* s=nested_vector12_range_assign(b.records,b.records+count,b.records);
        if(test_get_fs_head()!=fs_storage[0] || r!=a.records+count || s!=b.records+count || !equal(a,b)) return 6;
    }
    // Every source is empty. Destinations initially contain values, except
    // where overlap makes them source records. Check sequential aliasing.
    for(unsigned src=0;src<8;++src) for(unsigned dst=0;dst<8;++dst)
    for(unsigned n=0;n<=8-src && n<=8-dst;++n) {
        Fixture a,b;
        initialize(a,false); initialize(b,false);
        for(unsigned i=src;i<src+n;++i) {
            a.records[i].end=a.records[i].begin;
            b.records[i].end=b.records[i].begin;
        }
        U32Vector* r=original_nested_vector12_range_assign(0,a.records+src+n,a.records+src,a.records+dst);
        if(test_get_fs_head()!=fs_storage[0]) return 7;
        U32Vector* s=nested_vector12_range_assign(b.records+src,b.records+src+n,b.records+dst);
        if(test_get_fs_head()!=fs_storage[0] || r!=a.records+dst+n || s!=b.records+dst+n || !equal(a,b)) return 8;
        for(unsigned i=0;i<8;++i) {
            unsigned expected=((i>=src && i<src+n)||(i>=dst && i<dst+n))?0:i%6;
            if(a.records[i].end!=a.words[i]+expected) return 9;
        }
    }
    return 0;
}
