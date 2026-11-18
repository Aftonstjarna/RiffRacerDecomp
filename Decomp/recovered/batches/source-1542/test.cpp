#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((regparm(3))) original_worker_view_heap_push(unsigned, int32_t, WorkerViewHeapItem**, int32_t, WorkerViewHeapItem* const*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d,const void* s,size_t n) { for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=((const unsigned char*)s)[i]; return d; }
extern "C" void* memset(void* d,int c,size_t n) { for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=(unsigned char)c; return d; }
static WorkerViewHeapItem objects[16];
static unsigned char snapshot[sizeof(objects)];
static WorkerViewHeapItem* a[18];
static WorkerViewHeapItem* b[18];
static unsigned fs_storage[16];
static int run(int hole,int top,int value_index,int alias,unsigned extra) {
    WorkerViewHeapItem* va=&objects[value_index];
    WorkerViewHeapItem* vb=va;
    WorkerViewHeapItem* const* pa=alias<0 ? &va : &a[alias+1];
    WorkerViewHeapItem* const* pb=alias<0 ? &vb : &b[alias+1];
    worker_view_heap_push(a+1,hole,top,pa);
    original_worker_view_heap_push(0,hole,b+1,top,pb,extra);
    if(test_get_fs_head()!=0xffffffffu) return 1;
    for(int i=0;i<18;++i) if(a[i]!=b[i]) return 2;
    if(va!=vb) return 3;
    for(size_t i=0;i<sizeof(objects);++i) if(((unsigned char*)objects)[i]!=snapshot[i]) return 4;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0 || test_get_fs_head()!=0xffffffffu) return 10;
    for(int mode=0;mode<7;++mode) {
        for(int i=0;i<16;++i) {
            for(int j=0;j<0x188;++j) objects[i].opaque[j]=(unsigned char)(i*17+j);
            static const int32_t extremes[7]={-2147483647-1,-1,0,1,2147483647,7,7};
            objects[i].priority=mode<5 ? extremes[(i+mode)%7] : (mode==5 ? 7 : 15-i);
        }
        memcpy(snapshot,objects,sizeof(objects));
        for(int hole=0;hole<15;++hole) for(int top=0;top<=hole+1;++top)
          for(int val=0;val<16;++val) for(int alias=-1;alias<15;++alias) {
            for(int i=0;i<18;++i) a[i]=b[i]=&objects[(i*5+mode)%16];
            int result=run(hole,top,val,alias,0xa5a50000u+(unsigned)val);
            if(result) return 20+result;
          }
    }
    return 0;
}
