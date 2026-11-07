#include "impl.hpp"
using riff::Record12;
// regparm(3) maps the unused input to EAX, end to EDX, begin to ECX.
// The fourth argument stays on the caller-cleaned stack. Unlike fastcall,
// this accurately models the original plain RET rather than RET 4.
extern "C" Record12* __attribute__((regparm(3)))
original_record12_copy_assign_range(void* unused_eax, const Record12* end,
                                  const Record12* begin, Record12* destination);
static void initialize(Record12* p, unsigned n) {
    for (unsigned i=0;i<n;++i) {
        p[i].payload = (uint64_t(0xfff00000u ^ (i*719u)) << 32) |
                       (0x80000001u + i*0x12345u);
        p[i].tail = 0xdeadbeefu ^ (i*0x98765u);
    }
}
static bool same(const Record12* a,const Record12* b,unsigned n) {
    for(unsigned i=0;i<n;++i)
        if(a[i].payload!=b[i].payload || a[i].tail!=b[i].tail) return false;
    return true;
}
static int check(unsigned source,unsigned dest,unsigned count) {
    Record12 recovered[24], oracle[24];
    initialize(recovered,24); initialize(oracle,24);
    Record12* a=riff::copy_assign_range(recovered+source,recovered+source+count,recovered+dest);
    Record12* b=original_record12_copy_assign_range(0,oracle+source+count,oracle+source,oracle+dest);
    if(a!=recovered+dest+count || b!=oracle+dest+count) return 1;
    // Compare the complete arena, including source and all surrounding sentinels.
    if(!same(recovered,oracle,24)) return 2;
    return 0;
}
extern "C" int test_main() {
    if(riff::copy_assign_range(0,0,0)!=0) return 1;
    if(original_record12_copy_assign_range(0,0,0,0)!=0) return 2;
    // Every legal pair of record-aligned subranges in a small arena includes
    // empty, singleton, self-copy, disjoint, and both overlap directions.
    for(unsigned n=0;n<=12;++n)
        for(unsigned s=0;s+n<=24;++s)
            for(unsigned d=0;d+n<=24;++d)
                if(check(s,d,n)) return 3;
    return 0;
}
