#include "impl.hpp"
using namespace riff;
extern "C" void RIFF_FASTCALL original_script_gc_visit_prototype(Global*, Prototype*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Fixture {
    unsigned char global[128]; Prototype p; Object o[8]; Value v[6];
    Object* names[4]; Object* children[4]; Local locals[4];
};
static Fixture a,b;
static unsigned fs[8];
static void setup(Fixture& f, int mode) {
    unsigned char* bytes=(unsigned char*)&f;
    for (unsigned i=0;i<sizeof(f);++i) bytes[i]=0xa5;
    for(int i=0;i<8;++i) { f.o[i].type=11; f.o[i].marked=(unsigned char)(0xa0 | (i&3)); }
    f.p.constants=f.v; f.p.children=f.children; f.p.locals=f.locals; f.p.names=f.names;
    f.p.source= mode==1 ? 0 : &f.o[0];
    f.p.constantCount= mode==2 ? -1 : 6; f.p.nameCount=mode==2 ? -1 : 4;
    f.p.childCount=mode==2 ? -1 : 4; f.p.localCount=mode==2 ? -1 : 4;
    for(int i=0;i<6;++i) { f.v[i].object=&f.o[i]; f.v[i].tag=i+1; }
    f.v[0].object=0; f.v[0].tag=-1; f.v[1].tag=3; f.v[2].tag=4;
    f.v[4].object=&f.o[3];
    f.names[0]=&f.o[1]; f.names[1]=0; f.names[2]=&f.o[3]; f.names[3]=&f.o[7];
    f.children[0]=&f.o[2]; f.children[1]=0; f.children[2]=&f.o[6]; f.children[3]=&f.o[7];
    for(int i=0;i<4;++i) f.locals[i].name=i==1 ? 0 : &f.o[i+4];
    if(mode==3) { f.p.constantCount=0; f.p.nameCount=0; f.p.childCount=0; f.p.localCount=0; f.p.constants=0; f.p.names=0; f.p.children=0; f.p.locals=0; }
}
// Normalize fixture-relative pointers before comparing every byte, including padding.
static unsigned norm(const Fixture& f, unsigned v) {
    unsigned base=(unsigned)&f;
    return v>=base && v<base+sizeof(f) ? v-base+1 : v;
}
static int compare(const Fixture& x,const Fixture& y) {
    const unsigned char *p=(const unsigned char*)&x,*q=(const unsigned char*)&y;
    // Compare all bytes except pointer fields, which are checked separately below.
    for(unsigned i=0;i<sizeof(Fixture);++i) {
        bool ptr=(i>=__builtin_offsetof(Fixture,p)+8 && i<__builtin_offsetof(Fixture,p)+0xc)
          || (i>=__builtin_offsetof(Fixture,p)+0x10 && i<__builtin_offsetof(Fixture,p)+0x14)
          || (i>=__builtin_offsetof(Fixture,p)+0x18 && i<__builtin_offsetof(Fixture,p)+0x24)
          || (i>=__builtin_offsetof(Fixture,v) && i<__builtin_offsetof(Fixture,v)+sizeof(x.v) && (i-__builtin_offsetof(Fixture,v))%8<4)
          || (i>=__builtin_offsetof(Fixture,names) && i<__builtin_offsetof(Fixture,locals))
          || (i>=__builtin_offsetof(Fixture,locals) && (i-__builtin_offsetof(Fixture,locals))%12<4);
        if(!ptr && p[i]!=q[i]) return 1;
    }
    const unsigned *u=(const unsigned*)&x.p,*v=(const unsigned*)&y.p;
    int indexes[]={2,4,6,7,8};
    for(unsigned i=0;i<5;++i) if(norm(x,u[indexes[i]])!=norm(y,v[indexes[i]])) return 2;
    for(int i=0;i<6;++i) if(norm(x,(unsigned)x.v[i].object)!=norm(y,(unsigned)y.v[i].object)) return 3;
    for(int i=0;i<4;++i) if(norm(x,(unsigned)x.names[i])!=norm(y,(unsigned)y.names[i]) || norm(x,(unsigned)x.children[i])!=norm(y,(unsigned)y.children[i]) || norm(x,(unsigned)x.locals[i].name)!=norm(y,(unsigned)y.locals[i].name)) return 4;
    return 0;
}
extern "C" int test_main() {
    fs[0]=0x12345678; if(test_install_fs(fs)) return 1;
    unsigned head=test_get_fs_head();
    for(int mode=0;mode<4;++mode) {
        setup(a,mode); setup(b,mode);
        original_script_gc_visit_prototype((Global*)a.global,&a.p);
        if(test_get_fs_head()!=head) return 2;
        visit_prototype((Global*)b.global,&b.p);
        if(test_get_fs_head()!=head || compare(a,b)) return 3+mode;
    }
    return 0;
}
