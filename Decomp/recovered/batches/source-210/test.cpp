#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" int RR_STDCALL original_application_entry(void*,void*,const char*,int);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void* p,int c,unsigned n) { unsigned char* q=(unsigned char*)p; for(unsigned i=0;i<n;++i) q[i]=(unsigned char)c; return p; }
extern "C" void* memcpy(void* p,const void* s,unsigned n) { unsigned char* q=(unsigned char*)p; const unsigned char* r=(const unsigned char*)s; for(unsigned i=0;i<n;++i) q[i]=r[i]; return p; }
// These are writable dependency/data slots, never code. The local evidence link
// maps them to the documented addresses; ordinary links report the absent map.
uintptr_t oracle_iat[0x700/4] __attribute__((section(".oracle_iat"),aligned(4)));
uint32_t oracle_cookie __attribute__((section(".oracle_cookie"),aligned(4)));
int64_t oracle_frequency __attribute__((section(".oracle_frequency"),aligned(8)));
void* oracle_mutex __attribute__((section(".oracle_mutex"),aligned(4)));
static unsigned errors, count, logEvents[100];
static unsigned errorCode, frequencyOK, failure, loopMode, heapMode, once;
static void* newHandle;
static void event(unsigned x) { if(count<100) logEvents[count++]=x; else ++errors; }
static bool eq(const char* a,const char* b) { while(*a && *a==*b) {++a;++b;} return *a==*b; }
static void* RR_STDCALL mutexSpy(void* security,int own,const char* name) {
    event(1); if(security || own!=1 || ((uintptr_t)name!=0xa062fc && !eq(name,"OCTANE"))) ++errors; return newHandle;
}
static uint32_t RR_STDCALL errorSpy() { event(2); return errorCode; }
static int RR_STDCALL closeSpy(void* h) { event(3); if(h!=newHandle) ++errors; return 0; }
static int RR_STDCALL frequencySpy(int64_t* p) { event(4); *p=123456789; return frequencyOK; }
static int RR_STDCALL messageASpy(void* owner,const char* text,const char* title,unsigned type) {
    event(5); if(owner || type!=16) ++errors;
    if((uintptr_t)title!=0xa06304 && !eq(title,"Error")) ++errors;
    if((uintptr_t)text!=0xa06310 && !eq(text,"This game requires that a high-resolution performance counter is available, however none was detected. The game will now exit.")) ++errors;
    return 77;
}
static void* mutexValue; static int64_t frequencyValue; static double scaleValue;
static uint32_t threadValue; static uint8_t initializedValue; static void* serviceValue;
static Stage stageObject; static Stage* stageValue; static void* directoryValue;
static Graphics graphicsObject; static Graphics* graphicsValue;
static Worker workerObject; static Worker* workerValue;
static Services servicesObject; static Services* servicesValue;
static State state;
static Dependencies deps;
static Object messages; static void* messageVT[4]; static void* serviceVT[17]; static void* workerVT[2];
static char commandHeap[64]; static uint16_t wideHeap[32], titleHeap[32];
static uint16_t titleText[]={ 'T',0 };
static double convert(int64_t n) { event(6); if(n!=123456789) ++errors; return (double)n; }
static uint32_t RR_STDCALL threadSpy() {event(7);return 0x1234;}
static int32_t RR_STDCALL comSpy(void* p,unsigned f) {event(8); if(p||f)++errors;return -1;}
static void onceSpy() {event(9); if(initializedValue!=1)++errors;}
static void RR_THISCALL commandSpy(NarrowString* p,const char* c) {
    event(10); if(!eq(c,"AbC"))++errors;
    p->capacity=heapMode?31:15; p->size=heapMode==2?0:3;
    if(heapMode)p->storage.heap=commandHeap;
    char* q=p->data(); q[0]='A';q[1]='b';q[2]='C';q[3]=0;
}
static int lowerSpy(int x) { return x>='A'&&x<='Z'?x+32:x; }
static void transformSpy(char** out,char* b,char* e,char* dest,int (*lower)(int)) {
    event(11); if(e-b!=3 || b!=dest)++errors;
    while(b!=e)*dest++=(char)lower((signed char)*b++);
    *out=dest;
}
static void servicesSpy() {event(12);}
static void* allocateSpy(uint32_t n) {event(13); if(n!=0x148)++errors;return failure==6?0:(void*)0x123000;}
static void* RR_THISCALL constructServiceSpy(void* p) {event(14); if(p!=(void*)0x123000)++errors;return (void*)0x345000;}
static void stageSpy() {event(15);}
static bool RR_THISCALL checkStageSpy(Stage* p) {event(16);if(p!=&stageObject)++errors;return failure!=1;}
static void RR_THISCALL assignSpy(WideString* p,const uint16_t* text,uint32_t n) {event(17);if(p!=&stageObject.error||n!=29||text[0]!='F'||text[28]!='!')++errors;}
static void RR_THISCALL copySpy(WideString* p,WideString* from,uint32_t start,uint32_t n) {event(18);if(from!=&stageObject.error||start||n!=0xffffffffu||p->capacity!=7||p->size||p->storage.small[0])++errors;p->capacity=heapMode?31:7;p->size=1;if(heapMode)p->storage.heap=wideHeap;p->data()[0]='M';p->data()[1]=0;}
static Object* messagesSpy() {event(19);return &messages;}
static const uint16_t* RR_THISCALL titleSpy(Object* p,int index) {event(20);if(p!=&messages||index!=1)++errors;return titleText;}
static void wideSpy(WideString* p,const uint16_t* t) {event(21);if(t!=titleText)++errors;p->capacity=heapMode?31:7;p->size=1;if(heapMode)p->storage.heap=titleHeap;p->data()[0]='T';p->data()[1]=0;}
static int RR_STDCALL messageWSpy(void* p,const uint16_t* m,const uint16_t* t,unsigned f) {event(22);if(p||f!=16||m[0]!='M'||t[0]!='T')++errors;return 1;}
static void freeSpy(void* p) {event(p==commandHeap?25:p==wideHeap?24:p==titleHeap?23:99);}
static int RR_STDCALL dllSpy(const uint16_t* p) {event(26);if(p!=stageObject.directory.data())++errors;return 0;}
static void directorySpy() {event(27);}
static void RR_THISCALL setupSpy(void* p) {event(28);if(p!=(void*)0x456000)++errors;}
static bool startupSpy() {event(29);return failure!=2;}
static void RR_THISCALL messageInitSpy(Object* p) {event(30);if(p!=&messages)++errors;}
static void graphicsSpy() {event(31);}
static bool RR_THISCALL startGraphicsSpy(Graphics* p,void* instance,char* c,int show) {event(32);if(p!=&graphicsObject||instance!=(void*)0x400000||show!=7||!eq(c,heapMode==2?"AbC":"abc"))++errors;return failure!=3;}
static Object* RR_THISCALL getHandlerSpy(Services* p) {event(33);if(p!=&servicesObject)++errors;return &messages;}
static void workerSpy() {event(34);}
static bool RR_THISCALL startWorkerSpy(Worker* p,int x) {event(35);if(p!=&workerObject||x||!eq(p->command,heapMode==2?"AbC":"abc"))++errors;return failure!=4;}
static void pumpSpy() {event(36);if(loopMode==1)servicesObject.stop=1;}
static uint32_t RR_STDCALL waitSpy(void* h,uint32_t ms) {event(ms==0xffffffffu?41:37);if(h!=(void*)0x567000)++errors;return loopMode==2?0:0xffffffffu;}
static void RR_THISCALL frameSpy(Graphics* p) {event(38);if(p!=&graphicsObject)++errors;servicesObject.stop=1;}
static int RR_STDCALL setEventSpy(void* h) {event(h==(void*)0x100?39:40);if(!graphicsObject.stop||(h!=(void*)0x100&&h!=(void*)0x200))++errors;return 0;}
static void RR_THISCALL shutdownSpy(Graphics* p) {event(42);if(p!=&graphicsObject)++errors;}
static void reset() {
    count=errors=0; mutexValue=(void*)0xdead;frequencyValue=-5;scaleValue=9.5;threadValue=0xabcdef;
    initializedValue=(uint8_t)(once&1);serviceValue=(once&2)?(void*)0x987000:0; stageValue=&stageObject;directoryValue=(void*)0x456000;
    graphicsValue=&graphicsObject;workerValue=&workerObject;servicesValue=&servicesObject;
    memset(&graphicsObject,0xa5,sizeof(graphicsObject)); graphicsObject.events[0]=(void*)0x100;graphicsObject.events[1]=(void*)0x200;graphicsObject.stop=0;
    memset(&stageObject,0xa5,sizeof(stageObject));stageObject.directory.capacity=7;stageObject.directory.size=1;stageObject.directory.storage.small[0]='D';stageObject.directory.storage.small[1]=0;
    workerObject.vtable=workerVT;workerObject.handle=(void*)0x567000;workerObject.command=(char*)0x123;workerObject.unknown4=0x11223344;workerObject.unknownC=0x55667788;
    servicesObject.vtable=serviceVT;servicesObject.stop=loopMode==0?1:0;
    state.mutex=&mutexValue;state.frequency=&frequencyValue;state.frequencyPerMicrosecond=&scaleValue;state.threadId=&threadValue;state.initialized=&initializedValue;state.service=&serviceValue;state.stage=&stageValue;state.directoryService=&directoryValue;state.graphics=&graphicsValue;state.worker=&workerValue;state.services=&servicesValue;
}
static bool has(unsigned e) {for(unsigned i=0;i<count;++i)if(logEvents[i]==e)return true;return false;}
static unsigned expected[100], expectedCount;
static void expect(unsigned e) { expected[expectedCount++]=e; }
static bool portable() {
    for(failure=0;failure<7;++failure)for(heapMode=0;heapMode<3;++heapMode)for(loopMode=0;loopMode<4;++loopMode)for(once=0;once<4;++once) {
        reset();errorCode=5;frequencyOK=1;newHandle=0;
        int r=applicationEntry((void*)0x400000,(void*)0xbeef,"AbC",7,state,deps);
        if(errors||r!=((failure>=1&&failure<=4)?-1:0)||mutexValue!=0||frequencyValue!=123456789||scaleValue!=123.456789||threadValue!=0x1234||initializedValue!=1) return false;
        if(has(9)!=((once&1)==0)||has(11)!=(heapMode!=2)||has(14)!=(!(once&2)&&failure!=6)||has(25)!=(heapMode!=0))return false;
        if(serviceValue!=((once&2)?(void*)0x987000:failure==6?0:(void*)0x345000)||workerObject.unknown4!=0x11223344||workerObject.unknownC!=0x55667788)return false;
        bool success=!(failure>=1&&failure<=4);
        if(has(42)!=success||graphicsObject.stop!=(success?1:0)||has(39)!=success||has(40)!=success||has(41)!=success)return false;
        if(has(38)!=(success&&loopMode==3)||has(37)!=(success&&loopMode>=2)||has(36)!=(success&&loopMode!=0))return false;
        if(has(23)!=(failure==1&&heapMode!=0)||has(24)!=(failure==1&&heapMode!=0)||has(33)!=(failure==3))return false;
        // Independently predict complete call ordering, including failure cleanup.
        expectedCount=0;
        expect(1);expect(2);expect(4);expect(6);expect(7);expect(8);
        if(!(once&1))expect(9);
        expect(10);if(heapMode!=2)expect(11);expect(12);
        if(!(once&2)) {expect(13);if(failure!=6)expect(14);}
        expect(15);expect(16);
        if(failure==1) {
            expect(17);expect(18);expect(19);expect(20);expect(21);expect(22);
            if(heapMode) {expect(23);expect(24);}
        } else {
            expect(26);expect(27);expect(28);expect(29);
            if(failure!=2) {
                expect(19);expect(30);expect(31);expect(32);
                if(failure==3) {expect(33);expect(30);}
                else {
                    expect(34);expect(35);
                    if(failure!=4) {
                        if(loopMode)expect(36);
                        if(loopMode>=2)expect(37);
                        if(loopMode==3)expect(38);
                        expect(39);expect(40);expect(41);expect(42);
                    }
                }
            }
        }
        if(heapMode)expect(25);
        if(count!=expectedCount)return false;
        for(unsigned i=0;i<count;++i)if(logEvents[i]!=expected[i])return false;
        const unsigned char* g=(const unsigned char*)&graphicsObject;
        for(unsigned i=0;i<sizeof(Graphics);++i)if((i<0x460||i>=0x468)&&i!=0xba0&&g[i]!=0xa5)return false;
    }
    return true;
}
static bool early(bool mapped) {
    const unsigned codes[]={183,0,5,0xffffffffu};
    for(unsigned c=0;c<4;++c)for(unsigned h=0;h<2;++h) {
        reset();errorCode=codes[c];frequencyOK=0;newHandle=h?(void*)0x87654321:0;
        int a=applicationEntry((void*)0x400000,0,"AbC",7,state,deps);
        if(errors||a!=(c==0?-2:-1)||mutexValue!=newHandle||frequencyValue!=(c==0?-5:123456789)||scaleValue!=9.5||threadValue!=0xabcdef||initializedValue!=(once&1)||serviceValue!=0||graphicsObject.stop)return false;
        unsigned n=count, saved[8];for(unsigned i=0;i<n;++i)saved[i]=logEvents[i];
        if(n!=(c==0?3u:4u))return false;
        if(mapped) {
            oracle_frequency=-5;oracle_mutex=(void*)0xdead;count=errors=0;
            int b=original_application_entry((void*)0x400000,0,"AbC",7);
            if(errors||b!=a||count!=n||oracle_mutex!=newHandle||oracle_frequency!=frequencyValue)return false;
            for(unsigned i=0;i<n;++i)if(saved[i]!=logEvents[i])return false;
        }
    }
    return true;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"x86 narrow string");static_assert(sizeof(WideString)==24,"x86 wide string");
    static_assert(offsetof(Stage,error)==0x30,"stage");static_assert(offsetof(Graphics,stop)==0xba0,"graphics stop");static_assert(offsetof(Services,stop)==0x2d,"services stop");
    deps.createMutex=mutexSpy;deps.lastError=errorSpy;deps.closeHandle=closeSpy;deps.queryFrequency=frequencySpy;deps.messageA=messageASpy;
    deps.convertFrequency=convert;deps.currentThread=threadSpy;deps.coInitialize=comSpy;deps.initializeOnce=onceSpy;
    deps.constructCommand=commandSpy;deps.transform=transformSpy;deps.lowercase=lowerSpy;deps.initializeServices=servicesSpy;deps.allocate=allocateSpy;deps.constructService=constructServiceSpy;
    deps.ensureStage=stageSpy;deps.checkStage=checkStageSpy;deps.assignError=assignSpy;deps.copyError=copySpy;deps.getMessages=messagesSpy;deps.constructWide=wideSpy;deps.messageW=messageWSpy;deps.deallocate=freeSpy;
    deps.setDllDirectory=dllSpy;deps.ensureDirectoryService=directorySpy;deps.setupDirectoryService=setupSpy;deps.checkStartup=startupSpy;deps.ensureGraphics=graphicsSpy;deps.startGraphics=startGraphicsSpy;deps.ensureWorker=workerSpy;deps.pumpMessages=pumpSpy;deps.wait=waitSpy;deps.frame=frameSpy;deps.setEvent=setEventSpy;deps.shutdownGraphics=shutdownSpy;
    messages.vtable=messageVT;messageVT[0]=(void*)messageInitSpy;messageVT[3]=(void*)titleSpy;serviceVT[16]=(void*)getHandlerSpy;workerVT[1]=(void*)startWorkerSpy;
    oracle_iat[0x34/4]=(uintptr_t)mutexSpy;oracle_iat[0x108/4]=(uintptr_t)errorSpy;oracle_iat[0xd4/4]=(uintptr_t)closeSpy;oracle_iat[0xf0/4]=(uintptr_t)frequencySpy;oracle_iat[0x598/4]=(uintptr_t)messageASpy;oracle_cookie=0x12345678;
    bool mapped=(uintptr_t)oracle_iat==0x92d000&&(uintptr_t)&oracle_cookie==0xbaabc0&&(uintptr_t)&oracle_frequency==0xc00b48&&(uintptr_t)&oracle_mutex==0xc0d610;
    if(!portable())return 1;
    once=0;if(!early(mapped))return 2;
    if(mapped) {const char s[]="PASS: 8 original differential early exits; 336 portable startup/loop cases\n";test_write(s,sizeof(s)-1);}
    else {const char s[]="LIMIT: fixed oracle slots unmapped; portable assertions only, no original calls\n";test_write(s,sizeof(s)-1);}
    return 0;
}
