#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_device_pending_targets_cleanup(DevicePendingTargets*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
struct Fixture { unsigned before[4]; DevicePendingTargets device; unsigned after[12]; };
static Fixture fixture;
static unsigned char trace[8][sizeof(Fixture)];
static unsigned ids[8], calls, mutation, bad;
static ComResource resources[6];
static void copy(void* d, const void* s, unsigned n) {
    unsigned char* a = (unsigned char*)d;
    const unsigned char* b = (const unsigned char*)s;
    for(unsigned i=0;i<n;++i) a[i]=b[i];
}
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x=(const unsigned char*)a;
    const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static uint32_t RIFF_STDCALL release_resource(ComResource* p) {
    if(calls>=8) { bad=1; return 0; }
    unsigned id=0;
    while(id<6 && p!=&resources[id]) ++id;
    if(id==6) bad=1;
    ids[calls]=id;
    copy(trace[calls], &fixture, sizeof fixture);
    ++calls;
    if(mutation && calls==1) {
        // When readback is present, its replacement is overwritten after Release;
        // replacement/removal of lower slots affects subsequent releases.
        fixture.device.readback_surface=&resources[0];
        fixture.device.depth_surface=0;
        fixture.device.color_surface[0]=&resources[5];
        fixture.device.color_texture[0]=&resources[4];
        fixture.device.viewport.width=0xdeadbeef;
        fixture.device.flags[0]=0x17;
    }
    return 0x80000000u + calls; // ignored even when nonzero/high bit set
}
static ComVtable vt={0,0,release_resource};
static void setup(unsigned mask, bool alias) {
    unsigned char* b=(unsigned char*)&fixture;
    for(unsigned i=0;i<sizeof fixture;++i) b[i]=(unsigned char)(i*37+91);
    ComResource* p[6];
    for(unsigned i=0;i<6;++i) {
        resources[i].vtable=&vt;
        p[i]=(mask&(1u<<i)) ? &resources[alias?0:i] : 0;
    }
    fixture.device.color_texture[0]=p[0]; fixture.device.color_texture[1]=p[1];
    fixture.device.color_surface[0]=p[2]; fixture.device.color_surface[1]=p[3];
    fixture.device.depth_surface=p[4]; fixture.device.readback_surface=p[5];
    calls=bad=0;
    for(unsigned i=0;i<8;++i) { ids[i]=99; for(unsigned j=0;j<sizeof fixture;++j) trace[i][j]=0; }
}
extern "C" int test_main() {
    unsigned fs_storage[8]={0x13579bdf,0,0,0,0,0,0,0};
    if(test_install_fs(fs_storage)!=0) return 1;
    for(unsigned mode=0;mode<3;++mode) for(unsigned mask=0;mask<64;++mask) {
        mutation=(mode==2);
        setup(mask,mode==1);
        Fixture initial; copy(&initial,&fixture,sizeof fixture);
        original_device_pending_targets_cleanup(&fixture.device);
        if(test_get_fs_head()!=fs_storage[0] || bad) return 2;
        Fixture expected; copy(&expected,&fixture,sizeof fixture);
        unsigned expected_calls=calls, expected_ids[8];
        unsigned char expected_trace[8][sizeof(Fixture)];
        copy(expected_ids,ids,sizeof ids); copy(expected_trace,trace,sizeof trace);
        setup(mask,mode==1);
        fixture.device.cleanup();
        if(bad || calls!=expected_calls || !same(&fixture,&expected,sizeof fixture) ||
           !same(ids,expected_ids,sizeof ids) || !same(trace,expected_trace,sizeof trace)) return 3;
        // Independent checks of untouched guards and the zeroed owned region.
        if(!same(fixture.before,initial.before,sizeof initial.before) ||
           !same(fixture.after,initial.after,sizeof initial.after)) return 4;
        const unsigned char* b=(const unsigned char*)&fixture.device;
        for(unsigned i=mutation?0x1c:4;i<0x34;++i) if(b[i]) return 5;
        if(!mutation) {
            unsigned n=0;
            for(int i=5;i>=0;--i) if(mask&(1u<<i)) {
                if(ids[n++] != (mode==1?0u:(unsigned)i)) return 9;
            }
            if(calls!=n) return 10;
        }
        if(!mutation || !calls) {
            if(!same(fixture.device.flags,initial.device.flags,4)) return 6;
        }
        // A repeated cleanup performs no Release and retains flags/guards.
        if(mutation) continue;
        calls=0;
        original_device_pending_targets_cleanup(&fixture.device);
        if(calls || test_get_fs_head()!=fs_storage[0] || !same(&fixture,&expected,sizeof fixture)) return 7;
        fixture.device.cleanup();
        if(calls || !same(&fixture,&expected,sizeof fixture)) return 8;
    }
    test_write("pending targets: passed\n",24);
    return 0;
}
