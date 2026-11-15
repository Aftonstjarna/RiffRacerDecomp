#include "impl.hpp"
extern "C" uint32_t __attribute__((fastcall)) original_script_table_hash_boundary(const ScriptTable*, uint32_t);
extern "C" const ScriptValue* __attribute__((fastcall)) original_script_table_get_integer(const ScriptTable*, uint32_t);
extern "C" const ScriptValue* RIFF_FASTCALL script_table_get_integer(const ScriptTable* t, uint32_t k) {
    return original_script_table_get_integer(t, k);
}
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* p = static_cast<unsigned char*>(d);
    const unsigned char* q = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) p[i]=q[i];
    return d;
}
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* p=static_cast<const unsigned char*>(a);
    const unsigned char* q=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(p[i]!=q[i]) return false;
    return true;
}
static ScriptValue values[128];
static ScriptNode nodes[64];
static int check(ScriptTable& t,uint32_t lower,bool known=false,uint32_t expected=0) {
    ScriptTable saved=t;
    ScriptValue va[128]; ScriptNode no[64];
    memcpy(va,values,sizeof(values)); memcpy(no,nodes,sizeof(nodes));
    uint32_t a=original_script_table_hash_boundary(&t,lower);
    if(!same(&t,&saved,sizeof(t)) || !same(va,values,sizeof(values)) || !same(no,nodes,sizeof(nodes))) return 1;
    uint32_t b=t.hashBoundary(lower);
    if(a!=b || (known && b!=expected)) return 2;
    if(!same(&t,&saved,sizeof(t)) || !same(va,values,sizeof(values)) || !same(no,nodes,sizeof(nodes))) return 3;
    return 0;
}
extern "C" int test_main() {
    ScriptTable t;
    unsigned char* p=reinterpret_cast<unsigned char*>(&t);
    for(unsigned i=0;i<sizeof(t);++i) p[i]=static_cast<unsigned char>(0x83+i);
    t.array=values; t.arraySize=128; t.hash=nodes; t.hashLogSize=0;
    for(unsigned i=0;i<128;++i) { values[i].payload=0xdead0000+i; values[i].tag=0; }
    // Every pattern in ten slots, with nil beyond: covers doubling and bisection.
    for(unsigned mask=0;mask<1024;++mask) {
        for(unsigned i=0;i<10;++i) values[i].tag=(mask&(1u<<i)) ? (i&1 ? 0xffffffffu:3u):0;
        int r=check(t,0); if(r) return 10+r;
    }
    for(unsigned prefix=0;prefix<64;++prefix) {
        for(unsigned i=0;i<64;++i) values[i].tag=i<prefix?7:0;
        for(unsigned lower=0;lower<=prefix;++lower) {
            int r=check(t,lower,true,prefix); if(r) return 20+r;
        }
    }
    t.arraySize=64;
    // Explicit nil numeric keys avoid requiring a mapped global nil fixture.
    // Collision chains skip wrong types, NaNs, and unequal numeric keys.
    for(unsigned i=0;i<64;++i) {
        nodes[i].value.payload=0xcafe0000+i; nodes[i].value.tag=0;
        nodes[i].key=65.0f; nodes[i].keyTag=0; nodes[i].next=0;
    }
    nodes[0].keyTag=2; nodes[0].next=&nodes[1];
    uint32_t nan=0x7fc01234; memcpy(&nodes[1].key,&nan,4);
    nodes[1].keyTag=3; nodes[1].next=&nodes[2];
    nodes[2].key=66; nodes[2].keyTag=3; nodes[2].next=&nodes[3];
    nodes[3].key=65; nodes[3].keyTag=3;
    int r=check(t,64,true,64); if(r) return 30+r;
    // Nonzero hash modulo, including x86 shift masking (0,1,2,3,5,33).
    const unsigned shifts[]={0,1,2,3,5,33};
    for(unsigned s=0;s<6;++s) {
        t.hashLogSize=static_cast<uint8_t>(shifts[s]);
        uint32_t bits; float key=65; memcpy(&bits,&key,4);
        unsigned bucket=bits%(((1u<<(shifts[s]&31))-1u)|1u);
        for(unsigned i=0;i<64;++i) { nodes[i].next=0; nodes[i].keyTag=3; nodes[i].key=65; }
        nodes[bucket].value.tag=0;
        r=check(t,64,true,64); if(r) return 40+r;
    }
    t.hashLogSize=0; nodes[0].keyTag=3; nodes[0].next=0;
    // Signed conversion, rounding at 2^24, wrapped initial increment and zero hashing.
    const uint32_t starts[]={0x80000000u,0xfffffffeu,0xffffffffu,0x1000000u,0x7ffffffeu};
    for(unsigned i=0;i<5;++i) {
        nodes[0].key=static_cast<float>(static_cast<int32_t>(starts[i]+1));
        r=check(t,starts[i],true,starts[i]); if(r) return 50+r;
    }
    // Occupied huge key doubles across the cutoff and restarts a linear scan.
    nodes[0].key=static_cast<float>(0x3fffffff); nodes[0].value.tag=9;
    for(unsigned prefix=0;prefix<16;++prefix) {
        for(unsigned i=0;i<64;++i) values[i].tag=i<prefix?1:0;
        r=check(t,0x3ffffffeu,true,prefix); if(r) return 60+r;
    }
    // Hash-only exponential growth; the terminal interval has width one.
    t.arraySize=0; t.array=0;
    nodes[0].key=1; nodes[0].value.tag=0xffffffffu; nodes[0].next=&nodes[1];
    nodes[1].key=2; nodes[1].keyTag=3; nodes[1].value.tag=0; nodes[1].next=0;
    r=check(t,0,true,1); if(r) return 70+r;
    return 0;
}
