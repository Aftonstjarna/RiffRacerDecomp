#include "impl.hpp"
using namespace riff;
static_assert(sizeof(Vector4)==16 && sizeof(Transform)==64 && sizeof(Sphere)==52, "i386 oracle layouts");
extern "C" void __attribute__((thiscall)) original_sphere_aabb(Sphere*, const Transform*, Vector4*, Vector4*);
extern "C" void test_write(const char*, unsigned);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
static uint32_t bits(float f) { union { float f; uint32_t u; } v; v.f=f; return v.u; }
static float number(uint32_t u) { union { float f; uint32_t u; } v; v.u=u; return v.f; }
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) {
        if(x[i]!=y[i]) return false;
    }
    return true;
}
static void fill(void* a,unsigned n) { unsigned char* p=(unsigned char*)a; for(unsigned i=0;i<n;++i) p[i]=(unsigned char)(i*31+0x53); }
static SphereVtable first, second;
static float margins[3];
static unsigned calls, trace, fault;
static Sphere* expected;
static Transform* active;
static bool mutate;
static float RIFF_THISCALL next(Sphere* s) {
    if(s!=expected || calls>=3) { fault=1; return 0; }
    trace=trace*10+2;
    s->opaque[5] += 7;
    if(mutate) active->rows[3].y=9.0f;
    return margins[calls++];
}
static float RIFF_THISCALL initial(Sphere* s) {
    if(s!=expected || calls) fault=1;
    trace=1; s->vtable=&second; s->opaque[5] += 7;
    return margins[calls++];
}
struct State { uint32_t before[4]; Sphere s; Transform t; Vector4 lo, hi; uint32_t after[3]; };
static void setup(State& s, uint32_t x, uint32_t y, uint32_t z) {
    fill(&s,sizeof(s)); s.s.vtable=&first;
    s.t.rows[3].x=number(x); s.t.rows[3].y=number(y); s.t.rows[3].z=number(z);
}
static int run(uint32_t x,uint32_t y,uint32_t z, unsigned alias) {
    State a,b; setup(a,x,y,z); setup(b,x,y,z);
    Vector4* la=&a.lo; Vector4* ua=&a.hi; Vector4* lb=&b.lo; Vector4* ub=&b.hi;
    if(alias==1) ua=la,ub=lb;
    if(alias==2) la=&a.t.rows[3],lb=&b.t.rows[3];
    if(alias==3) ua=&a.t.rows[3],ub=&b.t.rows[3];
    if(alias==4) la=&a.t.rows[0],lb=&b.t.rows[0];
    calls=trace=fault=0; expected=&a.s; active=&a.t;
    original_sphere_aabb(&a.s,&a.t,la,ua);
    if(calls!=3 || trace!=122 || fault) return 1;
    calls=trace=fault=0; expected=&b.s; active=&b.t;
    b.s.aabb(&b.t,lb,ub);
    if(calls!=3 || trace!=122 || fault) return 2;
    if(!equal(&a,&b,sizeof(a))) return 3;
    // Check all unrelated bytes independently, not only differential agreement.
    State pristine; setup(pristine,x,y,z);
    pristine.s.vtable=&second; pristine.s.opaque[5]+=21;
    if(!equal(&a.s,&pristine.s,sizeof(Sphere)) || !equal(a.before,pristine.before,sizeof(a.before)) || !equal(a.after,pristine.after,12)) return 4;
    for(unsigned i=0;i<3;++i) if(!(alias==4 && i==0) && !equal(&a.t.rows[i],&pristine.t.rows[i],16)) return 5;
    if(alias!=2 && alias!=3 && !mutate && !equal(&a.t.rows[3],&pristine.t.rows[3],16)) return 6;
    if(bits(ua->w)!=0 || bits(ub->w)!=0 || bits(la->w)!=0) return 7;
    return 0;
}
extern "C" int test_main() {
    first.margin=initial; second.margin=next;
    const uint32_t values[]={0,0x80000000u,0x3f800000u,0xc0800000u,1,0x007fffffu,0x00800000u,0x7f7fffffu,0xff7fffffu,0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u};
    unsigned saved=test_get_mxcsr();
    unsigned count=0;
    for(unsigned mode=0;mode<4;++mode) {
        test_set_mxcsr(0x1f80u | (mode<<13));
        for(unsigned i=0;i<13;++i) for(unsigned j=0;j<13;++j) {
            margins[0]=number(values[j]); margins[1]=number(values[(j+3)%13]); margins[2]=number(values[(j+7)%13]);
            for(unsigned alias=0;alias<5;++alias) {
                mutate=(i%3==0); int r=run(values[i],values[(i+4)%13],values[(i+8)%13],alias);
                if(r) { test_set_mxcsr(saved); return 10+r; } ++count;
            }
        }
    }
    // Explicit finite expected result verifies the axis/call mapping and zeros.
    margins[0]=1; margins[1]=2; margins[2]=3; mutate=false;
    State s; setup(s,bits(10),bits(20),bits(30)); calls=trace=fault=0; expected=&s.s; active=&s.t;
    s.s.aabb(&s.t,&s.lo,&s.hi);
    if(s.lo.x!=7 || s.lo.y!=18 || s.lo.z!=29 || s.hi.x!=13 || s.hi.y!=22 || s.hi.z!=31) return 30;
    test_set_mxcsr(saved);
    if(count!=3380) return 31;
    const char message[]="sphere-aabb: 3380 differential cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
