#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((regparm(3))) original_worker_view_heap_finish(unsigned, WorkerViewHeapItem**, WorkerViewHeapItem**, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d, const void* s, size_t n) { for (size_t i=0;i<n;++i) static_cast<unsigned char*>(d)[i]=static_cast<const unsigned char*>(s)[i]; return d; }
extern "C" void* memset(void* d, int c, size_t n) { for (size_t i=0;i<n;++i) static_cast<unsigned char*>(d)[i]=static_cast<unsigned char>(c); return d; }
static WorkerViewHeapItem items[66], snapshot[66];
static WorkerViewHeapItem* a[68];
static WorkerViewHeapItem* b[68];
static unsigned fs_data[16];
static unsigned seed=0x13579bdfu;
static unsigned next_random() { seed=seed*1664525u+1013904223u; return seed; }
static int run(int n, int mode, unsigned context) {
    for (int i=0;i<66;++i) {
        for (int j=0;j<0x188;++j) items[i].unknown[j]=(unsigned char)(i*11+j*3);
        unsigned r=next_random();
        if (mode==0) items[i].priority=(int32_t)r;
        else if (mode==1) items[i].priority=(int32_t)(r%5)-2;
        else if (mode==2) items[i].priority=7;
        else if (mode==3) items[i].priority=(i&1) ? (-2147483647-1) : 2147483647;
        else items[i].priority=i-33;
    }
    memcpy(snapshot,items,sizeof(items));
    for (int i=0;i<68;++i) a[i]=b[i]=&items[(i+31)%66];
    for (int i=0;i<n;++i) a[i+1]=b[i+1]=&items[i];
    // Alternate actual heaps and arbitrary ranges: both are defined by the code.
    if (mode != 4) for (int i=1;i<n;++i) {
        int h=i;
        while (h>0 && a[1+(h-1)/2]->priority<a[1+h]->priority) {
            WorkerViewHeapItem* t=a[1+h]; a[1+h]=a[1+(h-1)/2]; a[1+(h-1)/2]=t; h=(h-1)/2;
        }
    }
    for (int i=0;i<n;++i) b[i+1]=a[i+1];
    worker_view_heap_finish(a+1,a+1+n,context);
    original_worker_view_heap_finish(0,b+1+n,b+1,context);
    if (test_get_fs_head()!=0xffffffffu) return 1;
    for (int i=0;i<68;++i) if (a[i]!=b[i]) return 2;
    for (size_t i=0;i<sizeof(items);++i) if (reinterpret_cast<unsigned char*>(items)[i]!=reinterpret_cast<unsigned char*>(snapshot)[i]) return 3;
    if (mode!=4) for (int i=1;i<n;++i) if (a[i]->priority>a[i+1]->priority) return 4;
    return 0;
}
extern "C" int test_main() {
    fs_data[0]=0xffffffffu;
    if (test_install_fs(fs_data)!=0 || test_get_fs_head()!=0xffffffffu) return 10;
    for (int n=0;n<=64;++n) for (int mode=0;mode<5;++mode) for (int rep=0;rep<8;++rep) {
        int result=run(n,mode,next_random());
        if (result) return 20+result;
    }
    return 0;
}
