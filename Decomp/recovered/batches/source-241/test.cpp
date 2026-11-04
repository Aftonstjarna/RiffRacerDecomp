#include "impl.hpp"
extern "C" int32_t __attribute__((thiscall)) original_save_device_size(SaveDevice*);
extern "C" void test_write(const char*, unsigned);
struct TestImports { SaveSeek seek; SaveTell tell; };
TestImports original_imports __attribute__((section(".test_imports"),used,aligned(4)));

struct Event { int32_t kind, handle, offset, origin, result; };
struct State {
    Event events[4];
    int count, bad, tells, seeks;
    int32_t initial, end, seek_end_result, seek_restore_result, cursor;
    bool mutate;
    SaveDevice* device;
};
static State s;
static int handles[5];
static int32_t handle_id(void* h) {
    for(int i=0;i<4;++i) if(h==&handles[i]) return i;
    return -1;
}
static void record(int k,void* h,int32_t off,int32_t origin,int32_t result) {
    if(s.count>=4) { s.bad=1; return; }
    Event& e=s.events[s.count++];
    e.kind=k; e.handle=handle_id(h); e.offset=off; e.origin=origin; e.result=result;
    if(e.handle<0) s.bad=1;
    if(s.mutate) s.device->file=&handles[s.count];
}
static int32_t RIFF_CDECL tell_cb(void* h) {
    int32_t r=s.tells++ ? s.end : s.initial;
    record(1,h,0,0,r); return r;
}
static int32_t RIFF_CDECL seek_cb(void* h,int32_t off,int32_t origin) {
    int32_t r=s.seeks++ ? s.seek_restore_result : s.seek_end_result;
    if(r==0) s.cursor=origin==2 ? s.end : off;
    record(2,h,off,origin,r); return r;
}
static bool equal_bytes(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a;
    const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void initialize(SaveDevice& d,int null_handle,int32_t pos,int32_t end,
                       int32_t se,int32_t sr,bool mutate) {
    unsigned char* p=(unsigned char*)&d;
    for(unsigned i=0;i<sizeof(d);++i) p[i]=(unsigned char)(i*37+19);
    d.file=null_handle ? 0 : &handles[0];
    State empty={}; s=empty;
    s.initial=pos; s.end=end; s.seek_end_result=se; s.seek_restore_result=sr;
    s.cursor=pos; s.device=&d; s.mutate=mutate;
}
extern "C" int test_main() {
    original_imports.seek=seek_cb; original_imports.tell=tell_cb;
    save_device_imports.seek=seek_cb; save_device_imports.tell=tell_cb;
    if((uintptr_t)&original_imports!=0x92d3c0u) return 90;
    const int32_t values[]={0,1,-1,4096,0x7fffffff,(-2147483647-1)};
    const int32_t results[]={0,1,-1,(-2147483647-1)};
    unsigned cases=0;
    for(int nul=0;nul<2;++nul)
    for(unsigned p=0;p<6;++p) for(unsigned e=0;e<6;++e)
    for(unsigned a=0;a<4;++a) for(unsigned b=0;b<4;++b)
    for(int mutate=0;mutate<2;++mutate) {
        SaveDevice reference, recovered, before;
        initialize(reference,nul,values[p],values[e],results[a],results[b],mutate!=0);
        before=reference;
        int32_t expected=original_save_device_size(&reference);
        State observed=s;
        initialize(recovered,nul,values[p],values[e],results[a],results[b],mutate!=0);
        int32_t actual=recovered.size();
        if(expected!=actual || s.bad || observed.bad) return 1;
        if(s.count!=observed.count || s.cursor!=observed.cursor ||
           s.tells!=observed.tells || s.seeks!=observed.seeks) return 2;
        if(!equal_bytes(s.events,observed.events,sizeof(s.events))) return 3;
        if(!equal_bytes(&reference,&recovered,sizeof(reference))) return 4;
        // Independently assert call ordering, short circuit, error semantics,
        // restore arguments, and untouched bytes, beyond differential parity.
        const int calls=nul?0:(results[a]!=0?2:4);
        if(s.count!=calls) return 5;
        const int32_t answer=(nul||results[a]!=0||results[b]!=0)?0:values[e];
        if(actual!=answer) return 6;
        if(calls) {
            if(s.events[0].kind!=1 || s.events[1].kind!=2 ||
               s.events[1].offset!=0 || s.events[1].origin!=2) return 7;
            if(calls==4 && (s.events[2].kind!=1 || s.events[3].kind!=2 ||
               s.events[3].offset!=values[p] || s.events[3].origin!=0)) return 8;
            for(int i=0;i<calls;++i)
                if(s.events[i].handle!=(mutate?i:0)) return 9;
        }
        // Only the controlled callback may change file. Undo its mutation
        // before checking every byte against the initial sentinel object.
        recovered.file=before.file;
        if(!equal_bytes(&before,&recovered,sizeof(before))) return 10;
        ++cases;
    }
    if(cases!=2304) return 11;
    test_write("save-device-size: 2304 oracle cases passed\n",43);
    return 0;
}
