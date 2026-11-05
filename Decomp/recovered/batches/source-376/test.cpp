#include "impl.hpp"
using riff::Record28;
using riff::Record28Vector;
extern "C" Record28** __attribute__((thiscall)) original_record28_erase_range(
    Record28Vector*, Record28**, Record28*, Record28*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned fs_storage[8];
struct Fixture {
    unsigned before[3];
    Record28 records[12];
    unsigned after[3];
};
static void fill(Fixture& f, unsigned seed) {
    for (unsigned i=0;i<3;++i) { f.before[i]=0x13579bdfu+i; f.after[i]=0xfdb97531u-i; }
    for (unsigned i=0;i<12;++i)
        for (unsigned j=0;j<7;++j)
            f.records[i].words[j]=(seed*0x1020304u) ^ (i*0x432167u+j*0xdeadbeefu);
}
static bool same_record(const Record28& a,const Record28& b) {
    for(unsigned j=0;j<7;++j) if(a.words[j]!=b.words[j]) return false;
    return true;
}
static bool pointer_equal(Record28* a,Record28* b,Fixture& x,Fixture& y) {
    return a-x.records == b-y.records;
}
static int check(unsigned n,unsigned first,unsigned last,unsigned mode,unsigned seed) {
    Fixture a,b,initial; fill(a,seed); fill(b,seed); fill(initial,seed);
    Record28Vector x={a.records,a.records+n,a.records+12};
    Record28Vector y={b.records,b.records+n,b.records+12};
    Record28 *rx=a.records+11,*ry=b.records+11;
    Record28** sx=mode==1?&x.begin:mode==2?&x.end:mode==3?&x.capacity_end:&rx;
    Record28** sy=mode==1?&y.begin:mode==2?&y.end:mode==3?&y.capacity_end:&ry;
    Record28** retx=x.erase_range(sx,a.records+first,a.records+last);
    Record28** rety=original_record28_erase_range(&y,sy,b.records+first,b.records+last);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    if(retx!=sx || rety!=sy) return 2;
    if(!pointer_equal(x.begin,y.begin,a,b) || !pointer_equal(x.end,y.end,a,b) ||
       !pointer_equal(x.capacity_end,y.capacity_end,a,b) || !pointer_equal(rx,ry,a,b)) return 3;
    if(*sx!=a.records+first || *sy!=b.records+first) return 4;
    for(unsigned i=0;i<12;++i) {
        if(!same_record(a.records[i],b.records[i])) return 5;
        unsigned expected=i;
        if(first!=last && i>=first && i<n-(last-first)) expected=i+(last-first);
        if(!same_record(a.records[i],initial.records[expected])) return 6;
    }
    for(unsigned i=0;i<3;++i)
        if(a.before[i]!=initial.before[i] || b.before[i]!=initial.before[i] ||
           a.after[i]!=initial.after[i] || b.after[i]!=initial.after[i]) return 7;
    if(mode==0 && (x.begin!=a.records || x.end!=a.records+n-(last-first) ||
                   x.capacity_end!=a.records+12)) return 8;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678u;
    if(test_install_fs(fs_storage)!=0) return 10;
    for(unsigned n=0;n<=12;++n)
        for(unsigned first=0;first<=n;++first)
            for(unsigned last=first;last<=n;++last)
                for(unsigned mode=0;mode<4;++mode) {
                    int r=check(n,first,last,mode,n+first*13+last*29);
                    if(r) return 20+r;
                }
    // Empty null triple uses no pointer arithmetic or allocation access.
    Record28Vector x={0,0,0},y={0,0,0};
    Record28 *rx=0,*ry=0;
    if(x.erase_range(&rx,0,0)!=&rx) return 40;
    if(original_record28_erase_range(&y,&ry,0,0)!=&ry) return 41;
    if(test_get_fs_head()!=fs_storage[0]) return 42;
    if(rx || ry || x.begin || x.end || x.capacity_end || y.begin || y.end || y.capacity_end) return 43;
    test_write("record28 erase tests passed\n",28);
    return 0;
}
