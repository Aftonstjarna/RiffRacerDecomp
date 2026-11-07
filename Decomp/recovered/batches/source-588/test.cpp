#include "impl.hpp"
using namespace riff;
extern "C" bool RIFF_THISCALL original_device_bind_pending_targets(Device*);
extern "C" bool RIFF_THISCALL original_device_pending_targets_prepare(Device*);
extern "C" void RIFF_THISCALL original_device_pending_targets_cleanup(Device*);
bool RIFF_THISCALL Device::prepare_pending() { return original_device_pending_targets_prepare(this); }
void RIFF_THISCALL Device::cleanup_pending() { original_device_pending_targets_cleanup(this); }
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memset(void* p,int v,unsigned n) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i)b[i]=(unsigned char)v; return p; }
extern "C" void* memcpy(void* p,const void* q,unsigned n) { unsigned char* b=(unsigned char*)p; const unsigned char* a=(const unsigned char*)q; for(unsigned i=0;i<n;++i)b[i]=a[i]; return p; }
static Object gpu[7];
static void* table[48];
static Device* active;
static unsigned logdata[256], count, step, fail_step, errors;
static int32_t result;
static unsigned id(Object* p) {
    for(unsigned i=0;i<7;++i) { if(p==&gpu[i]) return i+1; }
    return p ? 99 : 0;
}
static void log(unsigned x) { logdata[count++]=x; }
static int32_t status() { ++step; return step==fail_step ? (int32_t)0x80004005u : result; }
static uint32_t RIFF_STDCALL release(Object* p) { log(100+id(p)); return 0; }
static int32_t RIFF_STDCALL texture(Object*,unsigned w,unsigned h,unsigned levels,unsigned usage,unsigned format,unsigned pool,Object** out,void* shared) {
    log(1); log(w); log(h); log(levels); log(usage); log(format); log(pool); log(shared?1:0);
    *out = out==&active->resources[0] ? &gpu[0] : &gpu[1]; return status();
}
static int32_t RIFF_STDCALL surface(Object* p,unsigned level,Object** out) { log(2);log(id(p));log(level); *out=p==&gpu[0]?&gpu[2]:&gpu[3];return status(); }
static int32_t RIFF_STDCALL depth(Object*,unsigned w,unsigned h,unsigned format,unsigned ms,unsigned quality,unsigned discard,Object** out,void* shared) {
    log(3);log(w);log(h);log(format);log(ms);log(quality);log(discard);log(shared?1:0);*out=&gpu[4];return status();
}
static int32_t RIFF_STDCALL aux(Object*,unsigned w,unsigned h,unsigned format,unsigned pool,Object** out,void* shared) {
    log(4);log(w);log(h);log(format);log(pool);log(shared?1:0);*out=&gpu[5];return status();
}
static int32_t RIFF_STDCALL color(Object*,unsigned index,Object* p) { log(5);log(index);log(id(p));return status(); }
static int32_t RIFF_STDCALL bind_depth(Object*,Object* p) { log(6);log(id(p));return status(); }
static int32_t RIFF_STDCALL viewport(Object*,Viewport* p) { log(7); if(p!=&active->viewport) ++errors; const uint32_t* v=(const uint32_t*)p;for(unsigned i=0;i<6;++i)log(v[i]);return status(); }
static void put(Device& d,unsigned offset,unsigned value) { memcpy((unsigned char*)&d+offset,&value,4); }
static void setup(Device& d,unsigned pending,unsigned mode,unsigned index,unsigned width) {
    memset(&d,0xa5,sizeof d);d.pending=(uint8_t)pending;d.mode=(uint8_t)mode;d.color_index=index;d.graphics=&gpu[6];
    for(unsigned i=0;i<6;++i)d.resources[i]=0;
    put(d,0xd8,width);put(d,0x1f8,21);put(d,0x1e0,75);
}
extern "C" int test_main() {
    unsigned fs[8]={0xdeadbeef};if(test_install_fs(fs)!=0)return 1;
    for(unsigned i=0;i<7;++i)gpu[i].vtable=table;
    table[2]=(void*)release;table[0x5c/4]=(void*)texture;table[0x48/4]=(void*)surface;
    table[0x74/4]=(void*)depth;table[0x90/4]=(void*)aux;table[0x94/4]=(void*)color;table[0x9c/4]=(void*)bind_depth;table[0xbc/4]=(void*)viewport;
    const unsigned widths[]={0,1,15,16,8191,8192,8193,0xffffffffu};
    const unsigned modes[]={0,1,2,255};
    for(unsigned m=0;m<4;++m)for(unsigned w=0;w<8;++w)for(unsigned f=0;f<10;++f)for(unsigned r=0;r<3;++r)for(unsigned pending=0;pending<2;++pending)for(unsigned index=0;index<4;++index)for(unsigned seeded=0;seeded<2;++seeded) {
        Device a,b;setup(a,pending,modes[m],m?index:0xffffffffu,widths[w]);
        if(seeded)for(unsigned i=0;i<6;++i)a.resources[i]=&gpu[i];
        memcpy(&b,&a,sizeof a);
        unsigned saved[256];fail_step=f;result=r==0?0:(r==1?1:0x7fffffff);count=step=0;active=&a;
        bool ar=original_device_bind_pending_targets(&a);if(test_get_fs_head()!=fs[0])return 2;
        unsigned n=count;memcpy(saved,logdata,n*4);count=step=0;active=&b;
        bool br=b.bind_pending();if(test_get_fs_head()!=fs[0])return 3;
        if(ar!=br||count!=n||errors)return 4;
        for(unsigned i=0;i<n;++i)if(saved[i]!=logdata[i])return 5;
        for(unsigned i=0;i<sizeof a;++i)if(((unsigned char*)&a)[i]!=((unsigned char*)&b)[i])return 6;
        if(!pending && (ar || n))return 7;
        if(pending && b.pending)return 8;
        if(br && (b.bound!=1 || b.bound_mode!=modes[m]))return 9;
    }
    return 0;
}
