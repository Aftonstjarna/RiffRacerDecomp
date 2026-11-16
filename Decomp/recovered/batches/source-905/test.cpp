#include "impl.hpp"
using namespace riff;
// Neither original is thiscall/fastcall: stack arguments are caller-cleaned.
// regparm(3) reserves EAX, passes count/memory in EDX and state in ECX.
extern "C" Closure* __attribute__((regparm(3))) original_script_lua_closure_allocate(
    uint32_t unused_eax, uint32_t count, State*, Table* environment);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(
    uint32_t unused_eax, void* memory, State*, uint32_t old_bytes, uint32_t new_bytes);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[32];
static unsigned fs_bad;
namespace riff {
void* reallocate(State* s, void* p, uint32_t old_bytes, uint32_t new_bytes) {
    void* r = original_script_reallocate(0, p, s, old_bytes, new_bytes);
    if(test_get_fs_head()!=fs_storage[0])fs_bad=1;
    return r;
}
}
static const unsigned capacity = 20+1024*4;
struct Fixture {
    State state;
    Global first, second;
    uint32_t memory[capacity/4+8]; // front and rear guards around allocator result
    uint32_t old_root[4], changed_root[4], environment[4];
    unsigned calls, bad, seen_old, seen_new;
    void* seen_memory;
};
static Fixture f;
alignas(4) static uint8_t snapshot[sizeof(Fixture)], expected[sizeof(Fixture)];
static uint32_t requested;
static unsigned mode;
static uint8_t white;
static void fill(void* p,unsigned n,uint8_t value){uint8_t* b=(uint8_t*)p;for(unsigned i=0;i<n;++i)b[i]=value;}
static void copy(void* d,const void* s,unsigned n){uint8_t* a=(uint8_t*)d;const uint8_t* b=(const uint8_t*)s;for(unsigned i=0;i<n;++i)a[i]=b[i];}
static bool equal(const void* x,const void* y,unsigned n){const uint8_t* a=(const uint8_t*)x;const uint8_t* b=(const uint8_t*)y;for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;return true;}
static Closure* destination(){return reinterpret_cast<Closure*>(&f.memory[4]);}
static void* allocator(void* user,void* memory,uint32_t old_bytes,uint32_t new_bytes){
    ++f.calls;f.seen_old=old_bytes;f.seen_new=new_bytes;f.seen_memory=memory;
    if(user!=&f || memory || old_bytes || new_bytes!=20+4*requested)f.bad=1;
    // Observe that no target header/root stores have occurred before allocation.
    if(f.first.root!=((mode&1)?0:f.old_root) || destination()->type!=0xa5)f.bad=2;
    if(mode&2)f.state.global=&f.second;
    Global* g=f.state.global;
    if(mode&4){g->root=f.changed_root;g->current_white=static_cast<uint8_t>(white^0xff);}
    return destination();
}
static void initialize(unsigned count,unsigned flags,uint8_t color){
    fill(&f,sizeof f,0xa5);requested=count;mode=flags;white=color;
    f.state.global=&f.first;f.state.error_frame=0;
    f.first.allocator=allocator;f.first.allocator_user=&f;f.first.allocated_bytes=0xfffffff0u;
    f.first.current_white=color;f.first.root=(flags&1)?0:f.old_root;f.first.panic=0;
    f.second.current_white=static_cast<uint8_t>(color^0x55);f.second.root=f.old_root;
    f.calls=f.bad=f.seen_old=f.seen_new=0;f.seen_memory=0;
}
static int run(unsigned count,unsigned flags,uint8_t color,bool null_environment){
    initialize(count,flags,color);
    Table* env=null_environment?0:reinterpret_cast<Table*>(f.environment);
    copy(snapshot,&f,sizeof f);
    Closure* r=original_script_lua_closure_allocate(0x12345678,count,&f.state,env);
    if(test_get_fs_head()!=fs_storage[0])return 1;
    if(r!=destination()||f.calls!=1||f.bad||f.seen_memory||f.seen_old||f.seen_new!=20+4*count)return 2;
    Global* g=(flags&2)?&f.second:&f.first;
    void* previous=(flags&4)?f.changed_root:((flags&2)?f.old_root:((flags&1)?0:f.old_root));
    uint8_t mark=(flags&4)?static_cast<uint8_t>(color^0xff):((flags&2)?static_cast<uint8_t>(color^0x55):color);
    if(f.state.global!=g||g->root!=r||r->next!=previous||r->type!=6||r->marked!=(mark&3)||r->is_c||r->upvalue_count!=uint8_t(count)||r->environment!=env)return 3;
    // Build an independent expected image from the untouched initial fixture.
    Fixture* e=reinterpret_cast<Fixture*>(expected);
    copy(expected,snapshot,sizeof f);
    e->calls=1;e->seen_new=20+4*count;
    e->first.allocated_bytes+=20+4*count; // dependency captures first before callback
    if(flags&2)e->state.global=&f.second;
    Global* eg=(flags&2)?&e->second:&e->first;
    if(flags&4)eg->current_white=static_cast<uint8_t>(color^0xff);
    eg->root=r;
    Closure* ec=reinterpret_cast<Closure*>(&e->memory[4]);
    ec->next=previous;ec->marked=mark&3;ec->type=6;ec->is_c=0;ec->upvalue_count=uint8_t(count);ec->environment=env;
    for(unsigned i=0;i<count;++i)e->memory[4+5+i]=0;
    if(!equal(&f,expected,sizeof f))return 4; // includes all guards/untouched fields
    copy(&f,snapshot,sizeof f);
    r=f.state.allocate_lua_closure(count,env);
    if(fs_bad||test_get_fs_head()!=fs_storage[0])return 5;
    if(r!=destination()||!equal(&f,expected,sizeof f))return 6;
    return 0;
}
extern "C" int test_main(){
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0)return 90;
    const unsigned counts[]={0,1,2,3,7,31,254,255,256,257,1024};
    const uint8_t colors[]={0,1,2,3,4,0x7f,0x80,0xff};
    for(unsigned i=0;i<sizeof(counts)/sizeof(counts[0]);++i)
        for(unsigned j=0;j<sizeof(colors)/sizeof(colors[0]);++j)
            for(unsigned flags=0;flags<8;++flags)
                for(unsigned env=0;env<2;++env){int r=run(counts[i],flags,colors[j],env!=0);if(r)return r;}
    return 0;
}
