#include "impl.hpp"
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// GCC fastcall places the first two arguments in ECX/EDX. The original
// uses caller cleanup for the third argument, unlike GCC fastcall. Isolate the
// call in an O0 frame whose epilogue restores ESP from EBP.
extern "C" WorkerRecord84* __attribute__((fastcall)) original_worker_record84_move_range(const WorkerRecord84*, const WorkerRecord84*, WorkerRecord84*);
static unsigned fs_storage[8];
static unsigned char a[600], b[600];
static __attribute__((noinline)) WorkerRecord84* oracle(const WorkerRecord84* p, const WorkerRecord84* e, WorkerRecord84* d) {
    return original_worker_record84_move_range(p,e,d);
}
static bool equal() { for (unsigned i=0;i<sizeof(a);++i) if(a[i]!=b[i]) return false; return true; }
static int scenario(unsigned src, unsigned dst, unsigned count) {
    for(unsigned i=0;i<sizeof(a);++i) a[i]=b[i]=(unsigned char)(i*73u+(i>>2)+19u);
    WorkerRecord84* ar=oracle((WorkerRecord84*)(a+src),(WorkerRecord84*)(a+src+84*count),(WorkerRecord84*)(a+dst));
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    WorkerRecord84* br=worker_record84_move_range((WorkerRecord84*)(b+src),(WorkerRecord84*)(b+src+84*count),(WorkerRecord84*)(b+dst));
    if ((uintptr_t)ar-(uintptr_t)a != (uintptr_t)br-(uintptr_t)b || !equal()) return 2;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678;
    if(test_install_fs(fs_storage)!=0) return 1;
    if(test_get_fs_head()!=fs_storage[0]) return 2;
    if(scenario(20,300,0) || scenario(20,300,1) || scenario(7,300,3) ||
       scenario(20,20,3) || scenario(20,21,2) || scenario(21,20,2) ||
       scenario(20,36,2) || scenario(20,24,2) || scenario(120,36,3) ||
       scenario(36,120,3)) return 3;
    WorkerRecord84* r=oracle((WorkerRecord84*)a,(WorkerRecord84*)(a+84),0);
    if(test_get_fs_head()!=fs_storage[0] || (uintptr_t)r!=84) return 4;
    if((uintptr_t)worker_record84_move_range((WorkerRecord84*)a,(WorkerRecord84*)(a+84),0)!=84) return 5;
    r=oracle((WorkerRecord84*)a,(WorkerRecord84*)a,0);
    if(test_get_fs_head()!=fs_storage[0] || r!=0) return 6;
    if(worker_record84_move_range((WorkerRecord84*)a,(WorkerRecord84*)a,0)!=0) return 7;
    return 0;
}
