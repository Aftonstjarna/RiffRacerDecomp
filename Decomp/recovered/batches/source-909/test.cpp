#include "impl.hpp"
extern "C" bool __attribute__((thiscall)) original_simplex_solver_contains_vertex(const SimplexSolver*, const SimplexVector*);
extern "C" unsigned test_get_mxcsr();
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[16];
static const unsigned fs_head = 0x13572468;
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
static float& component(SimplexVector& v, int k) { if(k==0)return v.x;if(k==1)return v.y;if(k==2)return v.z;return v.w; }
static float bits(uint32_t u) { float f; __builtin_memcpy(&f,&u,4); return f; }
static void copy(void* a,const void* b,unsigned n) { unsigned char* d=(unsigned char*)a; const unsigned char* s=(const unsigned char*)b; for(unsigned i=0;i<n;++i)d[i]=s[i]; }
static bool same(const void* a,const void* b,unsigned n) {const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
struct Fixture { unsigned pre[4]; SimplexSolver solver; unsigned post[12]; };
static int check(Fixture& f, SimplexVector& v, int expected, unsigned mode=0x1f80) {
    Fixture before; SimplexVector vb; copy(&before,&f,sizeof f);copy(&vb,&v,sizeof v);
    test_set_mxcsr(mode); bool original=original_simplex_solver_contains_vertex(&f.solver,&v); unsigned om=test_get_mxcsr();
    if(test_get_fs_head()!=fs_head)return 4;
    if(!same(&before,&f,sizeof f)||!same(&vb,&v,sizeof v)) return 1;
    test_set_mxcsr(mode); bool recovered=f.solver.contains_vertex(&v);unsigned rm=test_get_mxcsr();
    if(original!=recovered || (expected>=0 && original!=(expected!=0)) || om!=rm) return 2;
    if(!same(&before,&f,sizeof f)||!same(&vb,&v,sizeof v))return 3;
    return 0;
}
extern "C" int test_main() {
    unsigned saved=test_get_mxcsr();
    fs_storage[0]=fs_head;
    if(test_install_fs(fs_storage)!=0)return 99;
    Fixture f; unsigned char* p=(unsigned char*)&f;
    for(unsigned i=0;i<sizeof f;++i)p[i]=(unsigned char)(i*37+13);
    SimplexSolver& s=f.solver; SimplexVector v={1,2,3,4};
    s.cached_vertex=SimplexVector{90,91,92,93};s.distance_squared_threshold=0;
    for(int i=0;i<4;++i)s.vertices[i]=SimplexVector{20.0f+i,30,40,50};
#define CHECK(e) do { if(check(f,v,e)) return __LINE__; } while(0)
    s.vertex_count=(-2147483647-1);CHECK(0);s.vertex_count=-1;CHECK(0);s.vertex_count=0;CHECK(0);
    s.cached_vertex=v;CHECK(1);
    for(int k=0;k<4;++k){s.cached_vertex=v; component(s.cached_vertex,k)+=1;CHECK(0);}
    s.cached_vertex=SimplexVector{90,91,92,93};s.vertex_count=4;
    s.vertices[3]=v;s.vertices[3].w=123;CHECK(1);
    s.vertices[3].x=2;s.distance_squared_threshold=1;CHECK(1);
    s.distance_squared_threshold=bits(0x3f7fffff);CHECK(0);
    s.distance_squared_threshold=-1;CHECK(0);
    s.distance_squared_threshold=bits(0x7f800000);CHECK(1);
    s.distance_squared_threshold=bits(0x7fc12345);CHECK(0);
    s.distance_squared_threshold=0;s.vertices[0]=v;s.vertices[3].x=bits(0x7fc12345);CHECK(1);
    s.vertex_count=0;s.cached_vertex=v;
    v.x=0;s.cached_vertex.x=bits(0x80000000);CHECK(1);
    for(int k=0;k<4;++k){v=SimplexVector{1,2,3,4};s.cached_vertex=v;component(v,k)=bits(0x7fc12345);component(s.cached_vertex,k)=component(v,k);CHECK(0);}
    v=SimplexVector{bits(1),0,0,0};s.cached_vertex=SimplexVector{90,91,92,93};s.vertices[0]=SimplexVector{0,0,0,0};s.vertex_count=1;
    for(unsigned mode=0;mode<4;++mode)if(check(f,v,-1,0x1f80|(mode<<13)))return 90;
    for(unsigned mode=0;mode<4;++mode)if(check(f,v,-1,0x1f80|((mode&1)?0x8000:0)|((mode&2)?0x40:0)))return 92;
    s.vertex_count=1;s.vertices[0]=SimplexVector{1,2,3,4};s.distance_squared_threshold=0;
    if(check(f,s.vertices[0],1))return 93;
    v=SimplexVector{bits(0x7f800000),0,0,0};s.vertices[0]=v;
    CHECK(0); // infinity minus itself yields NaN, not zero distance
    s.cached_vertex=v;CHECK(1); // exact cached infinities do compare equal
    s.cached_vertex=SimplexVector{90,91,92,93};s.distance_squared_threshold=bits(0x7f800000);
    s.vertices[0]=SimplexVector{0,0,0,0};CHECK(1); // infinity >= infinity
    // Exercise every legal active slot and the inclusive distance boundary.
    v=SimplexVector{1,2,3,4};
    s.cached_vertex=SimplexVector{90,91,92,93};
    for(int count=1;count<=4;++count){
        s.vertex_count=count;
        for(int j=0;j<4;++j)s.vertices[j]=SimplexVector{20,30,40,50};
        s.vertices[count-1]=v;s.vertices[count-1].w=bits(0x7f812345);
        s.distance_squared_threshold=bits(0x80000000);CHECK(1);
    }
    // With an empty simplex, UCOMISS must leave quiet NaNs quiet, signal
    // signaling NaNs, and skip X entirely when W already differs.
    s.vertex_count=0;s.cached_vertex=v;
    v.x=bits(0x7f812345);s.cached_vertex.w=5;CHECK(0);
    s.cached_vertex.w=v.w;CHECK(0);
    v.x=bits(0x7fc12345);CHECK(0);
    // Existing sticky MXCSR flags are preserved by both implementations.
    v=SimplexVector{1,2,3,4};s.cached_vertex=v;
    if(check(f,v,1,0x1fbf))return 94;
    uint32_t rng=12345;
    for(int n=0;n<1200;++n){
        s.vertex_count=n%6-1;
        for(int j=0;j<4;++j){for(int k=0;k<4;++k){rng=rng*1664525+1013904223;component(s.vertices[j],k)=bits(rng);}}
        
        for(int k=0;k<4;++k){rng=rng*1664525+1013904223;component(v,k)=bits(rng);rng=rng*1664525+1013904223;component(s.cached_vertex,k)=bits(rng);}
        rng=rng*1664525+1013904223;s.distance_squared_threshold=bits(rng);
        if(check(f,v,-1))return 91;
    }
    test_set_mxcsr(saved);test_write("PASS\n",5);return 0;
}
