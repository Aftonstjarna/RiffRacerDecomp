#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_script_gc_clear_weak_entries(GCTable*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Fixture { GCObject objects[12]; GCValue array[8]; GCNode nodes[8]; GCTable tables[2]; };
static Fixture a,b;
static unsigned fs_storage[8];
static unsigned seed;
static unsigned rnd() { seed = seed * 1664525u + 1013904223u; return seed; }
static void setup(Fixture& f, unsigned s) {
    seed=s;
    for (int i=0;i<12;i++) { for(int j=0;j<5;j++) f.objects[i].prefix[j]=(uint8_t)rnd(); f.objects[i].flags=(uint8_t)rnd(); }
    const int tags[] = {-1,0,1,3,4,5,7,8,11};
    for (int i=0;i<8;i++) {
        f.array[i].object=&f.objects[rnd()%12]; f.array[i].tag=tags[rnd()%9];
        f.nodes[i].value.object=&f.objects[rnd()%12]; f.nodes[i].value.tag=tags[rnd()%9];
        f.nodes[i].key.object=&f.objects[rnd()%12]; f.nodes[i].key.tag=tags[rnd()%9]; f.nodes[i].link=rnd();
    }
    for(int i=0;i<2;i++) {
        GCTable& t=f.tables[i]; for(int j=0;j<5;j++) t.prefix[j]=(uint8_t)rnd();
        t.flags=(uint8_t)rnd(); t.unused6=(uint8_t)rnd(); t.hash_log2=(uint8_t)(2 + (s%2)*32);
        t.unused8=rnd(); t.array=f.array+i*4; t.nodes=f.nodes+i*4; t.unused14=rnd();
        t.next=i==0 ? &f.tables[1] : 0; t.array_size=(s+i)%5;
    }
}
static bool equal(const Fixture& x,const Fixture& y) {
    for(int i=0;i<12;i++) { for(int j=0;j<5;j++) if(x.objects[i].prefix[j]!=y.objects[i].prefix[j]) return false; if(x.objects[i].flags!=y.objects[i].flags) return false; }
    for(int i=0;i<8;i++) {
        if(x.array[i].tag!=y.array[i].tag || x.array[i].object-x.objects != y.array[i].object-y.objects) return false;
        if(x.nodes[i].value.tag!=y.nodes[i].value.tag || x.nodes[i].key.tag!=y.nodes[i].key.tag || x.nodes[i].link!=y.nodes[i].link) return false;
        if(x.nodes[i].value.object-x.objects!=y.nodes[i].value.object-y.objects || x.nodes[i].key.object-x.objects!=y.nodes[i].key.object-y.objects) return false;
    }
    for(int i=0;i<2;i++) { const GCTable& p=x.tables[i]; const GCTable& q=y.tables[i];
        for(int j=0;j<5;j++) if(p.prefix[j]!=q.prefix[j]) return false;
        if(p.flags!=q.flags || p.unused6!=q.unused6 || p.hash_log2!=q.hash_log2 || p.unused8!=q.unused8 || p.unused14!=q.unused14 || p.array_size!=q.array_size) return false;
        if(p.array-x.array!=q.array-y.array || p.nodes-x.nodes!=q.nodes-y.nodes || (p.next!=0)!=(q.next!=0)) return false;
    } return true;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678; if(test_install_fs(fs_storage)!=0) return 1;
    unsigned head=test_get_fs_head();
    original_script_gc_clear_weak_entries(0); if(test_get_fs_head()!=head) return 2;
    clear_weak_entries(0);
    for(unsigned s=0;s<10000;s++) {
        setup(a,s); setup(b,s);
        original_script_gc_clear_weak_entries(&a.tables[0]);
        if(test_get_fs_head()!=head) return 3;
        clear_weak_entries(&b.tables[0]);
        if(!equal(a,b)) return 4;
    }
    // Exhaust the tag/flag decisions in isolated array and hash entries.
    const int tags[] = {-1,0,3,4,5,7,8,11};
    for (unsigned at=0; at<8; ++at) for (unsigned kt=0; kt<8; ++kt)
    for (unsigned vt=0; vt<8; ++vt) for (unsigned flags=0; flags<16; ++flags) {
        setup(a,42); setup(b,42);
        Fixture* fixtures[] = {&a,&b};
        for (int n=0;n<2;n++) {
            Fixture& f=*fixtures[n]; GCTable& t=f.tables[0];
            t.next=0; t.flags|=0x10; t.array_size=1; t.hash_log2=0;
            f.array[0].tag=tags[at]; f.array[0].object=&f.objects[0];
            f.nodes[0].key.tag=tags[kt]; f.nodes[0].key.object=&f.objects[1];
            f.nodes[0].value.tag=tags[vt]; f.nodes[0].value.object=&f.objects[2];
            f.objects[0].flags=(uint8_t)flags; f.objects[1].flags=(uint8_t)flags;
            f.objects[2].flags=(uint8_t)flags;
        }
        original_script_gc_clear_weak_entries(&a.tables[0]);
        if(test_get_fs_head()!=head) return 5;
        b.tables[0].clear_weak_entries();
        if(!equal(a,b)) return 6;
    }
    return 0;
}
