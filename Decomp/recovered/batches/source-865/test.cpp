#include "impl.hpp"
using namespace riff;
// regparm(3) puts the unused first argument in EAX, value in EDX,
// state in ECX; remaining event argument is caller-cleaned. Unlike GCC
// fastcall/thiscall, this exactly expresses the observed custom ABI.
extern "C" const Value* original_script_value_metamethod_lookup(
    uint32_t unusedEax, const Value*, const ScriptState*, uint32_t)
    __attribute__((regparm(3)));
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static struct Fixture {
    ScriptState state;
    GlobalState global;
    Value input;
    ScriptObject object;
    Metatable table;
    Metatable decoy;
    InternedName names[18];
    Node nodes[8];
    Node chain[3];
} f, before;
static void clear(void* p, unsigned n) {
    unsigned char* b=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i) b[i]=0;
}
static void copy(void* dst,const void* src,unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i) d[i]=s[i];
}
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void setup(unsigned tag,unsigned event,unsigned count,unsigned hash) {
    clear(&f,sizeof(f));
    f.state.global=&f.global;
    f.input.tag=tag;
    f.input.payload=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&f.object));
    f.object.metatable=&f.table;
    f.table.nodes=f.nodes;
    f.table.logNodeCount=static_cast<uint8_t>(count);
    f.decoy.nodes=f.nodes;
    for(unsigned i=0;i<9;++i) f.global.typeMetatables[i]=&f.decoy;
    if(tag!=5 && tag!=7) f.global.typeMetatables[tag]=&f.table;
    for(unsigned i=0;i<18;++i) f.global.metamethodNames[i]=&f.names[i];
    f.names[event].hash=hash;
    // Distinguish key pointer identity from equal hashes/content.
    f.names[(event+1)%18].hash=hash;
    for(unsigned i=0;i<8;++i) {
        f.nodes[i].value.payload=0x12340000+i;
        f.nodes[i].value.tag=6;
    }
}
static int compare(unsigned event,const Value* expected,unsigned fsHead) {
    copy(&before,&f,sizeof(f));
    const Value* recovered=f.state.lookupMetamethod(&f.input,event);
    if(recovered!=expected || !same(&f,&before,sizeof(f))) return 1;
    const Value* original=original_script_value_metamethod_lookup(0,&f.input,&f.state,event);
    if(test_get_fs_head()!=fsHead) return 2;
    if(original!=expected || recovered!=original) return 3;
    if(!same(&f,&before,sizeof(f))) return 4;
    return 0;
}
extern "C" int test_main() {
    unsigned fsStorage[8]={0x13579bdf,0,0,0,0,0,0,0};
    if(test_install_fs(fsStorage)!=0) return 10;
    const unsigned head=fsStorage[0];
    const unsigned counts[]={0,1,2,3,31,32,33,255};
    const unsigned hashes[]={0,1,7,0xffffffffu,0x80000000u};
    for(unsigned tag=0;tag<9;++tag) for(unsigned event=0;event<18;++event) {
        setup(tag,event,3,7);
        if(tag==5 || tag==7) {
            // Object path must ignore a conflicting global type metatable.
            f.global.typeMetatables[tag]=&f.table;
            f.object.metatable=0;
        } else f.global.typeMetatables[tag]=0;
        if(compare(event,originalNilAddress(),head)) return 20;
        // Missing metatable must not read event names, even for an invalid index.
        if(compare(0xffffffffu,originalNilAddress(),head)) return 21;
        if(tag==5 || tag==7) {
            f.state.global=0;
            if(compare(0xffffffffu,originalNilAddress(),head)) return 22;
        }
        for(unsigned c=0;c<8;++c) for(unsigned h=0;h<5;++h) {
            unsigned hash=hashes[h];
            // Keep selected buckets in fixture range while testing huge masks.
            if((counts[c]&31)>3) hash &= 7;
            setup(tag,event,counts[c],hash);
            unsigned bucket=hash & ((uint32_t(1)<<(counts[c]&31))-1);
            Node* node=&f.nodes[bucket];
            if(compare(event,originalNilAddress(),head)) return 30;
            node->key=&f.names[event]; node->keyTag=4;
            if(compare(event,&node->value,head)) return 31;
            // A matching string key can contain a nil value: return its address.
            node->value.tag=0;
            if(compare(event,&node->value,head)) return 32;
            node->keyTag=3;
            if(compare(event,originalNilAddress(),head)) return 33;
            node->keyTag=4; node->key=&f.names[(event+1)%18];
            if(compare(event,originalNilAddress(),head)) return 34;
            node->next=&f.chain[0];
            f.chain[0].key=&f.names[event]; f.chain[0].keyTag=0;
            f.chain[0].next=&f.chain[1];
            f.chain[1].key=&f.names[(event+1)%18]; f.chain[1].keyTag=4;
            f.chain[1].next=&f.chain[2];
            f.chain[2].key=&f.names[event]; f.chain[2].keyTag=4;
            f.chain[2].value.tag=6;
            if(compare(event,&f.chain[2].value,head)) return 35;
            f.chain[2].keyTag=9;
            if(compare(event,originalNilAddress(),head)) return 36;
            // First match wins even if there is another match later.
            node->key=&f.names[event];
            f.chain[2].keyTag=4;
            if(compare(event,&node->value,head)) return 37;
        }
    }
    return 0;
}
