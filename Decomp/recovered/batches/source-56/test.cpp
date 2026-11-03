#include "impl.hpp"
using namespace riff;
extern "C" ParameterHandle __attribute__((stdcall)) original_shader_parameter_lookup(ConstantTable*, const char*);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memset(void* dest, int value, unsigned count) {
    unsigned char* p = static_cast<unsigned char*>(dest);
    for (unsigned i=0; i<count; ++i) p[i]=static_cast<unsigned char>(value);
    return dest;
}
extern "C" void* memcpy(void* dest, const void* src, unsigned count) {
    unsigned char* d=static_cast<unsigned char*>(dest);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for (unsigned i=0; i<count; ++i) d[i]=s[i];
    return dest;
}
struct Event { uint32_t kind, index, count; ParameterHandle handle; };
struct FakeTable {
    ConstantTable table;
    uint32_t guard1, constants;
    int32_t tableStatus, parameterStatus;
    ParameterHandle handles[8];
    const char* names[8];
    uint32_t guard2, events;
    Event log[20];
    uint32_t errors;
};
static void record(FakeTable* f, uint32_t kind, uint32_t index, uint32_t count, ParameterHandle h) {
    if (f->events>=20) { ++f->errors; return; }
    Event& e=f->log[f->events++]; e.kind=kind; e.index=index; e.count=count; e.handle=h;
}
static int32_t RIFF_STDCALL describe(ConstantTable* t, TableDescription* d) {
    FakeTable* f=reinterpret_cast<FakeTable*>(t);
    record(f,1,0,0,0);
    d->creator="test"; d->version=0x300; d->constants=f->constants;
    return f->tableStatus;
}
static ParameterHandle RIFF_STDCALL constant(ConstantTable* t, ParameterHandle parent, uint32_t index) {
    FakeTable* f=reinterpret_cast<FakeTable*>(t);
    record(f,2,index,0,parent);
    if (parent || index>=f->constants || index>=8) { ++f->errors; return 0; }
    return f->handles[index];
}
static int32_t RIFF_STDCALL parameter(ConstantTable* t, ParameterHandle h, ParameterDescription* d, uint32_t* count) {
    FakeTable* f=reinterpret_cast<FakeTable*>(t);
    uint32_t i=0;
    while (i<8 && f->handles[i]!=h) ++i;
    record(f,3,i,*count,h);
    if (*count!=1 || i==8) { ++f->errors; return -1; }
    memset(d,0x6b,sizeof(*d));
    d->name=f->names[i];
    *count=0xabcdef01; // Must be reset before the next descriptor call.
    return f->parameterStatus;
}
static const ConstantTableVtable vtable={{0,0,0,0,0},describe,parameter,0,constant};
static const char handles[8]={1,2,3,4,5,6,7,8};
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int run(uint32_t count,int32_t ts,int32_t ps,const char* query,int expected,uint32_t nullMask=0) {
    FakeTable a; memset(&a,0,sizeof(a));
    a.table.vtable=&vtable; a.guard1=0x12345678; a.guard2=0x87654321;
    a.constants=count; a.tableStatus=ts; a.parameterStatus=ps;
    const char* names[8]={"", "a", "ab", "abc", "abcd", "ABC", "\200z", "abc"};
    for (unsigned i=0;i<8;++i) { a.handles[i]=(nullMask&(1u<<i))?0:&handles[i]; a.names[i]=names[i]; }
    FakeTable b=a, before=a;
    ParameterHandle x=original_shader_parameter_lookup(&a.table,query);
    ParameterHandle y=shaderParameterLookup(&b.table,query);
    ParameterHandle want=expected<0?0:&handles[expected];
    if(x!=want || y!=x || a.errors || b.errors || !same(&a,&b,sizeof(a))) return 1;
    uint32_t event=0;
    if (a.log[event++].kind!=1) return 3;
    if (ts==0) {
        uint32_t end=expected<0?count:static_cast<uint32_t>(expected+1);
        for(uint32_t i=0;i<end;++i) {
            const Event& get=a.log[event++];
            if(get.kind!=2 || get.index!=i || get.handle!=0) return 4;
            if(before.handles[i]) {
                const Event& desc=a.log[event++];
                if(desc.kind!=3 || desc.index!=i || desc.count!=1 || desc.handle!=before.handles[i]) return 5;
            }
        }
    }
    if(a.events!=event) return 6;
    // Everything before the event counter is immutable, including table/vtable,
    // status settings, handle/name arrays and both guard words.
    if(!same(&a,&before,static_cast<unsigned>(reinterpret_cast<const char*>(&a.events)-reinterpret_cast<const char*>(&a)))) return 2;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(TableDescription)==12,"32-bit table ABI");
    static_assert(sizeof(ParameterDescription)==48,"32-bit descriptor ABI");
    if(original_shader_parameter_lookup(0,0) || shaderParameterLookup(0,0)) return 1;
    if(run(0,0,0,0,-1) || run(8,1,0,0,-1) || run(8,-1,0,0,-1)) return 2;
    const char* queries[8]={"","a","ab","abc","abcd","ABC","\200z","abc"};
    for(int i=0;i<8;++i) if(run(8,0,0,queries[i],i==7?3:i)) return 3;
    if(run(8,0,0,"missing",-1) || run(8,0,0,"AB",-1) || run(8,0,0,"abcde",-1)) return 4;
    if(run(8,0,-1,"abc",3) || run(8,0,1,"abcd",4)) return 5;
    if(run(8,0,0,"abc",7,1u<<3) || run(8,0,0,0,-1,255)) return 6;
    if(run(3,0,0,"abc",-1) || run(1,0,0,"",0)) return 7;
    test_write("shader lookup tests passed\n",27);
    return 0;
}
