#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_script_error_dispatch(riff::ScriptState*);
extern "C" void __attribute__((fastcall)) original_script_throw_status(riff::ScriptState*,int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
namespace {
void fill(void* p,unsigned n,unsigned seed) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i)b[i]=(unsigned char)(seed+i*37); }
void copy(void* d,const void* s,unsigned n) { for(unsigned i=0;i<n;++i)((unsigned char*)d)[i]=((const unsigned char*)s)[i]; }
bool equal(const void* a,const void* b,unsigned n) { for(unsigned i=0;i<n;++i)if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i])return false; return true; }
struct Box { uint32_t guard0[4]; riff::ScriptState state; uint32_t guard1[4]; };
unsigned mode, failure, events;
int32_t expectedCapacity;
riff::Value relocated[16];
riff::Value* expectedFunction;
}
namespace riff {
void RIFF_FAST throwStatus(ScriptState* s,int32_t code) {
    if(!mode) { original_script_throw_status(s,code); return; }
    if(code==5) { if(events!=0) failure=1; events=1; }
    else { if(code!=2 || events!=3) failure=2; events=4; }
    s->status=(uint8_t)code;
}
void RIFF_FAST growStack(ScriptState* s,int32_t capacity) {
    if(!mode || capacity!=expectedCapacity || events>1)failure=3;
    events=2;
    // Model only relocation, not the allocator. Assert prepared slots first.
    if(s->top[-1].payload!=0x11223344u || s->top[-1].tag!=6 ||
       s->top[0].payload!=0xabcdef01u || s->top[0].tag!=3)failure=4;
    s->top=relocated+4;
    expectedFunction=relocated+3;
}
void callHandler(ScriptState* s,Value* function,int32_t results) {
    if(!mode || events>2 || function!=expectedFunction || results!=1 || s->top!=function+2)failure=5;
    events=3;
    s->unknown0c=0x12345678u; // Must survive final throw forwarding.
}
}
extern "C" int test_main() {
    uint32_t fs[8]={0xffffffffu};
    if(test_install_fs(fs)!=0)return 10;
    if(test_get_fs_head()!=0xffffffffu)return 11;
    // Direct differential cases. Deliberately poison unused pointers/fields:
    // no-handler dispatch must not inspect top, capacity or stack storage.
    for(unsigned seed=0;seed<1024;++seed) {
        Box a,b,expected;
        uint8_t global[0x70],saved[0x70];
        fill(&a,sizeof(a),seed); fill(global,sizeof(global),seed*7);
        for(unsigned j=0;j<4;++j)global[0x58+j]=0;
        copy(saved,global,sizeof(global));
        a.state.global=global; a.state.errorJump=0; a.state.errorHandlerOffset=0;
        copy(&b,&a,sizeof(a)); copy(&expected,&a,sizeof(a)); expected.state.status=2;
        unsigned head=test_get_fs_head();
        original_script_error_dispatch(&a.state);
        if(test_get_fs_head()!=head)return 12;
        b.state.dispatchError();
        if(test_get_fs_head()!=head)return 13;
        if(!equal(&a,&b,sizeof(a)) || !equal(&a,&expected,sizeof(a)))return 14;
        if(!equal(global,saved,sizeof(global)))return 15;
    }
    // Source-only dependency-contract checks. Never used as oracle substitutes.
    mode=1;
    const int32_t capacities[]={-2147483647-1,-1,0,1,2,1073741824,2147483647};
    for(unsigned c=0;c<7;++c)for(unsigned grow=0;grow<2;++grow)for(unsigned bad=0;bad<2;++bad) {
        Box a; riff::Value stack[16]; fill(&a,sizeof(a),c); fill(stack,sizeof(stack),c);
        a.state.top=stack+5; a.state.stackBase=(uint8_t*)stack;
        a.state.errorHandlerOffset=8; a.state.stackLimit=stack+5+(grow?1:2);
        a.state.stackCapacity=capacities[c]; stack[1].payload=0x11223344u; stack[1].tag=bad?4:6;
        stack[4].payload=0xabcdef01u; stack[4].tag=3;
        events=0; failure=0; expectedFunction=stack+4;
        uint32_t cap=(uint32_t)capacities[c]; expectedCapacity=(int32_t)(capacities[c]<1?cap+1:cap+cap);
        // A returning status-5 dependency leaves the invalid tag unchanged.
        // Growth checks above expect a valid tag; use no-growth for bad tags.
        if(bad && grow)continue;
        a.state.dispatchError();
        if(failure || events!=4 || a.state.status!=2 || a.state.unknown0c!=0x12345678u)return 20;
        if(stack[5].payload!=0xabcdef01u || stack[5].tag!=3 || stack[4].payload!=0x11223344u || stack[4].tag!=(bad?4:6))return 21;
    }
    const char message[]="script-error-dispatch: 1024 original comparisons passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
