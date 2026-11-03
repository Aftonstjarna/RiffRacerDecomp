#include "impl.hpp"
using namespace riff;
extern "C" void RIFF_THISCALL original_shader_release(ShaderManager*);
extern "C" void test_write(const char*, unsigned);
struct MockCallback { Callback base; unsigned id; };
struct MockResource { Resource base; unsigned id; };
static ShaderManager manager;
static Callback* externalA[282];
static Callback* externalB[282];
static MockCallback cb[1680];
static MockResource rs[900];
static unsigned mode, count, bad;
struct Event { unsigned kind, id, arg, state; };
static Event events[3000], savedEvents[3000];
static unsigned char savedManager[sizeof(manager)];
static Callback* savedA[282];
static Callback* savedB[282];
static unsigned hashBytes(unsigned h, const void* p, unsigned n) {
    const unsigned char* b = static_cast<const unsigned char*>(p);
    for (unsigned i=0;i<n;++i) h = (h ^ b[i]) * 16777619u;
    return h;
}
static void record(unsigned kind, unsigned id, unsigned arg) {
    if (count >= 3000) { bad=1; return; }
    unsigned h=hashBytes(2166136261u,&manager,sizeof(manager));
    h=hashBytes(h,externalA,sizeof(externalA));
    h=hashBytes(h,externalB,sizeof(externalB));
    events[count].kind=kind; events[count].id=id;
    events[count].arg=arg; events[count].state=h; ++count;
}
static void RIFF_THISCALL cleanup(Callback* p) {
    unsigned id=reinterpret_cast<MockCallback*>(p)->id;
    record(0,id,0);
    if (mode==6 && id==0) manager.shaders[0].pixelShader=&rs[899].base;
}
static void* RIFF_THISCALL destroy(Callback* p, unsigned flag) {
    unsigned id=reinterpret_cast<MockCallback*>(p)->id;
    record(1,id,flag);
    if(flag!=1) bad=1;
    if (mode==5 && id==0) manager.callbacks=externalB+1;
    if (mode==6 && id==0) manager.shaders[224].vertexShader=&rs[0].base;
    return p;
}
static uint32_t RIFF_STDCALL resourceRelease(Resource* p) {
    unsigned id=reinterpret_cast<MockResource*>(p)->id;
    record(2,id,0);
    if(mode==6 && id==1) {
        manager.shaders[0].vertexShader=&rs[899].base;
        manager.shaders[0].pixelConstants=&rs[899].base;
    }
    return 0x87654321u;
}
static CallbackVtable cv={destroy,0,0,0,cleanup};
static ResourceVtable rv={0,0,resourceRelease};
static void init(unsigned m) {
    mode=m; count=0; bad=0;
    unsigned char* b=reinterpret_cast<unsigned char*>(&manager);
    for(unsigned i=0;i<sizeof(manager);++i) b[i]=0;
    manager.unknownHeader[0]=0x11223344; manager.unknownHeader[1]=0xaabbccdd;
    for(unsigned i=0;i<1680;++i) { cb[i].base.vtable=&cv; cb[i].id=i; }
    for(unsigned i=0;i<900;++i) { rs[i].base.vtable=&rv; rs[i].id=i; }
    for(unsigned i=0;i<282;++i) externalA[i]=externalB[i]=0;
    externalA[0]=externalA[281]=&cb[1679].base;
    externalB[0]=externalB[281]=&cb[1678].base;
    manager.callbacks= m==4 ? manager.bindings[0] : externalA+1;
    for(unsigned i=0;i<1680;++i) {
        bool use=m==2 || m==4 || m==6 || (m==1 && (i==0 || i==1679)) || (m==3 && i%7==0);
        manager.bindings[i/280][i%280]=use ? &cb[m==3 ? 0 : i].base : 0;
    }
    for(unsigned i=0;i<280;++i) {
        bool use=m==2 || m>=5 || (m==1 && (i==0 || i==279)) || (m==3 && i%3==0);
        if(m!=4) manager.callbacks[i]=use ? &cb[m==3 ? 0 : i].base : 0;
        externalB[i+1]=(i%2==0) ? &cb[i].base : 0;
    }
    for(unsigned i=0;i<225;++i) {
        Resource** fields[4]={&manager.shaders[i].vertexShader,&manager.shaders[i].vertexConstants,&manager.shaders[i].pixelShader,&manager.shaders[i].pixelConstants};
        for(unsigned j=0;j<4;++j) {
            unsigned k=i*4+j;
            bool use=m==2 || m>=4 || (m==1 && (i==0 || i==224)) || (m==3 && k%5==0);
            *fields[j]=use ? &rs[m==3 ? 0 : k].base : 0;
        }
    }
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void copy(void* a,const void* b,unsigned n) {
    unsigned char* x=static_cast<unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) x[i]=y[i];
}
extern "C" int test_main() {
    for(unsigned m=0;m<7;++m) {
        init(m); original_shader_release(&manager);
        if(bad) return 10+m;
        unsigned savedCount=count;
        copy(savedEvents,events,count*sizeof(Event));
        copy(savedManager,&manager,sizeof(manager));
        copy(savedA,externalA,sizeof(externalA)); copy(savedB,externalB,sizeof(externalB));
        init(m); manager.release();
        if(bad || count!=savedCount || !equal(events,savedEvents,count*sizeof(Event))) return 20+m;
        if(!equal(savedManager,&manager,sizeof(manager)) || !equal(savedA,externalA,sizeof(externalA)) || !equal(savedB,externalB,sizeof(externalB))) return 30+m;
        if(manager.unknownHeader[0]!=0x11223344 || manager.unknownHeader[1]!=0xaabbccdd) return 40+m;
        for(unsigned i=0;i<225;++i) {
            ShaderRecord& r=manager.shaders[i];
            if(r.vertexShader || r.vertexConstants || r.pixelShader || r.pixelConstants) return 50+m;
        }
        // Repeated release is valid while the externally owned callback array
        // and mock objects remain alive. Non-first binding tables are retained.
        count=0; original_shader_release(&manager); savedCount=count;
        copy(savedEvents,events,count*sizeof(Event));
        count=0; manager.release();
        if(count!=savedCount || !equal(events,savedEvents,count*sizeof(Event))) return 60+m;
    }
    test_write("shader-release: 7 differential scenarios passed\n",48);
    return 0;
}
