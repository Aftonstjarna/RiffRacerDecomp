#include "impl.hpp"
extern "C" {
CarLights* RIFF_THIS original_shader_carlights_ctor(CarLights*,uint32_t);
void RIFF_THIS original_shader_base_ctor(CarLights*);
void RIFF_THIS original_shader_common_parameters(CarLights*);
int test_install_fs(void*);
unsigned test_get_fs_head();
void test_write(const char*,unsigned);
}
ShaderManager* shader_manager __attribute__((section(".manager"),used,aligned(4)));
uint32_t cookie __attribute__((section(".cookie"),used,aligned(4)));
uint32_t cookieGuard __attribute__((section(".cookie_guard"),used,aligned(4)));
void RIFF_THIS CarLights::initializeBase() { original_shader_base_ctor(this); }
void RIFF_THIS CarLights::initializeCommonParameters() { original_shader_common_parameters(this); }
extern "C" void* memset(void* d,int c,unsigned n) { unsigned char* p=(unsigned char*)d; for(unsigned i=0;i<n;++i)p[i]=(unsigned char)c; return d; }
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* p=(unsigned char*)d; const unsigned char* q=(const unsigned char*)s;for(unsigned i=0;i<n;++i)p[i]=q[i];return d; }
struct Resource { ResourceVtable* vtable; uint32_t id; };
struct Event { uint32_t kind,id,parent,name; };
static Event events[128], saved[128];
static unsigned count, error, mode, seed;
static CarLights* active;
static uint32_t word(const void* p) { return (uint32_t)(uintptr_t)p; }
static void record(uint32_t kind, ShaderResource* r,uint32_t parent,uint32_t name) {
    Resource* resource=(Resource*)r;
    if(count>=128) {error=1;return;}
    Event e={kind,resource->id,parent,name}; events[count++]=e;
    // Both callbacks see the object after identity initialization and resource stores.
    if(active->vtable!=0xa0145c || active->transform[0][0]!=1.0f || active->transform[3][2]!=0.0f) error=2;
}
static uint32_t classify(const char* s) {
    if(word(s)==0x9fe740)return 1;
    if(word(s)==0xa014b4)return 2;
    const char* a="matWorldViewProj"; const char* b="lightColour";
    unsigned i=0; while(s[i] && s[i]==a[i])++i; if(!s[i]&&!a[i])return 1;
    i=0;while(s[i] && s[i]==b[i])++i; if(!s[i]&&!b[i])return 2;
    error=3;return 0;
}
static uint32_t RIFF_STDCALL named(ShaderResource* r,uint32_t parent,const char* name) {
    uint32_t n=classify(name); record(9,r,parent,n);
    if(parent || n!=count)error=4;
    return mode==0 ? 0 : (seed ^ (((Resource*)r)->id*0x1020304u) ^ (n*0xabcdef01u));
}
// D3DX-style descriptor ABI: version, creator pointer, constant count.
static uint32_t RIFF_STDCALL describe(ShaderResource* r,uint32_t* desc) {
    record(5,r,0,0); desc[0]=0x1234;desc[1]=0;desc[2]=mode==2 ? 3 : 0;
    return mode==1 ? 0x80004005u : 0;
}
static uint32_t RIFF_STDCALL byIndex(ShaderResource* r,uint32_t parent,uint32_t index) {
    record(8,r,parent,index); return 0; // audited lookup skips null handles
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* p=(const unsigned char*)a;const unsigned char* q=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) { if(p[i]!=q[i])return false; }
    return true;
}
extern "C" int test_main() {
    uint32_t fs[16]; fs[0]=0xffffffffu;
    if(test_install_fs(fs)!=0)return 1;
    ResourceVtable vt={};vt.unused[5]=word((void*)&describe);vt.unused[8]=word((void*)&byIndex);vt.namedParameter=&named;
    Resource vertex={&vt,1}, pixel={&vt,2};
    ShaderManager manager; memset(&manager,0x71,sizeof(manager));shader_manager=&manager;
    cookie=0x12345678;cookieGuard=0;
    const uint32_t variants[]={0,1,2,3,0x7fffffff,0x80000000,0xffffffff,0xdeadbeef};
    unsigned total=0;
    for(mode=0;mode<3;++mode)for(unsigned alias=0;alias<2;++alias)for(unsigned fill=0;fill<2;++fill)for(unsigned v=0;v<8;++v) {
        seed=0x87654321u+total*0x10203u;
        manager.vertexProgram=seed;manager.pixelProgram=~seed;
        manager.vertexParameters=(ShaderResource*)&vertex;
        manager.pixelParameters=(ShaderResource*)(alias?&vertex:&pixel);
        ShaderManager before;memcpy(&before,&manager,sizeof(manager));
        struct Guarded {uint32_t pre[4];CarLights object;uint32_t post[4];} a,b;
        memset(&a,fill?0xff:0xa5,sizeof(a));memcpy(&b,&a,sizeof(a));
        active=&a.object;count=error=0;
        if(original_shader_carlights_ctor(active,variants[v])!=active)return 2;
        if(test_get_fs_head()!=fs[0])return 3;
        if(error)return 4;
        unsigned originalCount=count;memcpy(saved,events,count*sizeof(Event));
        active=&b.object;count=error=0;
        if(active->construct(variants[v])!=active)return 5;
        if(test_get_fs_head()!=fs[0])return 6;
        if(error || count!=originalCount || !equal(events,saved,count*sizeof(Event)))return 7;
        if(!equal(&a,&b,sizeof(a)) || !equal(&before,&manager,sizeof(manager)))return 8;
        if(a.object.unknown0c || a.object.variant!=variants[v])return 9;
        for(unsigned i=0;i<4;++i) {
            uint32_t untouched=fill?0xffffffffu:0xa5a5a5a5u;
            if(a.pre[i]!=untouched || a.post[i]!=untouched)return 13;
        }
        for(unsigned i=0;i<16;++i)if(a.object.commonParameters[i]!=0)return 14;
        if(count!=(mode==2?66u:18u))return 15;
        for(unsigned r=0;r<4;++r)for(unsigned c=0;c<4;++c)if(a.object.transform[r][c]!=(r==c?1.0f:0.0f))return 10;
        if(vertex.vtable!=&vt || pixel.vtable!=&vt || vertex.id!=1 || pixel.id!=2)return 11;
        if(cookie!=0x12345678 || cookieGuard!=0 || shader_manager!=&manager)return 12;
        ++total;
    }
    static const char message[]="96 differential constructor cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
