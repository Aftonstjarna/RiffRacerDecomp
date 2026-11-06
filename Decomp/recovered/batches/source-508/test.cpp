#include "impl.hpp"
using riff::NarrowString;
extern "C" bool __attribute__((thiscall)) original_narrow_tree_key_less(
    const riff::NarrowTreeKeyLess*, const NarrowString&, const NarrowString&);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) a[i]=b[i];
}
static bool equal(const void* x,const void* y,unsigned n) {
    const unsigned char* a=static_cast<const unsigned char*>(x);
    const unsigned char* b=static_cast<const unsigned char*>(y);
    for(unsigned i=0;i<n;++i) if(a[i]!=b[i]) return false;
    return true;
}
struct Fixture { unsigned before; NarrowString s; unsigned after; unsigned char data[64]; };
static void setup(Fixture& f, unsigned len, bool heap, unsigned cap, unsigned seed) {
    unsigned char* bytes=reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof(f);++i) bytes[i]=static_cast<unsigned char>(seed+i*13);
    f.s.length=len; f.s.capacity=heap?cap:15;
    if(heap) f.s.storage.heap=f.data;
}
extern "C" int test_main() {
    unsigned fs[8]={0x13579bdf,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    riff::NarrowTreeKeyLess cmp;
    unsigned char cmp_before[sizeof(cmp)];
    reinterpret_cast<unsigned char*>(&cmp)[0]=0x79;
    copy(cmp_before,&cmp,sizeof(cmp));
    unsigned cases=0;
    for(unsigned mode=0;mode<4;++mode) {
      for(unsigned n=0;n<=40;++n) for(unsigned m=0;m<=40;++m) {
        if((!(mode&1)&&n>15)||(!(mode&2)&&m>15)) continue;
        for(unsigned pattern=0;pattern<8;++pattern) {
          Fixture a,b,old_a,old_b;
          setup(a,n,(mode&1)!=0,pattern&1?16:0xffffffffu,31);
          setup(b,m,(mode&2)!=0,pattern&1?0xffffffffu:16,97);
          unsigned char* x=(mode&1)?a.data:a.s.storage.small;
          unsigned char* y=(mode&2)?b.data:b.s.storage.small;
          for(unsigned i=0;i<64;++i) {
            if(i<n) x[i]=static_cast<unsigned char>((i*37+pattern*53)&255);
            if(i<m) y[i]=static_cast<unsigned char>((i*37+pattern*53)&255);
          }
          unsigned common=n<m?n:m;
          if(common && pattern>=2) {
            unsigned pos=pattern==2?0:pattern==3?common-1:common/2;
            x[pos]=pattern&1?0:255; y[pos]=pattern&1?128:0;
          }
          // Include embedded NUL with differing suffixes; lengths, not strlen.
          if(common>2 && pattern==7) {x[0]=0;y[0]=0; x[1]=1;y[1]=2;}
          bool expected=n<m;
          for(unsigned i=0;i<common;++i) if(x[i]!=y[i]) {expected=x[i]<y[i];break;}
          copy(&old_a,&a,sizeof(a));copy(&old_b,&b,sizeof(b));
          bool original=original_narrow_tree_key_less(&cmp,a.s,b.s);
          if(test_get_fs_head()!=0x13579bdfu) return 2;
          if(original!=expected || cmp(a.s,b.s)!=original) return 3;
          if(!equal(&a,&old_a,sizeof(a))||!equal(&b,&old_b,sizeof(b))||
             !equal(&cmp,cmp_before,sizeof(cmp))) return 4;
          // Aliasing is valid, and equal keys are never less.
          if(original_narrow_tree_key_less(&cmp,a.s,a.s)) return 5;
          if(test_get_fs_head()!=0x13579bdfu) return 6;
          if(cmp(a.s,a.s)||!equal(&a,&old_a,sizeof(a))||
             !equal(&b,&old_b,sizeof(b))||!equal(&cmp,cmp_before,sizeof(cmp))) return 7;
          ++cases;
        }
      }
    }
    if(cases!=25992) return 8;
    static const char message[]="narrow-tree-key-less: differential tests passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
