#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_presentation_parameters(PresentationState*);
extern "C" void __attribute__((thiscall)) original_viewport_size(PresentationState*,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
void RR_THISCALL PresentationState::setViewportSize(uint32_t w,uint32_t h) { original_viewport_size(this,w,h); }
extern "C" void* memset(void* p,int c,unsigned n) { unsigned char* d=(unsigned char*)p; for(unsigned i=0;i<n;++i)d[i]=(unsigned char)c; return p; }
extern "C" void* memcpy(void* p,const void* s,unsigned n) { unsigned char* d=(unsigned char*)p; const unsigned char* a=(const unsigned char*)s; for(unsigned i=0;i<n;++i)d[i]=a[i]; return p; }
static uint32_t seed=0x12345678;
static uint32_t next() { seed=seed*1664525u+1013904223u; return seed; }
static int run(DisplayMode* m,unsigned count,uint32_t w,uint32_t h,unsigned fullscreen,unsigned fit=0,unsigned tail=0) {
    alignas(4) PresentationState a,b;
    unsigned char before[sizeof(a)];
    for(unsigned i=0;i<sizeof(a);++i)a.storage[i]=(unsigned char)next();
    a.word(0x27c)=(uint32_t)(uintptr_t)m;
    a.word(0x280)=(uint32_t)(uintptr_t)m+count*24+tail;
    a.word(0x48c)=w; a.word(0x490)=h;
    a.storage[0x4bf]=(unsigned char)fullscreen; a.storage[0x4b8]=(unsigned char)fit;
    memcpy(&b,&a,sizeof(a));
    DisplayMode copy[20]; memcpy(copy,m,count*24);
    memcpy(before,&a,sizeof(a));
    original_presentation_parameters(&a);
    b.updatePresentationParameters();
    for(unsigned i=0;i<sizeof(a);++i) if(a.storage[i]!=b.storage[i])return 1;
    for(unsigned i=0;i<count*24;++i)if(((unsigned char*)m)[i]!=((unsigned char*)copy)[i])return 2;
    // Independent assertions on copies and unconditional writes.
    if(b.word(0x23c)!=b.word(0x48c)||b.word(0x1bc)!=b.word(0x490)||b.word(0x1e8)!=0||b.word(0x1d8)!=(fullscreen==0))return 3;
    // Comparison covers every unknown byte, including vector pointers and flags.
    const unsigned changed[]={0x48c,0x490,0x494,0x498,0x49c,0x4a0,0x294,
        0x24c,0x1c8,0x23c,0x240,0x244,0x248,0x1b8,0x1bc,0x1d8,0x1e8};
    for(unsigned i=0;i<sizeof(a);++i) {
        bool permitted=false;
        for(unsigned j=0;j<sizeof(changed)/sizeof(changed[0]);++j)
            if(i>=changed[j] && i<changed[j]+4)permitted=true;
        if(!permitted && b.storage[i]!=before[i])return 4;
    }
    return 0;
}
static int expected(DisplayMode* m,unsigned n,uint32_t w,uint32_t h,unsigned f,uint32_t ew,uint32_t eh) {
    PresentationState s;
    memset(&s,0,sizeof(s));
    s.word(0x27c)=(uint32_t)(uintptr_t)m; s.word(0x280)=s.word(0x27c)+n*24;
    s.word(0x48c)=w; s.word(0x490)=h; s.storage[0x4bf]=(unsigned char)f;
    s.updatePresentationParameters();
    return s.word(0x48c)!=ew || s.word(0x490)!=eh;
}
extern "C" int test_main() {
    DisplayMode m[20];
    const uint32_t pairs[][2]={{1920,1080},{1280,720},{1600,900},{800,1200},{1920,720},{0,0},{0xffffffffu,0xffffffffu},{0x80000000u,1},{1,0x80000000u}};
    for(unsigned i=0;i<20;++i){m[i].width=pairs[i%9][0];m[i].height=pairs[i%9][1];for(unsigned j=0;j<4;++j)m[i].other[j]=next();}
    for(unsigned f=0;f<3;++f)for(unsigned n=0;n<=20;++n)for(unsigned k=0;k<9;++k) {
        if(run(m,n,pairs[k][0],pairs[k][1],f))return 10;
        if(run(m,n,pairs[k][0]+1,pairs[k][1]+1,f,0,23))return 11;
    }
    for(unsigned t=0;t<1500;++t){unsigned n=next()%21;for(unsigned i=0;i<n;++i){m[i].width=next();m[i].height=next();}if(run(m,n,next(),next(),next()%3))return 12;}
    // Aspect-fit flag is safe to exercise only on a branch that skips helper.
    m[0].width=1000;m[0].height=1000;
    if(run(m,1,100,100,0,1))return 13;
    // A later narrower mode cannot raise the windowed height bound.
    m[0].width=1000;m[0].height=500;m[1].width=800;m[1].height=1200;
    if(expected(m,2,900,900,0,1000,500))return 14;
    // Fullscreen upper candidates must improve both dimensions.
    m[0].width=1400;m[0].height=900;m[1].width=1300;m[1].height=1000;
    if(expected(m,2,1200,800,1,1400,900))return 15;
    // UINT_MAX is also the 'no upper candidate' sentinel, even as real width.
    m[0].width=0xffffffffu;m[0].height=900;
    if(expected(m,1,1200,800,1,0,0))return 16;
    if(expected(m,0,100,100,1,0,0))return 17;
    test_write("presentation parameters: passed\n",32);
    return 0;
}
