#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((regparm(3))) original_worker_view_heap_sift(unsigned, int32_t, WorkerViewHeapItem**, int32_t, WorkerViewHeapItem* const*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d,const void* s,size_t n) { for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=((const unsigned char*)s)[i]; return d; }
extern "C" void* memset(void* d,int c,size_t n) { for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=(unsigned char)c; return d; }
static WorkerViewHeapItem objects[20];
static unsigned char snapshot[sizeof(objects)];
static WorkerViewHeapItem* a[20];
static WorkerViewHeapItem* b[20];
static unsigned fs_storage[16];
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0 || test_get_fs_head()!=0xffffffffu) return 1;
    static const int32_t scores[8]={-2147483647-1,-10,-1,0,1,7,7,2147483647};
    for(int mode=0;mode<8;++mode) {
        for(int i=0;i<20;++i) {
            for(int j=0;j<0x188;++j) objects[i].opaque[j]=(unsigned char)(i*19+j);
            objects[i].priority=mode==7 ? 7 : scores[(i*3+mode)%8];
        }
        memcpy(snapshot,objects,sizeof(objects));
        for(int len=0;len<=16;++len) for(int hole=0;hole<(len ? len : 1);++hole)
          for(int alias=-1;alias<16;++alias) for(int val=0;val<8;++val) {
            for(int i=0;i<20;++i) a[i]=b[i]=&objects[(i*7+val+mode)%20];
            WorkerViewHeapItem* va=&objects[val];
            WorkerViewHeapItem* vb=va;
            WorkerViewHeapItem* const* pa=alias<0 ? &va : &a[alias+1];
            WorkerViewHeapItem* const* pb=alias<0 ? &vb : &b[alias+1];
            worker_view_heap_sift(a+1,hole,len,pa);
            original_worker_view_heap_sift(0,hole,b+1,len,pb,0xa5a50000u+(unsigned)val);
            if(test_get_fs_head()!=0xffffffffu) return 2;
            for(int i=0;i<20;++i) if(a[i]!=b[i]) return 3;
            if(va!=vb) return 4;
            for(size_t i=0;i<sizeof(objects);++i) if(((unsigned char*)objects)[i]!=snapshot[i]) return 5;
          }
    }
    return 0;
}
