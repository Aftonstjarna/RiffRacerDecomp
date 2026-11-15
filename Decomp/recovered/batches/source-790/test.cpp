#include "impl.hpp"
using namespace riff;
extern "C" const Value* __attribute__((fastcall)) original_script_table_get_value(const Table*,const Value*);
extern "C" const Value* __attribute__((fastcall)) original_script_table_get_string(const Table*,const StringHeader*);
extern "C" const Value* __attribute__((fastcall)) original_script_table_get_integer(const Table*,int32_t);
extern "C" Node* __attribute__((fastcall)) original_script_table_main_bucket(const Table*,const Value*);
extern "C" void test_write(const char*,unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
// Test-only adapters preserve the actual ECX/EDX register ABI of dependencies.
const Value* RIFF_FASTCALL Table::getString(const StringHeader* s) const {return original_script_table_get_string(this,s);}
const Value* RIFF_FASTCALL Table::getInteger(int32_t i) const {return original_script_table_get_integer(this,i);}
Node* RIFF_FASTCALL Table::mainBucket(const Value* k) const {return original_script_table_main_bucket(this,k);}
// Data-only external jump tables read directly from Game.exe. Local full tests
// map them to their original VAs. No executable bytes are supplied here.
uint32_t getDispatch[4] __attribute__((section(".get_dispatch"),used,aligned(4)))={0x4f0c14,0x4f0c19,0x4f0c19,0x4f0c06};
uint32_t bucketDispatch[4] __attribute__((section(".bucket_dispatch"),used,aligned(4)))={0x4f0150,0x4f016a,0x4f0127,0x4f0133};
uint32_t floatZero __attribute__((section(".float_zero"),used,aligned(4)))=0;
static Node nodes[11];
static Value arrayValues[4];
static unsigned calls;
static bool mapped;
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void copy(void* a,const void* b,unsigned n) {
    for(unsigned i=0;i<n;++i) ((unsigned char*)a)[i]=((const unsigned char*)b)[i];
}
static unsigned bucket(uint32_t tag,uint32_t bits,unsigned e) {
    unsigned mask=(1u<<e)-1;
    if(tag==1 || tag==4) return bits&mask;
    if(tag==3 && (bits&0x7fffffffu)==0) return 0;
    return bits%(mask|1);
}
static int check(uint32_t tag,uint32_t bits,unsigned e,unsigned scenario,unsigned mode) {
    Table table={}; table.hashLog2=(uint8_t)e; table.nodes=nodes;
    table.array=arrayValues; table.arraySize=4;
    table.opaque[6]=0xb5; table.opaque8=0xaabbccdd;
    table.opaque20[0]=0x13579bdf; table.opaque20[1]=0x2468ace0;
    StringHeader str={{0x88776655,0x44332211},bits};
    Value key; key.tag=tag; key.payload.bits=bits;
    if(tag==4) key.payload.string=&str;
    for(unsigned i=0;i<11;++i) {
        nodes[i].value.tag=0xface0000+i; nodes[i].value.payload.bits=0x90000000+i;
        nodes[i].key.tag=0xfedcba98; nodes[i].key.payload.bits=~key.payload.bits;
        nodes[i].next=0;
    }
    for(unsigned i=0;i<4;++i) {arrayValues[i].tag=0x71+i;arrayValues[i].payload.bits=i+80;}
    unsigned index=bucket(tag,bits,e);
    // One bucket -> three collision candidates. Scenarios cover first match,
    // later match, same-tag unequal payload, unequal tag, and absent key.
    Node* first=&nodes[index]; first->next=&nodes[8]; nodes[8].next=&nodes[9];
    Node* chosen=scenario==0?first:&nodes[9];
    if(scenario<2) chosen->key=key;
    if(scenario==2) {nodes[8].key=key; nodes[8].key.payload.bits^=1;}
    if(scenario==3) {nodes[8].key=key; nodes[8].key.tag^=0x100;}
    unsigned char savedNodes[sizeof(nodes)],savedArray[sizeof(arrayValues)];
    copy(savedNodes,nodes,sizeof(nodes)); copy(savedArray,arrayValues,sizeof(arrayValues));
    Table savedTable=table; Value savedKey=key; StringHeader savedStr=str;
    test_set_mxcsr(mode);
    const Value* actual=table.getValue(&key);
    unsigned actualMxcsr=test_get_mxcsr();
    test_set_mxcsr(mode);
    const Value* expected=original_script_table_get_value(&table,&key);
    unsigned originalMxcsr=test_get_mxcsr(); ++calls;
    if(actual!=expected) return 1;
    if(actualMxcsr!=originalMxcsr) return 2;
    if(!equal(&table,&savedTable,sizeof(table)) || !equal(&key,&savedKey,sizeof(key)) ||
       !equal(&str,&savedStr,sizeof(str)) || !equal(nodes,savedNodes,sizeof(nodes)) ||
       !equal(arrayValues,savedArray,sizeof(arrayValues))) return 3;
    // Independent result assertions for unambiguous non-specialized paths.
    if(tag==0 && actual!=(const Value*)0x99a41c) return 4;
    if(tag>4 && actual!=(scenario<2?&chosen->value:(const Value*)0x99a41c)) return 5;
    if(tag==3 && bits==0x3f800000 && actual!=&arrayValues[0]) return 6;
    return 0;
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    mapped=(uintptr_t)getDispatch==0x4f0c38 && (uintptr_t)bucketDispatch==0x4f018c && (uintptr_t)&floatZero==0xa063ec;
    const uint32_t tags[]={0,1,2,3,4,5,6,7,0x7fffffff,0x80000000,0xffffffff};
    const uint32_t bits[]={0,1,0x80000000,0x3f800000,0x40000000,0x40800000,
       0x40a00000,0xbf800000,0x3fc00000,0xbfc00000,0x4effffff,0x4f000000,
       0xcf000000,0xcf000001,0x7f800000,0xff800000,0x7fc00001,0x7f800001,
       0xffc12345,0x007fffff,0x80000001,0xffffffff};
    for(unsigned m=0;m<4;++m)
     for(unsigned e=0;e<4;++e)
      for(unsigned t=0;t<sizeof(tags)/sizeof(tags[0]);++t)
       for(unsigned b=0;b<sizeof(bits)/sizeof(bits[0]);++b)
        for(unsigned s=0;s<4;++s) {
            // The trusted link may omit external data mappings. Still compare
            // nil, strings, array-index numbers, and generic tags >4 directly.
            if(!mapped && (tags[t]==1 || tags[t]==2 ||
                (tags[t]==3 && bits[b]!=0x3f800000 && bits[b]!=0x40000000 && bits[b]!=0x40800000))) continue;
            int r=check(tags[t],bits[b],e,s,0x1f80u | ((m&1)?0x40u:0) | ((m&2)?0x6000u:0));
            if(r) {test_set_mxcsr(saved); return 10+r;}
        }
    test_set_mxcsr(saved);
    if(!calls) return 30;
    if(mapped) {
        const char msg[]="get-value: full mapped original differential tests passed\n";
        test_write(msg,sizeof(msg)-1);
    } else {
        const char msg[]="get-value: original comparisons passed for nil, strings, array indices, generic identity keys; float/boolean collision paths require fixed dispatch/zero mappings\n";
        test_write(msg,sizeof(msg)-1);
    }
    return 0;
}
