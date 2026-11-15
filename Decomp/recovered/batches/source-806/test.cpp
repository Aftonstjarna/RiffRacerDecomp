#include "impl.hpp"
using namespace riff;
extern "C" Table* __attribute__((regparm(3))) original_script_table_construct(unsigned,int32_t,State*,int32_t);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(unsigned,void*,State*,uint32_t,uint32_t);
extern "C" void __attribute__((regparm(3))) original_script_table_resize_array(unsigned,Table*,State*,int32_t);
extern "C" void __attribute__((regparm(3))) original_script_table_initialize_hash_storage(unsigned,Table*,State*,int32_t);
static_assert(sizeof(Table)==32,"x86 layout");
static_assert(sizeof(Global)==72,"x86 layout");
static State state;
static Global globals[2];
static Table table;
static uint32_t array[128];
static unsigned calls,bad;
static bool mutation,zero_null;
static int count;
static void fill(void* p,unsigned n,unsigned char v){unsigned char* b=(unsigned char*)p;for(unsigned i=0;i<n;++i)b[i]=v;}
static bool same(const void* a,const void* b,unsigned n){const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static void* allocate(void* user,void* p,uint32_t old_n,uint32_t new_n){
    unsigned step=calls++;
    if(p||old_n||user!=&globals[step&&mutation?1:0])bad=1;
    if(step==0){
        if(new_n!=32)bad=1;
        if(mutation)state.global=&globals[1];
        return &table;
    }
    if(step!=1||new_n!=uint32_t(count)*8u)bad=1;
    // The constructor must link/initialize before requesting array storage.
    Global* g=&globals[mutation?1:0];
    if(g->gc_head!=&table||table.type!=5||table.marked!=(g->current_white&3)||table.flags!=255||table.hash_log2||table.metatable||table.array||table.array_count||table.hash!=empty_hash()||table.untouched18!=0xa5a5a5a5u)bad=1;
    return new_n==0&&zero_null?0:array;
}
static void* reallocate(State* s,void* p,uint32_t a,uint32_t b){return original_script_reallocate(0,p,s,a,b);}
static void resize(State* s,Table* t,int32_t n){original_script_table_resize_array(0,t,s,n);}
static void hash(State* s,Table* t,int32_t n){original_script_table_initialize_hash_storage(0,t,s,n);}
static const Services services={reallocate,resize,hash};
static void setup(unsigned white){
    fill(&state,sizeof state,0x77);fill(globals,sizeof globals,0x55);fill(&table,sizeof table,0xa5);fill(array,sizeof array,0x66);
    state.global=&globals[0];
    for(unsigned i=0;i<2;++i){globals[i].allocator=allocate;globals[i].allocator_user=&globals[i];globals[i].current_white=uint8_t(white+i);globals[i].gc_head=reinterpret_cast<Table*>(uintptr_t(0x12340000+i*32));globals[i].allocated_bytes=0xfffffff0u;}
    calls=bad=0;
}
static int run(unsigned white){
    setup(white);State initial_state=state;Global initial[2]={globals[0],globals[1]};
    Table* result=original_script_table_construct(0,count,&state,0);
    if(result!=&table||bad||calls!=2)return 1;
    unsigned owner=mutation?1:0;
    Table expected;fill(&expected,sizeof expected,0xa5);
    expected.next=initial[owner].gc_head;expected.type=5;expected.marked=initial[owner].current_white&3;expected.flags=255;expected.hash_log2=0;
    expected.metatable=0;expected.array=count==0&&zero_null?0:array;expected.hash=empty_hash();expected.last_free=empty_hash();expected.array_count=count;
    if(!same(&expected,&table,32))return 2;
    Global expected_g[2]={initial[0],initial[1]};expected_g[0].allocated_bytes+=32;expected_g[owner].allocated_bytes+=uint32_t(count)*8;expected_g[owner].gc_head=&table;
    State expected_s=initial_state;expected_s.global=&globals[owner];
    if(!same(globals,expected_g,sizeof globals)||!same(&state,&expected_s,sizeof state))return 3;
    for(unsigned i=0;i<128;++i)if(array[i]!=(i%2&&i<unsigned(count)*2?0u:0x66666666u))return 4;
    Table saved=table;uint32_t saved_array[128];for(unsigned i=0;i<128;++i)saved_array[i]=array[i];
    setup(white);result=state.construct_table(count,0,services);
    if(result!=&table||bad||calls!=2||!same(&saved,&table,32)||!same(saved_array,array,sizeof array)||!same(globals,expected_g,sizeof globals)||!same(&state,&expected_s,sizeof state))return 5;
    return 0;
}
// Dependency-boundary test for arbitrary signed capacities, without executing
// unsupported VM error paths or requiring the original logarithm data table.
static unsigned phase;static int32_t wanted_array,wanted_hash;
static void* stub_alloc(State*,void* p,uint32_t a,uint32_t b){if(phase++||p||a||b!=32)bad=1;return &table;}
static void stub_array(State* s,Table* t,int32_t n){if(phase++!=1||s!=&state||t!=&table||n!=wanted_array||t->hash!=empty_hash())bad=1;t->untouched18=0x12345678;}
static void stub_hash(State* s,Table* t,int32_t n){if(phase++!=2||s!=&state||t!=&table||n!=wanted_hash||t->untouched18!=0x12345678)bad=1;}
extern "C" int test_main(){
    const int sizes[]={0,1,2,7,31,63};
    for(unsigned w=0;w<256;++w)for(unsigned m=0;m<2;++m)for(unsigned z=0;z<2;++z)for(unsigned i=0;i<6;++i){count=sizes[i];mutation=m!=0;zero_null=z!=0;int r=run(w);if(r)return r;}
    const int32_t limits[]={0,1,2,-1,0x7fffffff,(-2147483647-1)};
    const Services stubs={stub_alloc,stub_array,stub_hash};
    for(unsigned a=0;a<6;++a)for(unsigned h=0;h<6;++h){setup(0xff);phase=0;wanted_array=limits[a];wanted_hash=limits[h];if(state.construct_table(wanted_array,wanted_hash,stubs)!=&table||phase!=3||bad)return 6;}
    return 0;
}
