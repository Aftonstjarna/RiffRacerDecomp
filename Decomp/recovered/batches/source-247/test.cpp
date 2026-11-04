#include "impl.hpp"
extern "C" uint8_t RR_THISCALL original_worker_request(Worker*, void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" { unsigned char oracle_iat[4096] __attribute__((section(".oracle_iat"),used,aligned(4))); }
static Worker a,b;
static Worker* current;
static unsigned step, errors, mode, initialIndex;
static uint8_t resultByte;
static uint32_t apiReturn;
static uint32_t payload[4];
static uint32_t fsStorage[8];
static void check(bool ok) { if(!ok) ++errors; }
static uint32_t nextIndex(unsigned stage) { return (mode & (1u<<stage)) ? (initialIndex ^ 1u) : initialIndex; }
extern "C" uint32_t RR_STDCALL WaitForMultipleObjects(uint32_t count,const uint32_t* handles,int32_t all,uint32_t timeout) {
    check(step++==0); check(count==2 && all==1 && timeout==UINT32_MAX);
    check(handles==current->completionEvents);
    check(handles[0]==0x12345678 && handles[1]==0x87654321);
    check(current->requestActive==0x95 && current->requestResult==0xa3);
    check(current->pendingRequest==0x24681357);
    current->selected=nextIndex(0);
    return apiReturn;
}
extern "C" int32_t RR_STDCALL ResetEvent(uint32_t h) {
    check(step++==1); check(h==current->completionEvents[nextIndex(0)]);
    check(current->requestActive==1 && current->requestResult==0);
    check(current->pendingRequest==static_cast<uint32_t>(reinterpret_cast<uintptr_t>((mode&8)?payload:0)));
    current->selected=nextIndex(1);
    return static_cast<int32_t>(apiReturn);
}
extern "C" int32_t RR_STDCALL SetEvent(uint32_t h) {
    check(step++==2); check(h==current->workEvents[nextIndex(1)]);
    check(current->requestActive==1 && current->requestResult==0);
    current->selected=nextIndex(2);
    return static_cast<int32_t>(apiReturn);
}
extern "C" uint32_t RR_STDCALL WaitForSingleObject(uint32_t h,uint32_t timeout) {
    check(step++==3); check(h==current->completionEvents[nextIndex(2)] && timeout==UINT32_MAX);
    check(current->requestActive==1 && current->requestResult==0);
    current->requestResult=resultByte;
    // Simulate counterpart consuming the pointer, as documented by frame body.
    if(mode&16) current->pendingRequest=0;
    return apiReturn;
}
static void initialize(Worker& w,uint8_t shutdown) {
    unsigned char* p=reinterpret_cast<unsigned char*>(&w);
    for(unsigned i=0;i<sizeof(w);++i) p[i]=static_cast<unsigned char>(i*37+19);
    w.workEvents[0]=0x11223344; w.workEvents[1]=0x55667788;
    w.completionEvents[0]=0x12345678; w.completionEvents[1]=0x87654321;
    w.selected=initialIndex; w.shuttingDown=shutdown;
    w.pendingRequest=0x24681357; w.requestActive=0x95; w.requestResult=0xa3;
}
extern "C" int test_main() {
    fsStorage[0]=0x13572468;
    if(test_install_fs(fsStorage)!=0) return 90;
    *reinterpret_cast<decltype(&WaitForMultipleObjects)*>(oracle_iat+0xc8)=WaitForMultipleObjects;
    *reinterpret_cast<decltype(&ResetEvent)*>(oracle_iat+0x104)=ResetEvent;
    *reinterpret_cast<decltype(&SetEvent)*>(oracle_iat+0x120)=SetEvent;
    *reinterpret_cast<decltype(&WaitForSingleObject)*>(oracle_iat+0x124)=WaitForSingleObject;
    const uint8_t shutdowns[]={0,1,0x80,0xff};
    const uint8_t results[]={0,1,2,0x80,0xff};
    const uint32_t returns[]={0,1,0x80,0x102,UINT32_MAX};
    for(unsigned s=0;s<4;++s) for(initialIndex=0;initialIndex<2;++initialIndex)
    for(mode=0;mode<32;++mode) for(unsigned r=0;r<5;++r) for(unsigned v=0;v<5;++v) {
        resultByte=results[r]; apiReturn=returns[v];
        initialize(a,shutdowns[s]); initialize(b,shutdowns[s]);
        void* argument=(mode&8)?payload:0;
        current=&a; step=0;
        uint8_t original=original_worker_request(&a,argument);
        check(test_get_fs_head()==fsStorage[0]);
        check(step==(s?0u:4u));
        current=&b; step=0;
        uint8_t recovered=b.request(argument);
        check(test_get_fs_head()==fsStorage[0]);
        check(step==(s?0u:4u)); check(original==recovered);
        check(original==(s?0:resultByte));
        const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
        const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
        for(unsigned i=0;i<sizeof(a);++i) check(x[i]==y[i]);
        // Independently check the complete final object, including untouched padding.
        Worker expected; initialize(expected,shutdowns[s]);
        if(!s) { expected.selected=nextIndex(2); expected.requestActive=0;
          expected.requestResult=resultByte;
          expected.pendingRequest=(mode&16)?0:static_cast<uint32_t>(reinterpret_cast<uintptr_t>(argument)); }
        const unsigned char* z=reinterpret_cast<const unsigned char*>(&expected);
        for(unsigned i=0;i<sizeof(a);++i) check(x[i]==z[i]);
        if(errors) return 1;
    }
    static const char message[]="worker-request: 6400 differential cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
