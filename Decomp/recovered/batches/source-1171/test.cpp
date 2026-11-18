#include "impl.hpp"
#include <stddef.h>
extern "C" Value* __attribute__((regparm(3))) original_script_prepare_callable(uint32_t, Value*, State*);
extern "C" const Value* __attribute__((regparm(3))) original_script_value_metamethod_lookup(uint32_t, Value*, State*, uint32_t);
extern "C" void __attribute__((fastcall)) original_script_stack_relocate_pointers(State*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Node { Value value; uint32_t key, keytag, next; };
struct Fixture { State s; uint8_t global[0x100]; uint8_t table[0x14]; uint8_t name[12]; Node node; Value oldstack[24], newstack[48]; uint32_t frame[6], upvalue[3]; };
static Fixture f;
static unsigned calls, bad, oldbytes, newbytes;
static uint32_t addr(const void* p) { return uint32_t(reinterpret_cast<uintptr_t>(p)); }
static void zero(void* p,unsigned n) { uint8_t* b=(uint8_t*)p; for(unsigned i=0;i<n;i++) b[i]=0; }
static void copy(void* d,const void* s,unsigned n) { uint8_t* a=(uint8_t*)d; const uint8_t* b=(const uint8_t*)s; for(unsigned i=0;i<n;i++) a[i]=b[i]; }
static void word(void* p,unsigned offset,uint32_t v) { *(uint32_t*)((uint8_t*)p+offset)=v; }
static void* allocator(void* user, void* p, uint32_t oldn, uint32_t newn) {
    ++calls; if(user!=&f || p!=f.oldstack) bad=1; oldbytes=oldn; newbytes=newn;
    copy(f.newstack,f.oldstack,sizeof(f.oldstack)); return f.newstack;
}
static const Value* lookup(State* s, Value* v,uint32_t e) { return original_script_value_metamethod_lookup(0,v,s,e); }
static void error(State*,Value*) { bad=2; }
static uint32_t alloc(State*,uint32_t p,uint32_t o,uint32_t n) { return addr(allocator(&f,(void*)(uintptr_t)p,o,n)); }
static uint32_t sizeerror(State*) { bad=3; return 0; }
static void relocate(State* s,uint32_t old) { original_script_stack_relocate_pointers(s,old); }
static Services svc={lookup,error,alloc,sizeerror,relocate};
static void setup(unsigned top,unsigned slot,unsigned spare,unsigned capacity) {
    zero(&f,sizeof f); calls=bad=oldbytes=newbytes=0;
    for(unsigned i=0;i<24;i++){f.oldstack[i].payload=0x11000000+i;f.oldstack[i].tag=2;}
    f.s.stack=addr(f.oldstack); f.s.top=addr(f.oldstack+top); f.s.base=addr(f.oldstack+1);
    f.s.limit=f.s.top+spare; f.s.capacity=capacity; f.s.global=addr(f.global);
    f.s.firstFrame=addr(f.frame); f.s.frame=addr(f.frame); f.s.upvalues=addr(f.upvalue);
    f.frame[0]=addr(f.oldstack+1);f.frame[1]=addr(f.oldstack+2);f.frame[2]=addr(f.oldstack+3);
    f.upvalue[2]=addr(f.oldstack+4);
    word(f.global,12,addr((void*)&allocator)); word(f.global,16,addr(&f));
    word(f.global,0x7c+2*4,addr(f.table)); word(f.global,0xa0+16*4,addr(f.name));
    word(f.table,0x10,addr(&f.node)); word(f.name,8,0);
    f.node.key=addr(f.name);f.node.keytag=4; f.node.value.payload=0xabcdef12;f.node.value.tag=6;
    (void)slot;
}
struct Snapshot { uint32_t stack[48*2], top,base,limit,capacity,frame[6],upvalue[3], account,calls,oldbytes,newbytes; uint8_t old[sizeof(f.oldstack)],global[sizeof(f.global)], table[sizeof(f.table)],name[sizeof(f.name)]; Node node; State state; uint8_t newbuf[sizeof(f.newstack)]; };
static void snap(Snapshot& x) {
    zero(&x,sizeof x); Value* p=(Value*)(uintptr_t)f.s.stack; copy(x.stack,p,24*sizeof(Value));
    x.top=f.s.top-f.s.stack;x.base=f.s.base-f.s.stack;x.limit=f.s.limit-f.s.stack;x.capacity=f.s.capacity;
    for(unsigned i=0;i<3;i++)x.frame[i]=f.frame[i]-f.s.stack;
    for(unsigned i=3;i<6;i++)x.frame[i]=f.frame[i];
    x.upvalue[0]=f.upvalue[0]; x.upvalue[1]=f.upvalue[1]; x.upvalue[2]=f.upvalue[2]-f.s.stack;
    x.state=f.s; x.state.top-=f.s.stack; x.state.base-=f.s.stack; x.state.limit-=f.s.stack; x.state.stack=0; copy(x.newbuf,f.newstack,sizeof x.newbuf);
    x.account=*(uint32_t*)(f.global+68);x.calls=calls;x.oldbytes=oldbytes;x.newbytes=newbytes;
    copy(x.old,f.oldstack,sizeof x.old);copy(x.global,f.global,sizeof x.global);copy(x.table,f.table,sizeof x.table);copy(x.name,f.name,sizeof x.name);x.node=f.node;
}
static bool equal(const void* a,const void* b,unsigned n){const uint8_t* x=(const uint8_t*)a;const uint8_t* y=(const uint8_t*)b;for(unsigned i=0;i<n;i++)if(x[i]!=y[i])return false;return true;}
extern "C" int test_main(){
    unsigned fs[8]={0x13579bdf,0,0,0,0,0,0,0}; if(test_install_fs(fs))return 1; unsigned head=fs[0];
    for(unsigned top=1;top<=8;top++) for(unsigned slot=0;slot<=top;slot++) for(unsigned growth=0;growth<3;growth++) {
        unsigned spare=growth==0?16:growth==1?8:0, cap=growth==2?0:12;
        Snapshot a,b; setup(top,slot,spare,cap);
        Value* original=original_script_prepare_callable(0,f.oldstack+slot,&f.s); if(test_get_fs_head()!=head||bad||addr(original)!=f.s.stack+slot*8)return 2; snap(a);
        setup(top,slot,spare,cap); Value* recovered=f.s.prepareCallable(f.oldstack+slot,svc); if(bad||addr(recovered)!=f.s.stack+slot*8)return 3;
        // The real allocator helper updates global accounting after the callback.
        if(calls) word(f.global,68,*(uint32_t*)(f.global+68)+newbytes-oldbytes);
        snap(b); if(!equal(&a,&b,sizeof a))return 4;
    }
    return 0;
}
