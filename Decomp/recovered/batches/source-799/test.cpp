#include "impl.hpp"
using namespace riff;
// EAX is unused; regparm(3) supplies EDX/ECX and caller-cleans stack sizes.
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(
    uint32_t unused_eax, void* memory, State* state, uint32_t old_bytes, uint32_t new_bytes);
static uint8_t memory[32], destination[32];
static unsigned calls, bad, old_seen, new_seen;
static void* ptr_seen;
static bool null_result, mutate;
static State* active;
static Global other;
static void* allocate(void* user, void* p,uint32_t old_n,uint32_t new_n) {
    ++calls; if(user!=destination)bad=1;
    ptr_seen=p;old_seen=old_n;new_seen=new_n;
    if(mutate)active->global=&other;
    return null_result ? 0 : destination;
}
static void fill(void* p,unsigned n,uint8_t c){uint8_t* b=(uint8_t*)p;for(unsigned i=0;i<n;++i)b[i]=c;}
static bool equal(const void* a,const void* b,unsigned n){const uint8_t* x=(const uint8_t*)a;const uint8_t* y=(const uint8_t*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static void unexpected_jump(void*,int){bad=2;}
static void unexpected_prepare(State*,uint32_t){bad=3;}
static const ErrorServices services={unexpected_jump,unexpected_prepare};
static int run(uint32_t old_n,uint32_t new_n,bool fail,bool change,bool nonnull) {
    State s; Global g;
    fill(&s,sizeof s,0xa5);fill(&g,sizeof g,0x5a);fill(&other,sizeof other,0x37);
    other.panic=0;s.global=&g;s.error_frame=0;g.panic=0;
    g.allocator=allocate;g.allocator_user=destination;g.allocated_bytes=0xfffffff0u;
    State before_s=s;Global before_g=g;Global before_other=other;
    null_result=fail;mutate=change;active=&s;calls=bad=0;
    void* input=nonnull?memory:0;
    void* result=original_script_reallocate(0,input,&s,old_n,new_n);
    if(calls!=1||bad||ptr_seen!=input||old_seen!=old_n||new_seen!=new_n)return 1;
    if(result!=(fail?0:destination))return 2;
    State expected_s=before_s;Global expected_g=before_g;
    if(change)expected_s.global=&other;
    if(fail&&new_n)expected_s.status=4;
    expected_g.allocated_bytes+=new_n-old_n;
    if(!equal(&s,&expected_s,sizeof s)||!equal(&g,&expected_g,sizeof g)||!equal(&other,&before_other,sizeof other))return 3;
    s=before_s;g=before_g;calls=bad=0;
    result=s.reallocate(input,old_n,new_n,services);
    if(result!=(fail?0:destination)||calls!=1||bad||ptr_seen!=input||old_seen!=old_n||new_seen!=new_n)return 4;
    if(!equal(&s,&expected_s,sizeof s)||!equal(&g,&expected_g,sizeof g)||!equal(&other,&before_other,sizeof other))return 5;
    for(unsigned i=0;i<32;++i)if(memory[i]!=0x66||destination[i]!=0x77)return 6;
    return 0;
}
extern "C" int test_main(){
    fill(memory,sizeof memory,0x66);fill(destination,sizeof destination,0x77);
    const uint32_t sizes[]={0,1,8,4096,0x7fffffffu,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<7;++i)for(unsigned j=0;j<7;++j)
        for(unsigned flags=0;flags<8;++flags){int r=run(sizes[i],sizes[j],flags&1,flags&2,flags&4);if(r)return r;}
    return 0;
}
