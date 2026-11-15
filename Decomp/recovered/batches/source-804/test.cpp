#include "impl.hpp"
using namespace riff;
// GCC regparm maps the otherwise-unused EAX, then EDX and ECX. This custom
// register convention is neither ordinary thiscall nor stdcall.
extern "C" void __attribute__((regparm(3))) original_script_table_destroy(uint32_t,Table*,State*);
struct Event { void* user; void* memory; uint32_t old_size,new_size; };
static Event events[3], expected[3];
static unsigned calls,bad;
static State state;
static Global globals[2];
static Table table;
static uint8_t array_memory[32],hash_memory[32];
static bool mutation;
static void fill(void* p,unsigned n,uint8_t c){uint8_t* b=(uint8_t*)p;for(unsigned i=0;i<n;++i)b[i]=c;}
static bool equal(const void* a,const void* b,unsigned n){const uint8_t* x=(const uint8_t*)a;const uint8_t* y=(const uint8_t*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static void* allocate(void* user,void* memory,uint32_t old_n,uint32_t new_n){
    if(calls>=3){bad=1;return 0;}
    Event& e=events[calls++];e.user=user;e.memory=memory;e.old_size=old_n;e.new_size=new_n;
    if(mutation&&calls==1){state.global=&globals[1];table.array=hash_memory;table.array_count=0x20000001u;}
    // Returning nonnull on a free is deliberately allowed; destroy ignores it.
    return calls&1 ? array_memory : 0;
}
static int run(unsigned hash_mode,bool null_array,uint8_t exponent,uint32_t count,bool mutate){
    const bool sentinel=hash_mode==0;
    State initial_state;Global initial_globals[2];Table initial_table;
    fill(&state,sizeof state,0xa5);fill(globals,sizeof globals,0x5a);fill(&table,sizeof table,0x37);
    state.global=&globals[0];
    for(unsigned i=0;i<2;++i){globals[i].allocator=allocate;globals[i].allocator_user=&globals[i];globals[i].allocated_bytes=0xfffffff0u+i;}
    table.hash=sentinel?empty_hash():(hash_mode==1?hash_memory:0);table.array=null_array?0:array_memory;table.hash_log2=exponent;table.array_count=count;
    initial_state=state;initial_table=table;for(unsigned i=0;i<2;++i)initial_globals[i]=globals[i];
    calls=bad=0;mutation=mutate;
    original_script_table_destroy(0,&table,&state);
    if(bad||calls!=(sentinel?2u:3u))return 1;
    unsigned n=calls;
    uint32_t deducted[2]={0,0};
    for(unsigned i=0;i<n;++i){
        unsigned owner=mutate&&i?1:0;
        void* ptr;uint32_t size;
        if(!sentinel&&i==0){ptr=initial_table.hash;size=(uint32_t(1)<<(exponent&31))*20u;}
        else if(i==n-1){ptr=&table;size=32;}
        else {ptr=mutate&&!sentinel?hash_memory:initial_table.array;size=(mutate&&!sentinel?0x20000001u:count)*8u;}
        if(events[i].user!=&globals[owner]||events[i].memory!=ptr||events[i].old_size!=size||events[i].new_size)return 2;
        deducted[owner]+=size;expected[i]=events[i];
    }
    State final_state=initial_state;Table final_table=initial_table;
    if(mutate){final_state.global=&globals[1];final_table.array=hash_memory;final_table.array_count=0x20000001u;}
    for(unsigned i=0;i<2;++i)initial_globals[i].allocated_bytes-=deducted[i];
    if(!equal(&state,&final_state,sizeof state)||!equal(&table,&final_table,sizeof table)||!equal(globals,initial_globals,sizeof globals))return 3;
    state=initial_state;table=initial_table;
    for(unsigned i=0;i<2;++i){globals[i]=initial_globals[i];globals[i].allocated_bytes+=deducted[i];}
    calls=bad=0;state.destroy_table(&table);
    if(calls!=n||bad||!equal(events,expected,n*sizeof(Event)))return 4;
    if(!equal(&state,&final_state,sizeof state)||!equal(&table,&final_table,sizeof table)||!equal(globals,initial_globals,sizeof globals))return 5;
    for(unsigned i=0;i<32;++i)if(array_memory[i]!=0x66||hash_memory[i]!=0x77)return 6;
    return 0;
}
extern "C" int test_main(){
    fill(array_memory,32,0x66);fill(hash_memory,32,0x77);
    const uint32_t counts[]={0,1,17,0x1fffffffu,0x20000000u,0xffffffffu};
    const uint8_t exponents[]={0,1,7,27,28,30,31,32,33,255};
    for(unsigned s=0;s<3;++s)for(unsigned a=0;a<2;++a)for(unsigned m=0;m<2;++m)
    for(unsigned e=0;e<sizeof exponents;++e)for(unsigned c=0;c<6;++c){int r=run(s,a!=0,exponents[e],counts[c],m!=0);if(r)return r;}
    return 0;
}
