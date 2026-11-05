#include "impl.hpp"
extern "C" Vector3* __attribute__((thiscall)) original_vector3_construct_refs(Vector3*, const float&, const float&, const float&);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
static void put(float& f, uint32_t bits) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&f);
    for (unsigned i=0;i<4;++i) p[i] = static_cast<unsigned char>(bits >> (8*i));
}
static uint32_t get(const float& f) {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&f);
    uint32_t b=0; for(unsigned i=0;i<4;++i) b |= uint32_t(p[i]) << (8*i); return b;
}
struct Guarded { uint32_t before[4]; Vector3 v; uint32_t after[4]; float inputs[3]; };
static float& field(Vector3& v, unsigned i) {
    switch(i) {case 0:return v.x; case 1:return v.y; case 2:return v.z; default:return v.fourth;}
}
static void init(Guarded& g, unsigned seed) {
    for(unsigned i=0;i<4;++i) {g.before[i]=0xa1234000+i;g.after[i]=0xfedc0000+i;put(field(g.v,i),seed+0x11111111u*i);}
}
static bool equal(const Guarded& a, const Guarded& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i])return false;
    return true;
}
extern "C" int test_main() {
    const uint32_t values[]={0,0x80000000u,0x3f800000u,0xbf800000u,0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,1,0x807fffffu,0x7f7fffffu,0x00800000u};
    const unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<4;++mode) {
        const unsigned control=0x1f80u | ((mode&1)?0x8040u:0) | ((mode&2)?0x6000u:0);
        for(unsigned n=0;n<12;++n) {
            // Each argument independently selects any destination field or its
            // own external input: exhaustive aligned alias combinations.
            for(unsigned a=0;a<5;++a)for(unsigned b=0;b<5;++b)for(unsigned c=0;c<5;++c) {
                Guarded p,q; init(p,values[n]); init(q,values[n]);
                for(unsigned i=0;i<3;++i){put(p.inputs[i],values[(n+i)%12]);put(q.inputs[i],values[(n+i)%12]);}
                const float& pa=a<4?field(p.v,a):p.inputs[0]; const float& qa=a<4?field(q.v,a):q.inputs[0];
                const float& pb=b<4?field(p.v,b):p.inputs[1]; const float& qb=b<4?field(q.v,b):q.inputs[1];
                const float& pc=c<4?field(p.v,c):p.inputs[2]; const float& qc=c<4?field(q.v,c):q.inputs[2];
                test_set_mxcsr(control);
                if(original_vector3_construct_refs(&p.v,pa,pb,pc)!=&p.v)return 1;
                if(test_get_mxcsr()!=control)return 2;
                if(q.v.construct_refs(qa,qb,qc)!=&q.v)return 3;
                if(test_get_mxcsr()!=control)return 4;
                if(!equal(p,q) || get(q.v.fourth)!=0)return 5;
                for(unsigned i=0;i<4;++i)if(q.before[i]!=0xa1234000+i || q.after[i]!=0xfedc0000+i)return 6;
                for(unsigned i=0;i<3;++i)if(get(q.inputs[i])!=values[(n+i)%12])return 7;
            }
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
