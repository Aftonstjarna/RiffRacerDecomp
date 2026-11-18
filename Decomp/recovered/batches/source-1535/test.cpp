#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((fastcall)) original_worker_view_pointer_small_sort(WorkerViewSortItem**, WorkerViewSortItem**);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage = 0x13579bdfu;
extern "C" void* memset(void* p, int v, size_t n) { unsigned char* d=(unsigned char*)p; while(n--) *d++=(unsigned char)v; return p; }
extern "C" void* memcpy(void* p, const void* q, size_t n) { unsigned char* d=(unsigned char*)p; const unsigned char* s=(const unsigned char*)q; while(n--) *d++=*s++; return p; }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; while(n--) if(*x++!=*y++) return false; return true; }
static int run(const int32_t* keys, unsigned n, bool oracle) {
    WorkerViewSortItem items[8], saved[8];
    WorkerViewSortItem* a[10]; WorkerViewSortItem* b[10]; WorkerViewSortItem* expected[10];
    memset(items,0xa5,sizeof items);
    for(unsigned i=0;i<8;++i) items[i].sort_key=keys[i];
    memcpy(saved,items,sizeof items);
    for(unsigned i=0;i<10;++i) a[i]=b[i]=expected[i]=&items[(i+7)%8];
    for(unsigned i=0;i<n;++i) a[i+1]=b[i+1]=expected[i+1]=&items[i];
    // Independent stable selection by rank, retaining original order on ties.
    for(unsigned i=0;i<n;++i) {
        unsigned rank=0;
        for(unsigned j=0;j<n;++j) if(keys[j]<keys[i] || (keys[j]==keys[i] && j<i)) ++rank;
        expected[rank+1]=&items[i];
    }
    worker_view_pointer_small_sort(a+1,a+1+n);
    if(!equal(a,expected,sizeof a) || !equal(items,saved,sizeof items)) return 1;
    if(oracle) {
        original_worker_view_pointer_small_sort(b+1,b+1+n);
        if(test_get_fs_head()!=fs_storage) return 2;
        if(!equal(b,expected,sizeof b) || !equal(items,saved,sizeof items)) return 3;
    }
    return 0;
}
extern "C" int test_main() {
    if(test_install_fs(&fs_storage)!=0) return 1;
    original_worker_view_pointer_small_sort(0,0);
    if(test_get_fs_head()!=fs_storage) return 2;
    worker_view_pointer_small_sort(0,0);
    // Exhaust all 4-key combinations, including duplicates and negative keys.
    for(unsigned n=0;n<=7;++n) {
        unsigned count=1; for(unsigned i=0;i<n;++i) count*=4;
        for(unsigned code=0;code<count;++code) {
            int32_t keys[8]; unsigned x=code;
            for(unsigned i=0;i<8;++i) { keys[i]=(int32_t)(x%4)-2; x/=4; }
            bool safe=true; for(unsigned i=1;i<n;++i) if(keys[i]<keys[0]) safe=false;
            int r=run(keys,n,safe); if(r) return 10+r;
        }
    }
    const int32_t extremes[8]={0x7fffffff,(-2147483647-1),0,0x7fffffff,-1,(-2147483647-1),1,0};
    if(run(extremes,8,false)) return 20;
    const int32_t oracle_extremes[8]={(-2147483647-1),0x7fffffff,-1,0,(-2147483647-1),0x7fffffff,1,-1};
    if(run(oracle_extremes,8,true)) return 21;
    return 0;
}
