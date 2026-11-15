#include "impl.hpp"
using namespace riff;
// regparm(3) describes the observed custom ABI using a discarded EAX input,
// EDX second input and ECX third input; remaining args are caller-cleaned.
extern "C" void __attribute__((regparm(3))) original_script_table_resize_array(
    unsigned unused_eax, Table*, void* state, int32_t count);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(
    unsigned unused_eax, void* memory, void* state, uint32_t old_bytes, uint32_t new_bytes);
struct Global { uint32_t pad[3]; void* (*allocator)(void*,void*,uint32_t,uint32_t); void* user; uint32_t rest[12]; uint32_t total; uint32_t tail[8]; };
struct State { uint32_t pad[4]; Global* global; uint32_t rest[20]; };
static Value pool[40], before[40], old_storage[40];
static unsigned calls, old_seen, new_seen, failed;
static void* pointer_seen;
static bool release_null;
static void* allocate(void* user, void* ptr, uint32_t old_size, uint32_t new_size) {
    if(user != pool) failed=1;
    ++calls; pointer_seen=ptr; old_seen=old_size; new_seen=new_size;
    return new_size==0 && release_null ? 0 : pool;
}
static void* reallocate(void* state,void* ptr,uint32_t old_size,uint32_t new_size) {
    return original_script_reallocate(0,ptr,state,old_size,new_size);
}
static unsigned oversize_calls;
static void* too_large(void*) { ++oversize_calls; return pool; }
static const ArrayServices services={reallocate,too_large};
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void fill(void* a,unsigned n,unsigned char v) { unsigned char* p=(unsigned char*)a; for(unsigned i=0;i<n;++i)p[i]=v; }
static int run(int old_count,int count,bool null_zero, bool moving=false) {
    Table a,b; State s; Global g;
    fill(&a,sizeof a,0xa5); a.array=moving?old_storage:pool; a.array_size=old_count; b=a;
    fill(&s,sizeof s,0); fill(&g,sizeof g,0); s.global=&g;
    g.allocator=allocate;g.user=pool;g.total=1000;
    for(unsigned i=0;i<40;++i){pool[i].payload=0x11220000+i;pool[i].tag=0xaabb0000+i;before[i]=pool[i];old_storage[i]=pool[i];}
    release_null=null_zero;calls=0;failed=0;
    original_script_table_resize_array(0,&a,&s,count);
    if(calls!=1 || failed || pointer_seen!=(moving?old_storage:pool) || old_seen!=uint32_t(old_count)*8u || new_seen!=uint32_t(count)*8u) return 1;
    if(g.total!=1000u+uint32_t(count-old_count)*8u) return 2;
    Value oracle[40];for(unsigned i=0;i<40;++i){oracle[i]=pool[i];pool[i]=before[i];}
    if(!same(old_storage,before,sizeof before))return 7;
    State expected_state;fill(&expected_state,sizeof expected_state,0);expected_state.global=&g;
    Global expected_global;fill(&expected_global,sizeof expected_global,0);expected_global.allocator=allocate;expected_global.user=pool;expected_global.total=g.total;
    if(!same(&s,&expected_state,sizeof s) || !same(&g,&expected_global,sizeof g))return 8;
    State state_after=s;Global global_after=g;
    g.total=1000;calls=0;
    resize_array(&s,&b,count,services);
    if(calls!=1 || failed || !same(&a,&b,sizeof a) || !same(pool,oracle,sizeof pool) || !same(&s,&state_after,sizeof s) || !same(&g,&global_after,sizeof g)) return 3;
    Table expected;fill(&expected,sizeof expected,0xa5);expected.array=(null_zero && count==0)?0:pool;expected.array_size=count;
    if(!same(&a,&expected,sizeof a))return 4;
    for(int i=0;i<40;++i) if(pool[i].payload!=before[i].payload || pool[i].tag!=((i>=old_count && i<count)?0:before[i].tag))return 5;
    return 0;
}
extern "C" int test_main() {
    const int sizes[]={0,1,2,7,16,31};
    for(unsigned i=0;i<6;++i)for(unsigned j=0;j<6;++j)for(unsigned z=0;z<4;++z){int r=run(sizes[i],sizes[j],(z&1)!=0,(z&2)!=0);if(r)return r;}
    // Guard-only source checks: the error helper is not an accepted oracle.
    // A negative old size would address before the allocation on a growth path.
    Table t;fill(&t,sizeof t,0);t.array=pool;t.array_size=0x7fffffff;
    const int32_t rejected[]={0x1fffffff,0x20000000,0x7fffffff,(-2147483647-1),-2};
    for(unsigned i=0;i<5;++i){oversize_calls=0;resize_array(0,&t,rejected[i],services);if(oversize_calls!=1)return 6;t.array_size=0x7fffffff;}
    // -1 wraps the guard, passes 0xfffffff8 to allocator, and does not grow.
    return run(0,-1,false);
}
