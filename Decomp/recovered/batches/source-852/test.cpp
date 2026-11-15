#include "impl.hpp"
using namespace riff;
// regparm(3) supplies EAX=unused, EDX=event, ECX=table and leaves the
// fourth argument on the caller-cleaned stack: the observed custom ABI.
// Neither plain thiscall nor fastcall describes this original routine.
extern "C" Value* __attribute__((regparm(3))) original_script_table_cached_event_lookup(
    uint32_t unused_eax, uint32_t event, ScriptTable* table, const ScriptString* name);
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// Original .rdata at 0x99a41c. Data-only fixture; local linker places it.
Value oracle_nil __attribute__((section(".oracle_nil"),used,aligned(4))) = {0,0};
static unsigned fs_storage[8];
static bool equal_bytes(const void* a,const void* b,unsigned size) {
    const uint8_t* x=static_cast<const uint8_t*>(a);
    const uint8_t* y=static_cast<const uint8_t*>(b);
    for(unsigned i=0;i<size;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void copy_bytes(void* a,const void* b,unsigned size) {
    uint8_t* x=static_cast<uint8_t*>(a);
    const uint8_t* y=static_cast<const uint8_t*>(b);
    for(unsigned i=0;i<size;++i) x[i]=y[i];
}
static int run_case(unsigned exponent,unsigned hash,unsigned event,unsigned scenario,unsigned flags) {
    Node buckets[8]; Node chain[3]; ScriptString keys[2]={{ {0x12345678,0x99},hash},{{0x12345678,0x99},hash}};
    for(unsigned i=0;i<8;++i) {
        buckets[i].value.payload=0xc0010000+i; buckets[i].value.tag=5;
        buckets[i].key=&keys[1]; buckets[i].key_tag=4; buckets[i].next=0;
    }
    for(unsigned i=0;i<3;++i) {
        chain[i].value.payload=0xbad00000+i; chain[i].value.tag=7;
        chain[i].key=&keys[0]; chain[i].key_tag=3;
        chain[i].next=i<2?&chain[i+1]:0;
    }
    unsigned index=hash&((uint32_t(1)<<(exponent&31))-1);
    Node* selected=&buckets[index];
    selected->next=&chain[0];
    if(scenario==0 || scenario==1) {
        selected->key=&keys[0]; selected->key_tag=4;
        selected->value.tag=scenario==0?4:0;
    } else if(scenario==2 || scenario==3) {
        chain[1].key_tag=4; chain[1].value.tag=scenario==2?0xffffffffu:0;
        chain[2].key_tag=4; // duplicate must lose to earlier matching key
    } else if(scenario==4) {
        // pointer-equal but wrong tag, pointer-unequal but identical contents,
        // then explicit nil terminal: exercises rejection without fixed data.
        chain[1].key=&keys[1]; chain[1].key_tag=4;
        chain[2].key_tag=4; chain[2].value.tag=0;
    } // scenario 5 is a real miss with fixed nil fixture.
    ScriptTable table={{0x10,0x32,0x54,0x76,0x98,0xba},static_cast<uint8_t>(flags),static_cast<uint8_t>(exponent),0x87654321,0xfedcba98,buckets};
    ScriptTable before=table; Node buckets_before[8]; Node chain_before[3]; ScriptString keys_before[2];
    copy_bytes(buckets_before,buckets,sizeof buckets); copy_bytes(chain_before,chain,sizeof chain); copy_bytes(keys_before,keys,sizeof keys);
    Value* original=original_script_table_cached_event_lookup(0,event,&table,&keys[0]);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    if(!equal_bytes(buckets,buckets_before,sizeof buckets) || !equal_bytes(chain,chain_before,sizeof chain) || !equal_bytes(keys,keys_before,sizeof keys)) return 7;
    ScriptTable after=table;
    table=before;
    Value* recovered=table.cached_event_lookup(event,&keys[0]);
    if(original!=recovered || !equal_bytes(&table,&after,sizeof table)) return 2;
    bool nil=scenario==1 || scenario==3 || scenario==4 || scenario==5;
    Value* expected=nil?0:(scenario==0?&selected->value:&chain[1].value);
    if(original!=expected) return 3;
    ScriptTable expected_table=before;
    if(nil) expected_table.absent_events=static_cast<uint8_t>(flags | static_cast<uint8_t>(uint32_t(1)<<(event&31)));
    if(!equal_bytes(&after,&expected_table,sizeof after)) return 4;
    if(!equal_bytes(buckets,buckets_before,sizeof buckets) || !equal_bytes(chain,chain_before,sizeof chain) || !equal_bytes(keys,keys_before,sizeof keys)) return 5;
    // Cache is set-only, and lookup itself does not consult it.
    Value* again=original_script_table_cached_event_lookup(0,event,&table,&keys[0]);
    if(again!=expected || test_get_fs_head()!=fs_storage[0] || !equal_bytes(&table,&expected_table,sizeof table)) return 6;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdf;
    if(test_install_fs(fs_storage)!=0) return 10;
    const unsigned exponents[]={0,1,2,3,32,33,34,35,255};
    const unsigned events[]={0,1,2,3,4,7,8,15,31,32,33,39,40,255,0xffffffffu};
    const unsigned flags[]={0,0x55,0x80,0xff};
    bool mapped=reinterpret_cast<uintptr_t>(&oracle_nil)==0x99a41c;
    for(unsigned e=0;e<sizeof(exponents)/sizeof(exponents[0]);++e)
    for(unsigned h=0;h<8;++h)
    for(unsigned v=0;v<sizeof(events)/sizeof(events[0]);++v)
    for(unsigned f=0;f<4;++f)
    for(unsigned s=0;s<(mapped?6u:5u);++s) {
        // Exponent 255 has a huge mask: bounded hashes still select 0..7.
        int result=run_case(exponents[e],h,events[v],s,flags[f]);
        if(result) return 20+result;
    }
    // High hash bits must disappear under a small bucket mask.
    for(unsigned exponent=0;exponent<4;++exponent)
    for(unsigned low=0;low<8;++low)
    for(unsigned scenario=0;scenario<(mapped?6u:5u);++scenario) {
        int result=run_case(exponent,0xfffffff8u|low,7,scenario,0x25);
        if(result) return 40+result;
    }
    if(oracle_nil.payload || oracle_nil.tag) return 30;
    if(!mapped) {
        const char message[]="PASS core; fixed-address nil miss cases skipped (fixture unmapped)\n";
        test_write(message,sizeof(message)-1);
    } else {
        const char message[]="PASS including fixed-address nil miss cases\n";
        test_write(message,sizeof(message)-1);
    }
    return 0;
}
