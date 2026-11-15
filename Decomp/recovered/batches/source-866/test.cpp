#include "impl.hpp"
using namespace riff;
extern "C" void* __attribute__((regparm(3))) original_script_buffer_ensure_capacity(
    uint32_t unused_eax, ScriptBuffer*, ScriptState*, uint32_t requested);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(
    uint32_t unused_eax, void*, ScriptState*, uint32_t old_size, uint32_t new_size);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[32];
static uint32_t state_words[25], global_words[24];
static unsigned char source[64], destination[64];
static ScriptBuffer* active_buffer;
static unsigned calls, errors, bad, old_seen, new_seen;
static void* pointer_seen;
static bool fail_allocation, mutate;
static void fill(void* p,unsigned n,unsigned char c) {
    unsigned char* b=(unsigned char*)p;for(unsigned i=0;i<n;++i)b[i]=c;
}
static bool equal(const void* p,const void* q,unsigned n) {
    const unsigned char* a=(const unsigned char*)p;
    const unsigned char* b=(const unsigned char*)q;
    for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;
    return true;
}
static void* allocator(void* user,void* p,uint32_t old_n,uint32_t new_n) {
    ++calls;if(user!=source)bad=1;
    pointer_seen=p;old_seen=old_n;new_seen=new_n;
    if(mutate) { active_buffer->data=source+1;active_buffer->capacity=7;active_buffer->unknown04=0x12345678; }
    return fail_allocation?0:destination;
}
static void* reallocate(ScriptState* s,void* p,uint32_t old_n,uint32_t new_n) {
    void* r=original_script_reallocate(0,p,s,old_n,new_n);
    if(test_get_fs_head()!=0x13579bdfu)bad=2;
    return r;
}
static void runtime_error(ScriptState* s,const char* text) {
    ++errors;
    if(s!=(ScriptState*)state_words)bad=3;
    const char expected[]="memory allocation error: block too big";
    if(!equal(text,expected,sizeof expected))bad=4;
}
static const BufferServices services={reallocate,runtime_error};
static void setup(ScriptBuffer* b,bool fail,bool change) {
    fill(state_words,sizeof state_words,0xa5);fill(global_words,sizeof global_words,0x5a);
    state_words[4]=(uint32_t)global_words;state_words[24]=0;
    global_words[3]=(uint32_t)&allocator;global_words[4]=(uint32_t)source;
    global_words[17]=0xfffffff0u;global_words[22]=0;
    calls=errors=bad=0;old_seen=new_seen=0;pointer_seen=0;
    fail_allocation=fail;mutate=change;active_buffer=b;
}
static int run(uint32_t old_n,uint32_t request,unsigned flags) {
    ScriptBuffer b; b.data=(flags&4)?source:0;b.unknown04=0xabcdef01;b.capacity=old_n;
    const ScriptBuffer before=b;
    const bool grows=request>old_n;
    uint32_t grown=request<32?32:request;
    // The two error inputs require the VM formatter/location/raise chain.
    // They are covered below only through the recovered dependency interface.
    if(grows && (uint32_t(grown+1)>0xfffffffdu))return 0;
    setup(&b,flags&1,flags&2);
    uint32_t initial_state[25],initial_global[24];
    for(unsigned i=0;i<25;++i)initial_state[i]=state_words[i];
    for(unsigned i=0;i<24;++i)initial_global[i]=global_words[i];
    void* r=original_script_buffer_ensure_capacity(0,&b,(ScriptState*)state_words,request);
    if(test_get_fs_head()!=0x13579bdfu)return 1;
    ScriptBuffer expected=before;
    if(grows) {expected.data=(flags&1)?0:destination;expected.capacity=grown;
        if(flags&2)expected.unknown04=0x12345678;
        initial_global[17]+=grown-old_n;
        if(flags&1)((unsigned char*)initial_state)[6]=4;
    }
    if(bad||errors||calls!=(grows?1u:0u))return 2;
    if(r!=expected.data||!equal(&b,&expected,sizeof b))return 3;
    if(grows&&(old_seen!=old_n||new_seen!=grown||pointer_seen!=before.data))return 4;
    if(!equal(initial_state,state_words,sizeof state_words)||!equal(initial_global,global_words,sizeof global_words))return 5;
    b=before;setup(&b,flags&1,flags&2);
    r=b.ensure_capacity((ScriptState*)state_words,request,services);
    if(bad||errors||calls!=(grows?1u:0u)||r!=expected.data||!equal(&b,&expected,sizeof b))return 6;
    if(grows&&(old_seen!=old_n||new_seen!=grown||pointer_seen!=before.data))return 7;
    if(!equal(initial_state,state_words,sizeof state_words)||!equal(initial_global,global_words,sizeof global_words))return 8;
    for(unsigned i=0;i<64;++i)if(source[i]!=0x66||destination[i]!=0x77)return 9;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0)return 10;
    fill(source,sizeof source,0x66);fill(destination,sizeof destination,0x77);
    const uint32_t values[]={0,1,2,30,31,32,33,63,64,65,4096,0x7fffffffu,0x80000000u,0xfffffffbu,0xfffffffcu,0xfffffffdu,0xfffffffeu,0xffffffffu};
    for(unsigned i=0;i<sizeof values/sizeof values[0];++i)
        for(unsigned j=0;j<sizeof values/sizeof values[0];++j)
            for(unsigned f=0;f<8;++f) {int r=run(values[i],values[j],f);if(r)return r;}
    // Source-only check of the statically recovered returning-error continuation.
    // No assertion of differential validation for VM errors or longjmp.
    for(uint32_t n=0xfffffffdu;n!=0xffffffffu;++n) {
        ScriptBuffer b={source,0xabcdef01,0};setup(&b,false,false);
        void* r=b.ensure_capacity((ScriptState*)state_words,n,services);
        if(r||b.data||b.capacity!=n||b.unknown04!=0xabcdef01||errors!=1||calls||bad)return 11;
    }
    return 0;
}
