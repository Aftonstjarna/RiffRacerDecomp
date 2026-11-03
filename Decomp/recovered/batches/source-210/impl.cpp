#include "impl.hpp"
namespace riff {
static const uint16_t missingData[] = {
 'F','a','i','l','e','d',' ','t','o',' ','f','i','n','d',' ','d','a','t','a',' ','p','a','c','k','f','i','l','e','!',0
};
static const char timerError[] =
 "This game requires that a high-resolution performance counter is available, however none was detected. The game will now exit.";
// Descriptive names only: actual class identities have not been established.
typedef void (RR_THISCALL *VirtualVoid)(Object*);
typedef const uint16_t* (RR_THISCALL *VirtualText)(Object*,int);
typedef Object* (RR_THISCALL *VirtualObject)(Services*);
typedef bool (RR_THISCALL *VirtualStart)(Worker*,int);
int applicationEntry(void* instance, void* previous, const char* command, int show,
                     State& s, const Dependencies& d) {
    (void)previous;
    *s.mutex = d.createMutex(0,1,"OCTANE");
    if (d.lastError() == 183) {
        d.closeHandle(*s.mutex);
        return -2; // Global intentionally still contains the closed handle.
    }
    if (!d.queryFrequency(s.frequency)) {
        d.messageA(0,timerError,"Error",0x10);
        return -1; // Does not close the newly created mutex.
    }
    *s.frequencyPerMicrosecond = d.convertFrequency(*s.frequency) / 1000000.0;
    *s.threadId = d.currentThread();
    d.coInitialize(0,0); // HRESULT ignored; no CoUninitialize in this routine.
    if (!*s.initialized) {
        *s.initialized=1; // Set before calling initialization.
        d.initializeOnce();
    }
    NarrowString text;
    d.constructCommand(&text,command);
    char* begin=text.data();
    char* transformedEnd;
    if (text.size) d.transform(&transformedEnd,begin,begin+text.size,begin,d.lowercase);
    else transformedEnd=begin;
    (void)transformedEnd;
    d.initializeServices();
    if (!*s.service) {
        void* allocation=d.allocate(0x148);
        *s.service=allocation ? d.constructService(allocation) : 0;
    }
    d.ensureStage();
    Stage* stage=*s.stage;
    bool stageReady=d.checkStage(stage);
    // Original caches deallocator even on paths where no string needs freeing.
    void (*freeString)(void*)=d.deallocate;
    if (!stageReady) {
        d.assignError(&stage->error,missingData,29);
        WideString message;
        message.capacity=7; message.size=0; message.storage.small[0]=0;
        d.copyError(&message,&(*s.stage)->error,0,0xffffffffu);
        Object* messages=d.getMessages();
        const uint16_t* title=reinterpret_cast<VirtualText>(messages->vtable[3])(messages,1);
        WideString caption;
        d.constructWide(&caption,title);
        d.messageW(0,message.data(),caption.data(),0x10);
        if (caption.capacity>=8) freeString(caption.storage.heap);
        caption.capacity=7; caption.size=0; caption.storage.small[0]=0;
        if (message.capacity>=8) freeString(message.storage.heap);
        if (text.capacity>=16) freeString(text.storage.heap);
        return -1;
    }
    d.setDllDirectory(stage->directory.data()); // Return value ignored.
    d.ensureDirectoryService();
    d.setupDirectoryService(*s.directoryService);
    int result=-1;
    if (d.checkStartup()) {
        Object* messages=d.getMessages();
        reinterpret_cast<VirtualVoid>(messages->vtable[0])(messages);
        d.ensureGraphics();
        Graphics* graphics=*s.graphics;
        if (!d.startGraphics(graphics,instance,text.data(),show)) {
            Services* services=*s.services;
            Object* handler=reinterpret_cast<VirtualObject>(services->vtable[16])(services);
            reinterpret_cast<VirtualVoid>(handler->vtable[0])(handler);
        } else {
            d.ensureWorker();
            Worker* worker=*s.worker;
            worker->command=text.data(); // Borrowed pointer; not cleared on cleanup.
            if (reinterpret_cast<VirtualStart>(worker->vtable[1])(worker,0)) {
                uint32_t (RR_STDCALL *poll)(void*,uint32_t)=d.wait;
                while (!(*s.services)->stop) {
                    d.pumpMessages();
                    if ((*s.services)->stop) break;
                    // Every nonzero status (including WAIT_FAILED) runs a frame.
                    if (poll(worker->handle,0)==0) break;
                    d.frame(graphics);
                }
                graphics->stop=1;
                d.setEvent(graphics->events[0]);
                d.setEvent(graphics->events[1]);
                d.wait(worker->handle,0xffffffffu);
                d.shutdownGraphics(graphics);
                result=0;
                // Original reloads IAT deallocator after shutdown.
                freeString=d.deallocate;
            }
        }
    }
    if (text.capacity>=16) freeString(text.storage.heap);
    return result;
}
}
