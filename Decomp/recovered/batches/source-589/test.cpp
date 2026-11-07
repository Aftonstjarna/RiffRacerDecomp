#include "impl.hpp"
using namespace riff;
extern "C" bool RIFF_THISCALL original_device_pending_targets_prepare(Device*);
extern "C" void RIFF_THISCALL original_device_pending_targets_cleanup(Device*);
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
static unsigned failure_output;
static unsigned id(Object* p) {
    for(unsigned i=0;i<7;++i) { if(p==&gpu[i]) return i+1; }
    return p ? 99 : 0;
}
static void log(unsigned x) { logdata[count++]=x; }
static int32_t status() { ++step; return step==fail_step ? (int32_t)0x80004005u : result; }
static uint32_t RIFF_STDCALL release(Object* p) {
    log(100+id(p));
    // Capture state during Release, before cleanup clears the current slot.
    for(unsigned i=0;i<6;++i)log(id(active->resources[i]));
    const unsigned char* bytes=(const unsigned char*)&active->viewport;
    for(unsigned i=0;i<24;++i)log(bytes[i]);
    return 0;
}
static void output(Object** out,Object* value) {
    if(step+1!=fail_step || failure_output==0)*out=value;
    else if(failure_output==1)*out=0;
    // failure_output==2 models an untouched output on failure.
}
static int32_t RIFF_STDCALL texture(Object* receiver,unsigned w,unsigned h,unsigned levels,unsigned usage,unsigned format,unsigned pool,Object** out,void* shared) {
    if(receiver!=active->graphics || (out!=&active->resources[0]&&out!=&active->resources[1]))++errors;
    log(1); log(w); log(h); log(levels); log(usage); log(format); log(pool); log(shared?1:0);
    output(out,out==&active->resources[0] ? &gpu[0] : &gpu[1]); return status();
}
static int32_t RIFF_STDCALL surface(Object* p,unsigned level,Object** out) { log(2);log(id(p));log(level); output(out,p==&gpu[0]?&gpu[2]:&gpu[3]);return status(); }
static int32_t RIFF_STDCALL depth(Object* receiver,unsigned w,unsigned h,unsigned format,unsigned ms,unsigned quality,unsigned discard,Object** out,void* shared) {
    if(receiver!=active->graphics || out!=&active->resources[4])++errors;
    log(3);log(w);log(h);log(format);log(ms);log(quality);log(discard);log(shared?1:0);output(out,&gpu[4]);return status();
}
static int32_t RIFF_STDCALL aux(Object* receiver,unsigned w,unsigned h,unsigned format,unsigned pool,Object** out,void* shared) {
    if(receiver!=active->graphics || out!=&active->resources[5])++errors;
    log(4);log(w);log(h);log(format);log(pool);log(shared?1:0);output(out,&gpu[5]);return status();
}
static void setup(Device& d,unsigned mode,unsigned width) {
    memset(&d,0xa5,sizeof d); d.mode=(uint8_t)mode;d.graphics=&gpu[6];
    for(unsigned i=0;i<6;++i)d.resources[i]=0;
    d.requested_width=width;d.color_format=21;d.depth_format=75;
}
extern "C" int test_main() {
    unsigned fs[8]={0xdeadbeef};if(test_install_fs(fs)!=0)return 1;
    for(unsigned i=0;i<7;++i)gpu[i].vtable=table;
    table[2]=(void*)release;table[0x5c/4]=(void*)texture;table[0x48/4]=(void*)surface;
    table[0x74/4]=(void*)depth;table[0x90/4]=(void*)aux;
    const unsigned widths[]={0,1,2,15,16,17,1920,8191,8192,8193,0x80000000u,0xffffffffu};
    const unsigned modes[]={0,1,2,255};
    for(unsigned m=0;m<4;++m)for(unsigned w=0;w<12;++w)for(unsigned f=0;f<8;++f)for(unsigned r=0;r<3;++r)for(unsigned seeded=0;seeded<2;++seeded)for(unsigned fo=0;fo<3;++fo) {
        Device a,b,before;setup(a,modes[m],widths[w]);
        if(seeded)for(unsigned i=0;i<6;++i)a.resources[i]=&gpu[i];
        memcpy(&b,&a,sizeof a);memcpy(&before,&a,sizeof a);
        unsigned saved[256];failure_output=fo;fail_step=f;result=r==0?0:(r==1?1:0x7fffffff);count=step=0;active=&a;
        bool ar=original_device_pending_targets_prepare(&a);if(test_get_fs_head()!=fs[0])return 2;
        unsigned n=count;memcpy(saved,logdata,n*4);count=step=0;active=&b;
        bool br=b.prepare_pending();if(test_get_fs_head()!=fs[0])return 3;
        if(ar!=br||count!=n||errors)return 4;
        for(unsigned i=0;i<n;++i)if(saved[i]!=logdata[i])return 5;
        for(unsigned i=0;i<sizeof a;++i) {
            if(((unsigned char*)&a)[i]!=((unsigned char*)&b)[i])return 6;
            if((i<4||i>=0x34)&&((unsigned char*)&b)[i]!=((unsigned char*)&before)[i])return 7;
        }
        if(br) {
            unsigned width=widths[w]<8192?widths[w]:8192;
            if(b.viewport.x||b.viewport.y||b.viewport.width!=width||b.viewport.height!=(width*9>>4)||b.viewport.minimum!=0||b.viewport.maximum!=1)return 8;
            if(!m&&(b.resources[1]!=before.resources[1]||b.resources[3]!=before.resources[3]))return 9;
        } else {
            for(unsigned i=0;i<6;++i)if(b.resources[i])return 10;
            for(unsigned i=0x1c;i<0x34;++i)if(((unsigned char*)&b)[i])return 11;
        }
    }
    return 0;
}
