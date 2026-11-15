#include "impl.hpp"
using namespace riff;
extern "C" uint32_t __attribute__((fastcall)) original_script_gc_separate_finalizable(State*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i];return d; }
extern "C" void* memset(void* d,int v,unsigned n) { unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)v;return d; }
struct Fixture { State state; Global global; Object* head; String name,other; Object objects[8]; Table tables[6]; Node nodes[6][5]; };
static Fixture f;
static unsigned char before[sizeof(Fixture)], after[sizeof(Fixture)];
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true; }
static uint32_t sizes[6]={0,1,0xffffffe8u,0xffffffffu,4096,17};
extern "C" int test_main() {
    unsigned fs[8]={0x13572468u}; if(test_install_fs(fs)!=0)return 1;
    for(unsigned flags=0;flags<256;++flags) for(unsigned force_index=0;force_index<3;++force_index)
    for(unsigned ring=0;ring<3;++ring) for(unsigned variant=0;variant<8;++variant) {
        memset(&f,0xa5,sizeof(f));
        f.state.global=&f.global; f.global.root_link=&f.head;f.global.finalizer_name=&f.name;
        f.name.hash=variant&3;f.other.hash=f.name.hash;f.head=(variant==7?0:&f.objects[0]);
        f.global.finalizer_tail=ring?&f.objects[5+ring]:0;
        if(ring==1)f.objects[6].next=&f.objects[6];
        if(ring==2){f.objects[6].next=&f.objects[7];f.objects[7].next=&f.objects[6];}
        unsigned exp[8]={0,1,2,32,33,34,2,0};
        for(unsigned i=0;i<6;++i) {
            Object& o=f.objects[i];o.next=i==5?0:&f.objects[i+1];o.marks=(uint8_t)(flags ^ (i*3));o.payload_size=sizes[(i+variant)%6];o.metatable=&f.tables[i];
            Table& t=f.tables[i]; t.absent_events=(uint8_t)(0x80 | (i==1?4:0));t.hash_exponent=(uint8_t)exp[variant];t.nodes=f.nodes[i];
            for(unsigned j=0;j<5;++j){Node& n=f.nodes[i][j];n.key=&f.other;n.key_tag=4;n.value_tag=7;n.next=0;}
            unsigned bucket=f.name.hash & ((1u<<(exp[variant]&31))-1);
            Node* n=&f.nodes[i][bucket];
            if(i==2)o.metatable=0;
            if(variant&1){n->key_tag=3;n->key=&f.name;n->next=&f.nodes[i][4];n=n->next;}
            n->key=&f.name;n->key_tag=4;n->value_tag=(i==3 || variant==6)?0:(i==4?0x80000000u:1);
        }
        uint32_t force=force_index==2?0x80000000u:force_index;
        bool moved[6]={false};uint32_t expected=0;
        if(variant!=7)for(unsigned i=0;i<6;++i) {
            unsigned m=f.objects[i].marks;
            moved[i]=((m&3)||force) && !(m&8) && i!=1 && i!=2 && i!=3 && variant!=6;
            if(moved[i])expected+=24u+f.objects[i].payload_size;
        }
        memcpy(before,&f,sizeof(f));
        uint32_t oracle=original_script_gc_separate_finalizable(&f.state,force);
        if(test_get_fs_head()!=fs[0])return 2;
        if(oracle!=expected)return 3;
        Object* p=f.head;
        if(variant!=7)for(unsigned i=0;i<6;++i)if(!moved[i]){if(p!=&f.objects[i])return 4;p=p->next;}
        if(p)return 5;
        Object* tail=f.global.finalizer_tail;
        unsigned count=ring;for(unsigned i=0;i<6;++i)if(moved[i])++count;
        if(count){p=tail->next;for(unsigned i=0;i<ring;++i){if(p!=&f.objects[6+i])return 6;p=p->next;}for(unsigned i=0;i<6;++i)if(moved[i]){if(p!=&f.objects[i])return 7;p=p->next;}if(p!=tail->next)return 8;}else if(tail)return 9;
        memcpy(after,&f,sizeof(f));memcpy(&f,before,sizeof(f));
        uint32_t recovered=f.state.separate_finalizable(force);
        if(recovered!=oracle || !equal(after,&f,sizeof(f)))return 10;
        // A second call must be idempotent: all eligible objects are now marked.
        if(original_script_gc_separate_finalizable(&f.state,force)!=0)return 11;
        if(test_get_fs_head()!=fs[0] || !equal(after,&f,sizeof(f)))return 12;
    }
    test_write("gc separation comparisons passed\n",33);return 0;
}
