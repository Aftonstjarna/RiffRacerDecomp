#include "impl.hpp"
using namespace riff;
extern "C" bool __attribute__((thiscall)) original_shader_pair_create(ShaderPair*, const uint32_t*, const uint32_t*);
extern "C" void test_write(const char*, unsigned);
// Local verification linker maps these writable dependency slots, not code.
GetConstants oracle_import __attribute__((section(".oracle_import"),aligned(4)));
DeviceOwner* oracle_owner __attribute__((section(".oracle_owner"),aligned(4)));
static void* resourceVT[3];
static void* deviceVT[107];
static Interface resources[8], dev;
static DeviceOwner owner;
static uint32_t vertexCode[2]={0xfffe0300u,0xffffu}, pixelCode[2]={0xffff0300u,0xffffu};
struct Guarded { uint32_t before[4]; ShaderPair pair; uint32_t after[4]; };
static ShaderPair* active;
static unsigned mutate;
static Interface secondDev;
static DeviceOwner secondOwner;
static int32_t results[4];
static unsigned writeMask, nullMask, stage, errors, eventCount, events[12];
static Interface* snapshots[12][4];
static void event(unsigned n) {
    if(eventCount>=12) { errors=1; return; }
    snapshots[eventCount][0]=active->vertex;
    snapshots[eventCount][1]=active->vertexConstants;
    snapshots[eventCount][2]=active->pixel;
    snapshots[eventCount][3]=active->pixelConstants;
    events[eventCount++]=n;
}
static uint32_t RIFF_STDCALL releaseSpy(Interface* p) {
    unsigned id=8;
    for(unsigned i=0;i<8;++i) if(p==&resources[i]) id=i;
    if(id==8) errors=1;
    event(10+id);
    // A table Release can change the vertex slot before the subsequent load.
    if(mutate && (id==1 || id==5)) active->vertex=&resources[7];
    return 0xffffffffu;
}
static int32_t allocate(unsigned s, const uint32_t* code, Interface** out) {
    if(stage!=s || code!=(s<2?vertexCode:pixelCode)) errors=1;
    Interface** expected=s==0?&active->vertex:s==1?&active->vertexConstants:s==2?&active->pixel:&active->pixelConstants;
    if(out!=expected) errors=1;
    event(s); ++stage;
    if(mutate && s==1) oracle_owner=&secondOwner;
    if(writeMask&(1u<<s)) *out=(nullMask&(1u<<s))?0:&resources[s];
    return results[s];
}
static int32_t RIFF_STDCALL createVertex(Interface* d,const uint32_t* c,Interface** o) { if(d!=&dev) errors=1; return allocate(0,c,o); }
static int32_t RIFF_STDCALL createPixel(Interface* d,const uint32_t* c,Interface** o) { if(d!=(mutate?&secondDev:&dev)) errors=1; return allocate(2,c,o); }
static int32_t RIFF_STDCALL constants(const uint32_t* c,Interface** o) { return allocate(stage,c,o); }
static void init(Guarded& g) {
    for(unsigned i=0;i<4;++i) {g.before[i]=0xaabbcc00+i; g.after[i]=0x12345670+i;}
    g.pair.vertex=&resources[4]; g.pair.vertexConstants=&resources[5];
    g.pair.pixel=&resources[6]; g.pair.pixelConstants=&resources[7];
}
static bool equal(const Guarded& a,const Guarded& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return true;
}
static bool run(bool mapped) {
    Guarded a,b; init(a); init(b);
    stage=errors=eventCount=0; active=&a.pair; oracle_owner=&owner;
    bool result=a.pair.createUsing(vertexCode,pixelCode,&oracle_owner,&oracle_import);
    if(errors) return false;
    // Independently assert reached calls, return and per-path cleanup/untouched slots.
    Guarded expected; init(expected);
    Interface** slots[4]={&expected.pair.vertex,&expected.pair.vertexConstants,&expected.pair.pixel,&expected.pair.pixelConstants};
    unsigned reached=results[0]<0?1:results[1]<0?2:results[2]<0?3:4;
    for(unsigned i=0;i<reached;++i) if(writeMask&(1u<<i)) *slots[i]=(nullMask&(1u<<i))?0:&resources[i];
    if(reached==2) expected.pair.vertex=0;
    if(reached>=3 && (results[2]<0 || results[3]<0)) {
        expected.pair.vertex=expected.pair.vertexConstants=0;
        if(reached==4) expected.pair.pixel=0;
    }
    bool wanted=reached==4 && results[3]>=0;
    if(result!=wanted || !equal(a,expected)) return false;
    if(!mapped) return true;
    Interface* savedSnapshots[12][4];
    unsigned savedEvents[12], count=eventCount;
    for(unsigned i=0;i<count;++i) for(unsigned j=0;j<4;++j) savedSnapshots[i][j]=snapshots[i][j];
    for(unsigned i=0;i<count;++i) savedEvents[i]=events[i];
    stage=errors=eventCount=0; active=&b.pair; oracle_owner=&owner;
    bool original=original_shader_pair_create(&b.pair,vertexCode,pixelCode);
    if(errors || original!=result || eventCount!=count || !equal(a,b)) return false;
    for(unsigned i=0;i<count;++i) {
        if(events[i]!=savedEvents[i]) return false;
        for(unsigned j=0;j<4;++j) if(snapshots[i][j]!=savedSnapshots[i][j]) return false;
    }
    return true;
}
extern "C" int test_main() {
    resourceVT[2]=reinterpret_cast<void*>(releaseSpy);
    for(unsigned i=0;i<8;++i) resources[i].vtable=resourceVT;
    deviceVT[0x16c/4]=reinterpret_cast<void*>(createVertex);
    deviceVT[0x1a8/4]=reinterpret_cast<void*>(createPixel);
    dev.vtable=deviceVT; secondDev.vtable=deviceVT; owner.device=&dev; secondOwner.device=&secondDev; oracle_owner=&owner; oracle_import=constants;
    bool mapped=reinterpret_cast<uint32_t>(&oracle_owner)==0xbfcc44u && reinterpret_cast<uint32_t>(&oracle_import)==0x92d64cu;
    const int32_t hr[]={0,1,2147483647,(-2147483647-1),-1};
    for(mutate=0;mutate<2;++mutate) for(unsigned fail=0;fail<5;++fail) for(unsigned h=0;h<5;++h)
      for(writeMask=0;writeMask<16;++writeMask) for(nullMask=0;nullMask<16;++nullMask) {
        for(unsigned s=0;s<4;++s) results[s]=(s==fail)?hr[h]:0;
        // Unconditional Release requires nonnull vertex/pixel at those branches.
        if(results[0]>=0 && results[1]<0 && (writeMask&1) && (nullMask&1)) continue;
        if(results[0]>=0 && results[1]>=0 && results[2]>=0 && results[3]<0 && (writeMask&4) && (nullMask&4)) continue;
        if(!run(mapped)) return 1;
      }
    if(mapped) { const char m[]="PASS: shader pair original differential cases\n"; test_write(m,sizeof(m)-1); }
    else { const char m[]="LIMIT: fixed dependency slots unmapped; C++ assertions only\n"; test_write(m,sizeof(m)-1); }
    return 0;
}
