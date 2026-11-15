#include "impl.hpp"
#include <stddef.h>
extern "C" int __attribute__((thiscall)) original_script_stream_peek(ScriptStream*);
static_assert(sizeof(ScriptStream)==20, "i386 layout");
static_assert(offsetof(ScriptStream,readerContext)==16, "layout");
struct Fixture { uint32_t before; ScriptStream stream; uint32_t after; };
static Fixture a,b;
static uint8_t bytes[4]={0,127,128,255};
static uint8_t stale[2]={42,13};
static ScriptStream* active;
static uint32_t suppliedCount, calls, errors;
static bool nullBuffer, mutate;
static const uint8_t* supplied;
static const uint8_t* RIFF_CDECL readChunk(void* context,void* argument,uint32_t* count) {
    ++calls;
    if(context != static_cast<void*>(&bytes) || argument != static_cast<void*>(&stale)) ++errors;
    *count=suppliedCount;
    if(mutate) {
        active->remaining=0x12345678u;
        active->cursor=stale+1;
        active->readerArgument=bytes;
        active->readerContext=stale;
        active->reader=0;
    }
    return nullBuffer ? 0 : supplied;
}
static void init(Fixture& f,uint32_t remaining) {
    f.before=0x89abcdefu; f.after=0x76543210u;
    f.stream.remaining=remaining; f.stream.cursor=stale;
    f.stream.reader=readChunk; f.stream.readerArgument=stale; f.stream.readerContext=bytes;
}
static bool equal() {
    return a.before==b.before && a.after==b.after && a.stream.remaining==b.stream.remaining
        && a.stream.cursor==b.stream.cursor && a.stream.reader==b.stream.reader
        && a.stream.readerArgument==b.stream.readerArgument && a.stream.readerContext==b.stream.readerContext;
}
static bool run(uint32_t remaining,uint32_t count,bool isNull,bool changes,unsigned index) {
    init(a,remaining); init(b,remaining);
    suppliedCount=count; nullBuffer=isNull; mutate=changes; supplied=bytes+index;
    calls=errors=0; active=&a.stream;
    int x=a.stream.peek(); uint32_t firstCalls=calls;
    active=&b.stream;
    int y=original_script_stream_peek(&b.stream);
    active=0;
    if(errors || calls!=firstCalls*2 || firstCalls!=(remaining==0 ? 1u:0u) || x!=y || !equal()) return false;
    int expected=remaining ? 42 : (isNull || !count ? -1 : bytes[index]);
    if(x!=expected || a.before!=0x89abcdefu || a.after!=0x76543210u) return false;
    uint32_t expectedCount=remaining ? remaining : ((!isNull && count) ? count : (changes ? 0x12345678u:0u));
    const uint8_t* expectedCursor=remaining ? stale : ((!isNull && count) ? supplied : (changes ? stale+1:stale));
    if(a.stream.remaining!=expectedCount || a.stream.cursor!=expectedCursor) return false;
    // A second successful peek must leave the buffer untouched and not refill.
    if(expected>=0 && a.stream.remaining) {
        uint32_t oldCalls=calls;
        if(a.stream.peek()!=expected || original_script_stream_peek(&b.stream)!=expected || calls!=oldCalls || !equal()) return false;
    }
    return true;
}
extern "C" int test_main() {
    const uint32_t values[]={0,1,2,0x80000000u,0xffffffffu};
    for(unsigned r=0;r<5;++r)
        for(unsigned c=0;c<5;++c)
            for(unsigned n=0;n<2;++n)
                for(unsigned m=0;m<2;++m)
                    for(unsigned i=0;i<4;++i)
                        if(!run(values[r],values[c],n!=0,m!=0,i)) return 1;
    return 0;
}
