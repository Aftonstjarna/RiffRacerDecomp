#include "impl.hpp"
extern "C" int32_t __attribute__((fastcall)) original_script_table_choose_array_capacity(const int32_t*, int32_t*);
extern "C" void test_write(const char*, unsigned);
static unsigned rng = 0x72ab1349u;
static unsigned next() { rng = rng * 1664525u + 1013904223u; return rng; }
static int compare(const int32_t* input, int32_t total, int alias)
{
    int32_t a[36], b[36], before[36];
    for (int i=0;i<36;++i) a[i]=b[i]=before[i]=input[i];
    int32_t x[3]={0x13579,total,0x24680};
    int32_t y[3]={0x13579,total,0x24680};
    int32_t* ap=alias>=0 ? a+alias : x+1;
    int32_t* bp=alias>=0 ? b+alias : y+1;
    int32_t ar=choose_array_capacity(a,ap);
    int32_t br=original_script_table_choose_array_capacity(b,bp);
    if(ar!=br || *ap!=*bp) return 1;
    for(int i=0;i<36;++i) {
        if(a[i]!=b[i]) return 2;
        if(i!=alias && (a[i]!=before[i] || b[i]!=before[i])) return 3;
    }
    if(x[0]!=0x13579 || y[0]!=0x13579 || x[2]!=0x24680 || y[2]!=0x24680) return 4;
    return 0;
}
extern "C" int test_main()
{
    int32_t h[36]={0};
    if(compare(h,0,-1) || compare(h,-1,-1) || compare(h,(-2147483647-1),-1)) return 10;
    for(int total=1;total<=128;++total) {
        for(int slot=0;slot<10;++slot) {
            for(int i=0;i<36;++i) h[i]=0;
            h[slot]=total;
            if(compare(h,total,-1)) return 11;
        }
    }
    for(int n=0;n<2000;++n) {
        int32_t total=0;
        for(int i=0;i<36;++i) {
            h[i]=i<16 ? static_cast<int32_t>(next()%9) : 0;
            total+=h[i];
        }
        if(compare(h,total,-1)) return 12;
        // Also exercise totals inconsistent with histogram, stopping by capacity.
        if(compare(h,1+static_cast<int32_t>(next()%512),-1)) return 13;
    }
    for(int i=0;i<36;++i) h[i]=(i&1)?-2147483647:-1;
    if(compare(h,256,-1)) return 14;
    for(int i=0;i<36;++i) h[i]=0;
    h[0]=2147483647; h[1]=1; // occupied wraps to INT_MIN, total never reached.
    if(compare(h,2,-1)) return 15;
    h[0]=0; h[1]=0; h[31]=2147483647; // capacity wraps to INT_MIN.
    if(compare(h,2147483647,-1)) return 16;
    for(int i=0;i<36;++i) h[i]=0;
    h[0]=0; h[1]=1; h[2]=1; h[3]=2; // exactly half full at each positive bucket
    if(compare(h,4,-1)) return 17;
    h[0]=7;
    if(compare(h,7,0)) return 18;
    h[35]=12;
    if(compare(h,12,35)) return 19;
    // Known simple result independently anchors the interpretation.
    h[0]=1; h[1]=1; h[2]=1;
    int32_t total=3;
    if(choose_array_capacity(h,&total)!=3 || total!=4) return 20;
    test_write("capacity oracle tests passed\n",29);
    return 0;
}
